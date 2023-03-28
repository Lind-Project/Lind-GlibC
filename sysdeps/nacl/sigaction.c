#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stddef.h>
#include <stdint.h>

#include <irt_syscalls.h>
#include <nacl_sigaction.h>

void __sigaction_to_nacl_abi_sigaction(
    struct sigaction *act,
    struct nacl_abi_sigaction *nacl_act
) {
  if (nacl_act != NULL && act != NULL) {
    nacl_act->__sa_handler = (uint32_t)(act->sa_handler);
    nacl_act->sa_flags = act->sa_flags;

    for (int i = 0; i < 16; ++i) {
      nacl_act->sa_mask.val[i] = act->sa_mask.__val[i];
    }
  }
}

void __nacl_abi_sigaction_to_sigaction(
    struct nacl_abi_sigaction *nacl_act,
    struct sigaction *act
) {
  if (nacl_act != NULL && act != NULL) {
    act->sa_handler = (__sighandler_t)(nacl_act->__sa_handler);
    act->sa_flags = nacl_act->sa_flags;

    for (int i = 0; i < 16; ++i) {
      act->sa_mask.__val[i] = nacl_act->sa_mask.val[i];
    }
  }
}

/* If ACT is not NULL, change the action for SIG to *ACT.
   If OACT is not NULL, put the old action for SIG in *OACT.  */
int __libc_sigaction(
    int sig,
    const struct sigaction *act,
    struct sigaction *oact
) {
  int result;
  struct nacl_abi_sigaction nacl_act, nacl_oact;

  if (sig <= 0 || sig >= NSIG) {
    __set_errno (EINVAL);
    return -1;
  }

  __sigaction_to_nacl_abi_sigaction(act, &nacl_act);
  __sigaction_to_nacl_abi_sigaction(oact, &nacl_oact);

  result = __nacl_irt_sigaction(
    sig,
    (act == NULL) ? NULL : &nacl_act,
    (oact == NULL) ? NULL : &nacl_oact
  );

  __nacl_abi_sigaction_to_sigaction(&nacl_oact, oact);

  if (result != 0) {
    __set_errno (result);
    return -1;
  }

  return 0;
}

libc_hidden_def (__libc_sigaction)

weak_alias (__libc_sigaction, __sigaction)
libc_hidden_weak (__sigaction)
weak_alias (__libc_sigaction, sigaction)

#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stddef.h>

#include <irt_syscalls.h>


/* If ACT is not NULL, change the action for SIG to *ACT.
   If OACT is not NULL, put the old action for SIG in *OACT.  */
int __libc_sigaction(
     int sig,
     const struct sigaction *act,
     struct sigaction *oact
) {
  int result;

  if (sig <= 0 || sig >= NSIG) {
    __set_errno (EINVAL);
    return -1;
  }

  result = __nacl_irt_sigaction(sig, act, oact);
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

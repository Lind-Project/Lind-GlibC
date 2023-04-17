#include <errno.h>
#include <signal.h>
#include <stddef.h>

#include <irt_syscalls.h>
#include <nacl_signal.h>

void __remove_unwanted_signals(uint64_t *nacl_set) {
  *nacl_set &= ~(1 << (SIGKILL-1));
  *nacl_set &= ~(1 << (SIGSTOP-1));
}

/* Get and/or change the set of blocked signals.  */
int __sigprocmask (int how, const sigset_t *set, sigset_t *oldset)
{
  uint64_t nacl_set = 0;
  uint64_t nacl_oldset = 0;
  int result;

  __sigset_t_to_uint(set, &nacl_set);
  __sigset_t_to_uint(oldset, &nacl_oldset);
  __remove_unwanted_signals(&nacl_set);

  result = __nacl_irt_sigprocmask(
    how,
    set ? &nacl_set : NULL,
    oldset ? &nacl_oldset : NULL
  );

  if (result != 0) {
    __set_errno (result);
    return -1;
  }

  __uint_to_sigset_t(&nacl_oldset, oldset);

  return 0;
}

weak_alias (__sigprocmask, sigprocmask)
weak_alias (__sigprocmask, __libc_sigprocmask)

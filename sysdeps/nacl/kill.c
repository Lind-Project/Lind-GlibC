#include <errno.h>
#include <signal.h>

int __libc_kill(pid_t pid, int sig) {
  int result;
  
  if (sig < 0 || sig >= NSIG) {
    __set_errno (EINVAL);
    return -1;
  }

  result = __nacl_irt_kill(pid, sig);
  if (result != 0) {
    __set_errno (result);
    return -1;
  }

  return 0;
}

libc_hidden_def (__libc_kill)

weak_alias (__libc_kill, __kill)
libc_hidden_weak (__kill)
weak_alias (__libc_kill, kill)

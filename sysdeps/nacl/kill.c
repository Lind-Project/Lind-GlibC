#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stddef.h>

#include <irt_syscalls.h>

int __kill(pid_t pid, int sig) {
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

weak_alias (__kill, kill)
weak_alias (__kill, __libc_kill)

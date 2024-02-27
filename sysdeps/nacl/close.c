
#include <errno.h>
#include <unistd.h>

#include <irt_syscalls.h>


int __close (int fd)
{
  int result = __nacl_irt_close (fd);
  if (result < 0) {
    __set_errno(-result);
    return -1;
  }
  return 0;
}
libc_hidden_def (__close)
weak_alias (__close, close)
strong_alias (__close, __libc_close)
strong_alias (__close, __close_nocancel)

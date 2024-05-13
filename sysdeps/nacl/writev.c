#include <errno.h>
#include <unistd.h>
#include <sysdep.h>

#include <irt_syscalls.h>


ssize_t __writev(int desc, const struct iovec *iov, int iovcnt)
{
  int result = __nacl_irt_writev (desc, iov, iovcnt);
  if (result < 0) {
    __set_errno(-result);
    return -1;
  }
  return result;
}
libc_hidden_def (__writev)
weak_alias (__writev, writev)

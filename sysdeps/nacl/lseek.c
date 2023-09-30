
#include <errno.h>
#include <unistd.h>

#include <irt_syscalls.h>


off_t __lseek (int fd, off_t offset, int whence)
{
  int result = __nacl_irt_seek (fd, offset, whence);
  if (result < 0) {
    __set_errno(-result);
    return -1;
  }
  return result;
}
libc_hidden_def (__lseek)
weak_alias (__lseek, lseek)

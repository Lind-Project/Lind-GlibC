#include <errno.h>
#include <unistd.h>
#include <stddef.h>

#include <irt_syscalls.h>


ssize_t __ftruncate (int fd, off_t length)
{
  int result = __nacl_irt_ftruncate (fd, length);
  if (result != 0) {
    __set_errno(-result);
    return -1;
  }
  return 0;
}

weak_alias (__ftruncate, ftruncate)
weak_alias (__ftruncate, __libc_ftruncate)

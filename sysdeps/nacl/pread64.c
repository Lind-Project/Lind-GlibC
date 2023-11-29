#include <errno.h>
#include <unistd.h>
#include <stddef.h>

#include <irt_syscalls.h>


ssize_t __pread64 (int fd, void *buf, size_t size, off_t offset)
{
  int result = __nacl_irt_pread64 (fd, buf, size, offset);
  if (result < 0) {
    __set_errno(-result);
    return -1;
  }
  return result;
}

weak_alias (__pread64, pread64)
weak_alias (__pread64, __libc_pread64)

#include <errno.h>
#include <unistd.h>
#include <stddef.h>

#include <irt_syscalls.h>


ssize_t __pread (int fd, void *buf, size_t size, off_t offset)
{
  int result = __nacl_irt_pread (fd, buf, size, offset);
  if (result < 0) {
    __set_errno(-result);
    return -1;
  }
  return result;
}

weak_alias (__pread, pread)
weak_alias (__pread, __libc_pread)

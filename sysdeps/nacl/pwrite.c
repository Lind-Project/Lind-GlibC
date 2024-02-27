#include <errno.h>
#include <unistd.h>
#include <sysdep.h>

#include <irt_syscalls.h>


ssize_t __pwrite(int desc, void const *buf, size_t count, off_t offset)
{
  int result = __nacl_irt_pwrite (desc, buf, count, offset);
  if (result < 0) {
    __set_errno(-result);
    return -1;
  }
  return result;
}

weak_alias (__pwrite, pwrite)
weak_alias (__pwrite, __libc_pwrite)

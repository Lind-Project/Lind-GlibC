
#include <errno.h>
#include <unistd.h>

#include <nacl_syscalls.h>
#include "strace.h"

off_t __lseek (int fd, off_t offset, int whence)
{
  nacl_strace("lseek");
  nacl_abi_off_t nacl_offset = offset;
  int result = NACL_SYSCALL (lseek) (fd, &nacl_offset, whence);
  if (result < 0) {
    errno = -result;
    return -1;
  }
  return nacl_offset;
}
libc_hidden_def (__lseek)
weak_alias (__lseek, lseek)

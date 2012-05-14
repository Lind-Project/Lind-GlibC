
#include <errno.h>
#include <unistd.h>
#include <stddef.h>

#include <nacl_syscalls.h>
#include "strace.h"
#include "nacl_util.h"
#include "lind_syscalls.h"

ssize_t __libc_read (int fd, void *buf, size_t size)
{
  int result = -1;

  if (fd >= 10) {
    result = lind_read_rpc(fd, size, buf);
  }  else {
    result = NACL_SYSCALL (read) (fd, buf, size);
  }

  if (result < 0) {
    errno = -result;
    return -1;
  }

  return result;
}

libc_hidden_def (__libc_read)
weak_alias (__libc_read, __read)
libc_hidden_weak (__read)
weak_alias (__libc_read, read)
strong_alias (__libc_read, __read_nocancel)

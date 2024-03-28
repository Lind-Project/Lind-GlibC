#include <errno.h>
#include <unistd.h>
#include <stddef.h>

#include <irt_syscalls.h>


ssize_t __truncate (const char *path, off_t length)
{
  int result = __nacl_irt_truncate (path, length);
  if (result != 0) {
    errno = result;
    return -1;
  }
  return 0;
}

weak_alias (__truncate, truncate)
weak_alias (__truncate, __libc_truncate)

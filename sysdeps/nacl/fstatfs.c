#include <errno.h>
#include <sys/statfs.h>
#include <stddef.h>
#include <irt_syscalls.h>

/* Return information about the filesystem on which FD resides.  */
int
__fstatfs (int fd, struct statfs *buf)
{
  int result = __nacl_irt_fstatfs(fd, buf);
  
  if (result < 0) {
    __set_errno (-result);
     return -1;
  }
   return result;
}

weak_alias (__fstatfs, fstatfs)

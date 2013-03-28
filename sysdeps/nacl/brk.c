
#include <errno.h>
#include <unistd.h>
#include <sysdep.h>

#include <irt_syscalls.h>
#include <nacl_syscalls.h>
#include "strace.h"

void *__curbrk = 0;
weak_alias (__curbrk, ___brk_addr)

int __brk (void *addr)
{
  nacl_strace("brk");
  int rv = __nacl_irt_sysbrk (&addr);

  if (rv != 0) {
    errno = rv;
    return -1;
  }

  __curbrk = addr;
  return 0;
}
weak_alias (__brk, brk)

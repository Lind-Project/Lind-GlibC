
#include <stdlib.h>
#include <unistd.h>

#include <irt_syscalls.h>
#include <nacl_syscalls.h>
#include "strace.h"


void _exit (int status)
{
  nacl_strace("exit");
  __nacl_irt_exit (status);
  /* In case the syscall returns: */
  while (1)
    __asm__("hlt");
}
libc_hidden_def (_exit)
weak_alias (_exit, _Exit)

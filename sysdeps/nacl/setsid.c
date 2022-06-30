#include <unistd.h>

#include <irt_syscalls.h>

/*
 * imitates setsid with getpid
 */
pid_t __setsid (void)
{
  return __nacl_irt_getpid();
}

weak_alias (__setsid, setsid)

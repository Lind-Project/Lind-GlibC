
#include <errno.h>
#include <sys/stat.h>

#include <nacl_stat.h>
#include <nacl_syscalls.h>

#include "nacl_util.h"
#include "lind_syscalls.h"
#include "strace.h"


int __xstat (int version, const char *path, struct stat *buf)
{
  if (buf == NULL || path == NULL)
    {
      errno = EFAULT;
      return -1;
    }
  nacl_strace("xstat");
  /* struct nacl_abi_stat st; */

  int result = lind_xstat_rpc(version, path, buf);
   /* int result = NACL_SYSCALL (stat) (path, &st); */


  if (result < 0)
    {
      errno = -result;
      return -1;
    }
  else
    {
      /*__nacl_abi_stat_to_stat (&st, buf);*/
      return 0;
    }
}
libc_hidden_def (__xstat)
#ifdef SHARED
extern __typeof (__xstat64) __xstat64 __attribute__ ((alias ("__GI___xstat")));
#endif

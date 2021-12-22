
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>

#include <kernel_stat.h>
#include <irt_syscalls.h>


int __fxstat (int vers, int fd, struct stat *buf)
{
  if (buf == NULL) {
    errno = EFAULT;
    return -1;
  }
  int result = __nacl_irt_fstat (fd, buf);
  if (result != 0) {
    errno = result;
    return -1;
  }
  return 0;
}
hidden_def(__fxstat)
#ifdef SHARED
extern __typeof (__fxstat64) __fxstat64 __attribute__ ((alias ("__GI___fxstat")));
#endif

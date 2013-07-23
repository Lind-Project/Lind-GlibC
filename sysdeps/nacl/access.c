#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include "lind_strace.h"
#include "lind_util.h"
#include "lind_syscalls.h"

/* Test for access to FILE.  */
int
__access (const char* file, int type)
{
  if (file == NULL || (type & ~(R_OK|W_OK|X_OK|F_OK)) != 0)
    {
      __set_errno (EINVAL);
      return -1;
    }

  /* Since everything is okay, forward to lind server. */
  int return_code = lind_access(type, file);

  if (return_code < 0) {
    __set_errno ( -1 * return_code);
    return -1;
  } else {
    return return_code;
  }
}

weak_alias (__access, access)

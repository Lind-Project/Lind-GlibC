#include <errno.h>
#include <stddef.h>
#include <unistd.h>

/* Remove the link named NAME.  */
int __unlink (const char * name)  {
  if (name == NULL)
    {
      __set_errno (EINVAL);
      return -1;
    }
  /* since everything is okay, forward to lind server. */

  int result = __nacl_irt_unlink(name);

  if (result < 0) {
    __set_errno ( -result);
    return -1;
  } else {
    return result;
  }
}

weak_alias (__unlink, unlink)

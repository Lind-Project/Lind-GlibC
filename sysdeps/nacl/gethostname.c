#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <irt_syscalls.h>

int __gethostname(char *name, size_t len)
{
  int ret = __nacl_irt_gethostname(name, len);
  if (ret < 0) {
      __set_errno (-ret);
      return -1;
  }
  return ret;
}

weak_alias (__gethostname, gethostname)

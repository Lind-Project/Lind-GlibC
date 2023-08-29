#include <unistd.h>
#include <errno.h>
#include <irt_syscalls.h>

int __mkdir(const char* pathname, mode_t mode) {
  int ret = __nacl_irt_mkdir(pathname, mode);
  if (ret < 0) {
      __set_errno (-ret);
      return -1;
  }
  return 0;    
}

weak_alias (__mkdir, mkdir)

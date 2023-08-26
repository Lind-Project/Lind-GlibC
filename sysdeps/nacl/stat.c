#include <errno.h>
#include <stddef.h>
#include <irt_syscalls.h>

int __stat (const char *pathname, struct nacl_abi_stat *st)
{
  int result;
  result = __nacl_irt_stat(pathname, st);
  if (result < 0) {
    __set_errno(-result);
    return -1;
  }
  return 0;
}
libc_hidden_def (__stat)
weak_alias (__stat, stat)

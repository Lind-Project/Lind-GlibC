#include <errno.h>
#include <unistd.h>
#include <sysdep.h>

#include <irt_syscalls.h>


ssize_t __write(int desc, void const *buf, size_t count)
{
  int result = __nacl_irt_write (desc, buf, count);
  if (result < 0) {
    __set_errno(-result);
    return -1;
  }
  return result;
}
libc_hidden_def (__write)
weak_alias (__write, write)
strong_alias (__write, __libc_write)
libc_hidden_def (__libc_write)
strong_alias (__write, __write_nocancel)

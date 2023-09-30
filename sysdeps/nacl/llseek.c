
#include <errno.h>

#include <irt_syscalls.h>


loff_t __llseek (int fd, loff_t offset, int whence)
{
  nacl_abi_off_t nacl_offset = offset;
  int result = __nacl_irt_seek (fd, nacl_offset, whence);
  if (result < 0)
    {
      __set_errno(-result);
      return -1;
    }
  return result;
}
weak_alias (__llseek, llseek)


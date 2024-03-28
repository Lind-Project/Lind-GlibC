#include <errno.h>

#include <irt_syscalls.h>


loff_t __llseek (int fd, loff_t offset, int whence)
{
  int result = __nacl_irt_seek (fd, offset, whence);
  if (result < 0)
    {
      __set_errno(-result);
      return -1;
    }
  return offset;
}
weak_alias (__llseek, llseek)

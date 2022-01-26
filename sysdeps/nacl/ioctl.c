#include <errno.h>
#include <stdarg.h>
#include <sys/ioctl.h>

#include <irt_syscalls.h>

int __ioctl (int fd, unsigned long int request, ...) {

    if (fd < 0) {
      __set_errno (EBADF);
      return -1;
    }

    int arg = 0;
    void* arg_ptr = &arg;

    if (request == FIONBIO) {
      /* This command has a single void pointer as an arg, pointing to an integer*/
      va_list ap;
      va_start (ap, request);
      arg_ptr = va_arg (ap, void *);
    } else {
      /*  Lind does not support any other commands at this point*/
      __set_errno (ENOSYS);
      return -1;
    }

    result = __nacl_irt_ioctl(fd, request, arg_ptr);

    return result;
}

weak_alias (__ioctl, ioctl)

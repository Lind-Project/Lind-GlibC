#include <errno.h>
#include <stdarg.h>
#include <sys/ioctl.h>

#include <irt_syscalls.h>

int __ioctl (int fd, unsigned long request, ...) {

    if (fd < 0) {
      __set_errno (EBADF);
      return -1;
    }

    /*In requests that do not have any arguments, we simply pass a pointer to the int
      we define here as a placeholder since Lind excepts a pointer at the NaCl side.*/
    int arg = 0;
    void* arg_ptr = &arg; //Replaced later for requests using an arg
    int result;

    /*Right now, we are only passing down pointers to NaCl. Any non-pointer value
      for arg_ptr will cause a sysaddr translation error in NaCl.
      As a result, the arg_ptr should be set to &va_arg (ap, void *)
      instead of va_arg (ap, void *) for requests that directly accept 
      an arg value and not a pointer.*/

    if (request == FIONBIO || request == FIOASYNC) {
      /* This command has a single void pointer as an arg, pointing to an integer*/
      va_list ap;
      va_start (ap, request);
      arg_ptr = va_arg (ap, void *);
    } else {
      /*  Lind does not support any other commands at this point*/
      __set_errno (ENOSYS);
      return -1;
    }

    /*As all the valid commands are not listed right now, we return ENOSYS even when
      the given request is invalid for ioctl. (Which should normally return EINVAL)*/

    result = __nacl_irt_ioctl(fd, request, arg_ptr);

    if (result < 0) {
      __set_errno(-result);
      return -1;
    }

    return result;
}

weak_alias (__ioctl, ioctl)

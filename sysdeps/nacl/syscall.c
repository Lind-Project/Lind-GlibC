#include <errno.h>
#include <stdarg.h>
#include <nacl_syscalls.h>
#include <irt_syscalls.h>

long int __syscall (long int __sysno, ...) {


    write(1, "in syscall\n", 11);

    va_list args;
    va_start(args, __sysno);
    long arg1 = va_arg(args, long);
    long arg2 = va_arg(args, long); 
    long arg3 = va_arg(args, long); 
    long arg4 = va_arg(args, long); 
    long arg5 = va_arg(args, long); 
    long arg6 = va_arg(args, long); 

    int result = ((TYPE_nacl_syscall) NACL_SYSCALL_ADDR (__sysno)) (arg1, arg2, arg3, arg4, arg5, arg6);
    va_end(args);

    if (result < 0) {
        __set_errno (-result);
        return -1;
    }

    return result;
}

weak_alias (__syscall, syscall)

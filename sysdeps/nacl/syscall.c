#include <errno.h>
#include <stdarg.h>

#include <irt_syscalls.h>

int __syscall (int callnum, ...) {


    long result;
    va_list argptr;
    va_start(argptr, callnum);
    result = __nacl_irt_syscall(callnum, argptr);
    va_end(argptr);

    if (result < 0) {
        __set_errno (-result);
        return -1;
    }

    return result;
}

weak_alias (__syscall, syscall)

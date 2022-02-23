#include <errno.h>
#include <stdarg.h>
#include <nacl_syscalls.h>
#include <irt_syscalls.h>

int __syscall (int callnum, ...) {


    write(1, "in syscall\n", 11);

    va_list argptr;
    va_start(argptr, callnum);
    int result = __nacl_irt_syscall(callnum, argptr);
    va_end(argptr);

    if (result < 0) {
        __set_errno (-result);
        return -1;
    }

    return result;
}

weak_alias (__syscall, syscall)

#include <unistd.h>
#include <errno.h>
#include <irt_syscalls.h>

int __mkdir(const char* pathname, mode_t mode) {
    return __nacl_irt_mkdir(pathname, mode);
}

weak_alias (__mkdir, mkdir)

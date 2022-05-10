#include <errno.h>
#include <sysdep.h>
#include <unistd.h>
#include <irt_syscalls.h>

int __rename(const char *oldpath, const char *newpath)
{
    int ret = __nacl_irt_rename(oldpath, newpath);
    if (ret < 0) {
            __set_errno (-ret);
            return -1;
    }
    return ret;
}
weak_alias (__rename, rename)

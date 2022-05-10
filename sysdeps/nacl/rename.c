#include <errno.h>
#include <sysdep.h>
#include <unistd.h>


int __rename(const char *oldpath, const char *newpath)
{
    int ret = __nacl_irt_rename(oldpath, newpath);
    if (ret < 0) {
            __set_errno (-ret);
            return -1;
    }
    return ret;
}
libc_hidden_def (__rename)
weak_alias (__rename, rename)
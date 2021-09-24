#ifndef _LIND_SYSCALLS_H_
#define _LIND_SYSCALLS_H_

#include <sys/types.h>
#include <nacl_stat.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <unistd.h>

#define LIND_debug_noop                 1
#define LIND_debug_trace                3
#define LIND_fs_ioctl                   15
#define LIND_safe_fs_mmap               21
#define LIND_safe_fs_munmap             22
#define LIND_safe_fs_rename             55
#define LIND_safe_net_epoll_create      56
#define LIND_safe_net_epoll_ctl         57
#define LIND_safe_net_epoll_wait        58

#define SET_ERR_AND_RETURN(x) \
    do { \
        int result = (x); \
        if (result < 0) { \
            __set_errno(-result); \
            return -1; \
        } \
        return result; \
    } while (0)

#endif /* _LIND_SYSCALLS_H_ */


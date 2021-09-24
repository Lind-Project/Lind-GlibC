#ifndef _LIND_SYSCALLS_H_
#define _LIND_SYSCALLS_H_




#include <sys/types.h>
#include <nacl_stat.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <sys/epoll.h>
#include <unistd.h>

#define LIND_debug_noop                 1
#define LIND_debug_trace                3
#define LIND_fs_ioctl                   15
#define LIND_safe_fs_mmap               21
#define LIND_safe_fs_munmap             22
#define LIND_safe_net_getpeername       41
#define LIND_safe_net_getsockname       42
#define LIND_safe_net_poll              48
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

int lind_noop (void);
int lind_getsockname (int sockfd, socklen_t addrlen_in, struct sockaddr * addr, socklen_t * addrlen_out);
int lind_getpeername (int sockfd, socklen_t addrlen_in, struct sockaddr * addr, socklen_t * addrlen_out);
int lind_poll (int nfds, int timeout, struct pollfd *fds_in, struct pollfd *fds_out);
int lind_strace (const char* str);
int lind_epoll_create (int size);
int lind_epoll_ctl (int epfd, int op, int fd, struct epoll_event *event);
int lind_epoll_wait(int epfd, struct epoll_event *events,
                      int maxevents, int timeout);
ssize_t lind_sendmsg(int sockfd, const struct msghdr *msg, int flags);
ssize_t lind_recvmsg(int socket, struct msghdr *message, int flags);
#endif /* _LIND_SYSCALLS_H_ */


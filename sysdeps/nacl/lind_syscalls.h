#ifndef _LIND_SYSCALLS_H_
#define _LIND_SYSCALLS_H_




#include <sys/types.h>
#include <nacl_stat.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/select.h>
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
#define LIND_safe_net_select            46
#define LIND_safe_net_poll              48
#define LIND_safe_net_socketpair        49
#define LIND_safe_fs_rename             55
#define LIND_safe_net_epoll_create      56
#define LIND_safe_net_epoll_ctl         57
#define LIND_safe_net_epoll_wait        58
#define LIND_safe_net_sendmsg           59
#define LIND_safe_net_recvmsg           60

struct select_results {
    struct timeval used_t;
    fd_set r;
    fd_set w;
    fd_set e;
};

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
int lind_select (int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, const struct timeval *timeout, struct select_results *result);
int lind_poll (int nfds, int timeout, struct pollfd *fds_in, struct pollfd *fds_out);
int lind_socketpair (int domain, int type, int protocol, int *fds);
int lind_strace (const char* str);
<<<<<<< HEAD

ssize_t lind_sendmsg(int sockfd, const struct msghdr *msg, int flags);
ssize_t lind_recvmsg(int socket, struct msghdr *message, int flags);
=======
int lind_epoll_create (int size);
int lind_epoll_ctl (int epfd, int op, int fd, struct epoll_event *event);
int lind_epoll_wait(int epfd, struct epoll_event *events,
                      int maxevents, int timeout);
>>>>>>> unified_syscalls

#endif /* _LIND_SYSCALLS_H_ */


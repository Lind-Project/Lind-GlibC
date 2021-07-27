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
#define LIND_safe_fs_access             2
#define LIND_debug_trace                3
#define LIND_safe_fs_lseek              14
#define LIND_fs_ioctl                   15
#define LIND_safe_fs_mmap               21
#define LIND_safe_fs_munmap             22
#define LIND_safe_fs_getdents           23
#define LIND_safe_fs_dup                24
#define LIND_safe_fs_dup2               25
#define LIND_safe_fs_fcntl              28
#define LIND_safe_net_bind              33
#define LIND_safe_net_connect           38
#define LIND_safe_net_listen            39
#define LIND_safe_net_accept            40
#define LIND_safe_net_getpeername       41
#define LIND_safe_net_getsockname       42
#define LIND_safe_net_getsockopt        43
#define LIND_safe_net_setsockopt        44
#define LIND_safe_net_select            46
#define LIND_safe_net_getifaddrs        47
#define LIND_safe_net_poll              48
#define LIND_safe_net_socketpair        49
#define LIND_safe_fs_rename             55
#define LIND_safe_net_epoll_create      56
#define LIND_safe_net_epoll_ctl         57
#define LIND_safe_net_epoll_wait        58
#define LIND_safe_net_sendmsg           59
#define LIND_safe_net_recvmsg           60
// yiwen: added lind_pipe

#define LIND_safe_fs_pipe              66
#define LIND_safe_sys_pipe2             67

#define LIND_comp_cia                   105
#define LIND_comp_call                  106
#define LIND_comp_accept                107
#define LIND_comp_recv                  108

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

int lind_access (int version, const char *file);
int lind_lseek (off_t offset, int fd, int whence, off_t * ret);
int lind_noop (void);
int lind_pipe (int* pipedes);
int lind_pipe2 (int* pipedes, int flags);
int lind_dup (int oldfd);
int lind_dup2 (int oldfd, int newfd);
int lind_getdents (int fd, size_t nbytes, char *buf);
int lind_fcntl_get (int fd, int cmd);
int lind_fcntl_set (int fd, int cmd, long set_op);
int lind_bind (int sockfd, socklen_t addrlen, const struct sockaddr *addr);
int lind_connect (int sockfd, socklen_t addrlen, const struct sockaddr *src_addr);
int lind_listen (int sockfd, int backlog);
int lind_accept (int sockfd, int flags, struct sockaddr *addr, socklen_t *addrlen);
int lind_getsockname (int sockfd, socklen_t addrlen_in, struct sockaddr * addr, socklen_t * addrlen_out);
int lind_getpeername (int sockfd, socklen_t addrlen_in, struct sockaddr * addr, socklen_t * addrlen_out);
int lind_setsockopt (int sockfd, int level, int optname, socklen_t optlen, const void *optval);
int lind_getsockopt (int sockfd, int level, int optname, socklen_t optlen, void *optval);
int lind_select (int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, const struct timeval *timeout, struct select_results *result);
int lind_getifaddrs (int ifaddrs_buf_siz, void *ifaddrs);
int lind_poll (int nfds, int timeout, struct pollfd *fds_in, struct pollfd *fds_out);
int lind_socketpair (int domain, int type, int protocol, int *fds);
int lind_strace (const char* str);
int lind_epoll_create (int size);
int lind_epoll_ctl (int epfd, int op, int fd, struct epoll_event *event);
int lind_epoll_wait(int epfd, struct epoll_event *events,
                      int maxevents, int timeout);
ssize_t lind_sendmsg(int sockfd, const struct msghdr *msg, int flags);
ssize_t lind_recvmsg(int socket, struct msghdr *message, int flags);

#endif /* _LIND_SYSCALLS_H_ */


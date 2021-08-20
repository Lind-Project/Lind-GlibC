#include <stdio.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>
#include <nacl_syscalls.h>

#include <lind_syscalls.h>
#include <lind_strace.h>
#include <lind_util.h>
#include <component.h>

#include <nacl_stat.h>


typedef enum _LindArgType {AT_INT, AT_STRING, AT_STRING_OPTIONAL, AT_DATA, AT_DATA_OPTIONAL} LindArgType;

typedef struct _LindArg
{
    LindArgType arg_type;
    uint64_t ptr;
    uint64_t len;
} LindArg;

int lind_noop (void)
{
    return NACL_SYSCALL(lind_api)(LIND_debug_noop, 0, NULL, 0, NULL);
}

int lind_dup (int oldfd)
{
    LindArg in_args[1] = {{AT_INT, oldfd, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_dup, 2, in_args, 0, NULL);
}

int lind_dup2 (int oldfd, int newfd)
{
    LindArg in_args[2] = {{AT_INT, oldfd, 0}, {AT_INT, newfd, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_dup2, 2, in_args, 0, NULL);
}

int lind_getdents (int fd, size_t nbytes, char *buf)
{
    LindArg in_args[2] = {{AT_INT, fd, 0}, {AT_INT, nbytes, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)buf, nbytes}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_getdents, 2, in_args, 1, out_args);
}

int lind_fcntl_get (int fd, int cmd)
{
    LindArg in_args[2] = {{AT_INT, fd, 0}, {AT_INT, cmd, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_fcntl, 2, in_args, 0, NULL);
}

int lind_fcntl_set (int fd, int cmd, long set_op)
{
    LindArg in_args[3] = {{AT_INT, fd, 0}, {AT_INT, cmd, 0}, {AT_INT, set_op, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_fs_fcntl, 3, in_args, 0, NULL);
}




int lind_listen (int sockfd, int backlog)
{
    LindArg in_args[2] = {{AT_INT, sockfd, 0}, {AT_INT, backlog, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_listen, 2, in_args, 0, NULL);
}

int lind_getpeername (int sockfd, socklen_t addrlen_in, struct sockaddr * addr, socklen_t * addrlen_out)
{
    LindArg in_args[2] = {{AT_INT, sockfd, 0}, {AT_INT, addrlen_in, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)addr, addrlen_in}};
    if(addrlen_out) {
        *addrlen_out = addrlen_in;
    }
    return NACL_SYSCALL(lind_api)(LIND_safe_net_getpeername, 2, in_args, 1, out_args);
}

int lind_getsockname (int sockfd, socklen_t addrlen_in, struct sockaddr * addr, socklen_t * addrlen_out)
{
    LindArg in_args[2] = {{AT_INT, sockfd, 0}, {AT_INT, addrlen_in, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)addr, addrlen_in}};
    if(addrlen_out) {
        *addrlen_out = addrlen_in;
    }
    return NACL_SYSCALL(lind_api)(LIND_safe_net_getsockname, 2, in_args, 1, out_args);
}



int lind_select (int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, const struct timeval *timeout, struct select_results *result)
{
    LindArg in_args[5] = {{AT_INT, nfds, 0}, {AT_DATA_OPTIONAL, (uintptr_t)readfds, sizeof(fd_set)},
            {AT_DATA_OPTIONAL, (uintptr_t)writefds, sizeof(fd_set)}, {AT_DATA_OPTIONAL, (uintptr_t)exceptfds, sizeof(fd_set)},
            {AT_DATA_OPTIONAL, (uintptr_t)timeout, sizeof(struct timeval)}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)result, sizeof(struct select_results)}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_select, 5, in_args, 1, out_args);
}

int lind_getifaddrs (int ifaddrs_buf_siz, void *ifaddrs)
{
    LindArg in_args[1] = {{AT_INT, ifaddrs_buf_siz, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)ifaddrs, ifaddrs_buf_siz}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_getifaddrs, 1, in_args, 1, out_args);
}

#define MAX_IOVLEN 512

ssize_t lind_sendmsg(int sockfd, const struct msghdr *msg, int flags) {
    LindArg in_args[MAX_IOVLEN+5];
    if(msg->msg_iovlen > MAX_IOVLEN) {
        return -ENOSYS;
    }
    size_t nargs = msg->msg_iovlen+5;
    in_args[0].arg_type = AT_INT;
    in_args[0].ptr = sockfd;
    in_args[0].len = 0;

    in_args[1].arg_type = AT_INT;
    in_args[1].ptr = flags;
    in_args[1].len = 0;

    in_args[2].arg_type = AT_DATA_OPTIONAL;
    in_args[2].ptr = (uintptr_t)msg->msg_name;
    in_args[2].len = msg->msg_namelen;

    in_args[3].arg_type = AT_DATA_OPTIONAL;
    in_args[3].ptr = (uintptr_t)msg->msg_control;
    in_args[3].len = msg->msg_controllen;

    in_args[4].arg_type = AT_INT;
    in_args[4].ptr = msg->msg_flags;
    in_args[4].len = 0;

    for(size_t i=5; i<nargs; ++i) {
        in_args[i].arg_type = AT_DATA;
        in_args[i].ptr = (uintptr_t)msg->msg_iov[i-5].iov_base;
        in_args[i].len = msg->msg_iov[i-5].iov_len;
    }

    return NACL_SYSCALL(lind_api)(LIND_safe_net_sendmsg, nargs, in_args, 0, NULL);
}

ssize_t lind_recvmsg(int sockfd, struct msghdr *msg, int flags) {
    LindArg in_args[MAX_IOVLEN+5];
    LindArg out_args[MAX_IOVLEN+2];
    if(msg->msg_iovlen > MAX_IOVLEN) {
        return -ENOSYS;
    }

    size_t nargs = msg->msg_iovlen+5;
    in_args[0].arg_type = AT_INT;
    in_args[0].ptr = sockfd;
    in_args[0].len = 0;

    in_args[1].arg_type = AT_INT;
    in_args[1].ptr = flags;
    in_args[1].len = 0;

    in_args[2].arg_type = AT_DATA_OPTIONAL;
    in_args[2].ptr = (uintptr_t)msg->msg_name;
    in_args[2].len = msg->msg_namelen;

    in_args[3].arg_type = AT_INT;
    in_args[3].ptr = msg->msg_controllen;
    in_args[3].len = 0;

    in_args[4].arg_type = AT_INT;
    in_args[4].ptr = msg->msg_flags;
    in_args[4].len = 0;

    // output control message
    out_args[0].arg_type = AT_DATA;
    out_args[0].ptr = (uintptr_t)msg->msg_control;
    out_args[0].len = msg->msg_controllen;

    // local address
    out_args[1].arg_type = AT_DATA_OPTIONAL;
    out_args[1].ptr = (uintptr_t)msg->msg_name;
    out_args[1].len = msg->msg_namelen;

    for (size_t i = 5; i < nargs; ++i) {
        // input IO vector lengths
        in_args[i].arg_type = AT_INT;
        in_args[i].ptr = msg->msg_iov[i-5].iov_len;
        in_args[i].len = 0;
        // output IO vectors
        out_args[i-3].arg_type = AT_DATA;
        out_args[i-3].ptr = (uintptr_t)msg->msg_iov[i-5].iov_base;
        out_args[i-3].len = msg->msg_iov[i-5].iov_len;
    }

    return NACL_SYSCALL(lind_api)(LIND_safe_net_recvmsg, nargs, in_args, nargs-3, out_args);
}

int lind_poll (int nfds, int timeout, struct pollfd *fds_in, struct pollfd *fds_out)
{
    LindArg in_args[3] = {{AT_INT, nfds, 0}, {AT_INT, timeout, 0}, {AT_DATA, (uintptr_t)fds_in, sizeof(struct pollfd)*nfds}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)fds_out, sizeof(struct pollfd)*nfds}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_poll, 3, in_args, 1, out_args);
}

int lind_socketpair (int domain, int type, int protocol, int *fds)
{
    LindArg in_args[3] = {{AT_INT, domain, 0}, {AT_INT, type, 0}, {AT_INT, protocol, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)fds, sizeof(int)*2}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_socketpair, 3, in_args, 1, out_args);
}

int lind_strace (const char* str)
{
#if 1
    LindArg in_args[1] = {{AT_STRING, (uintptr_t)str, 0}};
    return NACL_SYSCALL(lind_api)(LIND_debug_trace, 1, in_args, 0, NULL);
#else
    return 0;
#endif
}

int lind_epoll_create (int size)
{
    LindArg in_args[1] = {{AT_INT, (uintptr_t)size, 0}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_epoll_create, 1, in_args, 0, NULL);
}

int lind_epoll_ctl (int epfd, int op, int fd, struct epoll_event *event)
{
    LindArg in_args[4] = {{AT_INT, epfd, 0}, {AT_INT, op, 0},
        {AT_INT, fd, 0}, {AT_DATA, (uintptr_t)event, sizeof(struct epoll_event)}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_epoll_ctl, 4, in_args, 0, NULL);
}

int lind_epoll_wait(int epfd, struct epoll_event *events,
                      int maxevents, int timeout)
{
    LindArg in_args[3] = {{AT_INT, epfd, 0}, {AT_INT, maxevents, 0},
        {AT_INT, timeout, 0}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)events, sizeof(struct epoll_event)*maxevents}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_epoll_wait, 3, in_args, 1, out_args);
}


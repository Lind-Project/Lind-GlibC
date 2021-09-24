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



int lind_poll (int nfds, int timeout, struct pollfd *fds_in, struct pollfd *fds_out)
{
    LindArg in_args[3] = {{AT_INT, nfds, 0}, {AT_INT, timeout, 0}, {AT_DATA, (uintptr_t)fds_in, sizeof(struct pollfd)*nfds}};
    LindArg out_args[1] = {{AT_DATA, (uintptr_t)fds_out, sizeof(struct pollfd)*nfds}};
    return NACL_SYSCALL(lind_api)(LIND_safe_net_poll, 3, in_args, 1, out_args);
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


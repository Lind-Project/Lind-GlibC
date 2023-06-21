/*
 * Copyright (c) 2011 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * NaCl kernel / service run-time system call numbers
 */

/* TODO(mseaborn): Import this header file from outside rather than
   keeping a copy in the glibc tree. */

#ifndef NATIVE_CLIENT_SRC_TRUSTED_SERVICE_RUNTIME_INCLUDE_BITS_NACL_SYSCALLS_H_
#define NATIVE_CLIENT_SRC_TRUSTED_SERVICE_RUNTIME_INCLUDE_BITS_NACL_SYSCALLS_H_


#include <nacl_stat.h>
#include <nacl_signal.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <sys/statfs.h>
#include <sys/poll.h>
#include <sys/select.h>
#include <sys/shm.h>

/* intentionally not using zero */

/*
 * TODO(bsy,sehr): these identifiers should be NACL_ABI_SYS_<name>.
 */

#define NACL_sys_null                    1
#define NACL_sys_nameservice             2

#define NACL_sys_unlink                  4
#define NACL_sys_link                    5
#define NACL_sys_rename                  6

#define NACL_sys_dup                     8
#define NACL_sys_dup2                    9
#define NACL_sys_dup3                   10
#define NACL_sys_open                   11
#define NACL_sys_close                  12
#define NACL_sys_read                   13
#define NACL_sys_write                  14
#define NACL_sys_lseek                  15
#define NACL_sys_ioctl                  16
#define NACL_sys_stat                   17
#define NACL_sys_fstat                  18
#define NACL_sys_chmod                  19

/* no fchmod emulation on windows */

#define NACL_sys_sysbrk                 20
#define NACL_sys_mmap                   21
#define NACL_sys_munmap                 22
#define NACL_sys_getdents               23
#define NACL_sys_mprotect               24
#define NACL_sys_truncate               26
#define NACL_sys_ftruncate              27
#define NACL_sys_exit                   30
#define NACL_sys_getpid                 31
#define NACL_sys_sched_yield            32
#define NACL_sys_sysconf                33
#define NACL_sys_send                   34
#define NACL_sys_sendto                 35
#define NACL_sys_recv                   36
#define NACL_sys_recvfrom               37
#define NACL_sys_gettimeofday           40
#define NACL_sys_clock                  41
#define NACL_sys_nanosleep              42
#define NACL_sys_clock_getres           43
#define NACL_sys_clock_gettime          44
#define NACL_sys_shutdown               45
#define NACL_sys_select                 46
#define NACL_sys_getcwd                 47
#define NACL_sys_poll                   48
#define NACL_sys_socketpair             49
#define NACL_sys_getuid                 50
#define NACL_sys_geteuid                51
#define NACL_sys_getgid                 52
#define NACL_sys_getegid                53
#define NACL_sys_flock                  54

#define NACL_sys_shmget                 56
#define NACL_sys_shmat                  57
#define NACL_sys_shmdt                  58
#define NACL_sys_shmctl                 59

#define NACL_sys_imc_makeboundsock      60
#define NACL_sys_imc_accept             61
#define NACL_sys_imc_connect            62
#define NACL_sys_imc_sendmsg            63
#define NACL_sys_imc_recvmsg            64
#define NACL_sys_imc_mem_obj_create     65
#define NACL_sys_imc_socketpair         66
#define NACL_sys_mutex_destroy          69
#define NACL_sys_mutex_create           70
#define NACL_sys_mutex_lock             71
#define NACL_sys_mutex_trylock          72
#define NACL_sys_mutex_unlock           73
#define NACL_sys_cond_create            74
#define NACL_sys_cond_wait              75
#define NACL_sys_cond_signal            76
#define NACL_sys_cond_broadcast         77
#define NACL_sys_cond_destroy           78
#define NACL_sys_cond_timed_wait_abs    79
#define NACL_sys_thread_create          80
#define NACL_sys_thread_exit            81
#define NACL_sys_tls_init               82
#define NACL_sys_thread_nice            83
#define NACL_sys_tls_get                84
#define NACL_sys_second_tls_set         85
#define NACL_sys_second_tls_get         86
#define NACL_sys_srpc_get_fd            90
#define NACL_sys_sem_create             100
#define NACL_sys_sem_wait               101
#define NACL_sys_sem_post               102
#define NACL_sys_sem_get_value          103
#define NACL_sys_dyncode_create         104
#define NACL_sys_dyncode_modify         105
#define NACL_sys_dyncode_delete         106
#define NACL_sys_reg_restore            107
#define NACL_sys_reg_restore_2          108

#define NACL_sys_lind_api               113

#define NACL_sys_pipe                   114
#define NACL_sys_pipe2                  115
#define NACL_sys_fork                   116
#define NACL_sys_execv                  117
#define NACL_sys_execve                 118
#define NACL_sys_getppid                119
#define NACL_sys_waitpid                120
#define NACL_sys_wait                   121
#define NACL_sys_wait4                  122
#define NACL_sys_lstat                  124
#define NACL_sys_gethostname            125
#define NACL_sys_pread                  126
#define NACL_sys_pwrite                 127

#define NACL_sys_fcntl_get              128
#define NACL_sys_fcntl_set              129

#define NACL_sys_chdir                  130
#define NACL_sys_mkdir                  131
#define NACL_sys_rmdir                  132
#define NACL_sys_statfs                 133
#define NACL_sys_fstatfs                134
#define NACL_sys_fchmod                 135
#define NACL_sys_socket                 136
#define NACL_sys_getsockopt             137
#define NACL_sys_setsockopt             138
#define NACL_sys_access                 139
#define NACL_sys_accept                 140
#define NACL_sys_connect                141
#define NACL_sys_bind                   142
#define NACL_sys_listen                 143

#define NACL_sys_getsockname            144
#define NACL_sys_getpeername            145
#define NACL_sys_getifaddrs             146

#define NACL_sys_epoll_create           157
#define NACL_sys_epoll_ctl              158
#define NACL_sys_epoll_wait             159

#define NACL_sys_pread                  126
#define NACL_sys_pwrite                 127

#define NACL_sys_sigaction		160
#define NACL_sys_kill			161
#define NACL_sys_sigprocmask		162

#define NACL_MAX_SYSCALLS               256

#define NACL_SYSCALL_ADDR(syscall_number) \
  (0x10000 + ((syscall_number) << 5))

#define NACL_SYSCALL(syscall) \
  ((TYPE_nacl_ ## syscall) NACL_SYSCALL_ADDR(NACL_sys_ ## syscall))


struct NaClImcMsgHdr;
struct nacl_abi_stat;
struct timeval;
struct timespec;

#define socklen_t unsigned int
typedef int (*TYPE_nacl_syscall)(long arg1, long arg2, long arg3, long arg4, long arg5, long arg6);
typedef int (*TYPE_nacl_nameservice)(int *desc_in_out);
typedef int (*TYPE_nacl_link)(char *from, char *to);
typedef int (*TYPE_nacl_unlink)(char *name);
typedef int (*TYPE_nacl_rename)(const char *oldpath, const char *newpath);
typedef int (*TYPE_nacl_dup)(int oldfd);
typedef int (*TYPE_nacl_dup2)(int oldfd, int newfd);
typedef int (*TYPE_nacl_dup3)(int oldfd, int newfd, int flags);
typedef int (*TYPE_nacl_read) (int desc, void *buf, size_t count);
typedef int (*TYPE_nacl_close) (int desc);
typedef int (*TYPE_nacl_fstat) (int fd, struct nacl_abi_stat *stbp);
typedef int (*TYPE_nacl_fstatfs) (int fd, struct statfs *buf);
typedef int (*TYPE_nacl_statfs) (const char *path, struct statfs *buf);
typedef int (*TYPE_nacl_access) (const char *name, int mode);
typedef int (*TYPE_nacl_write) (int desc, void const *buf, size_t count);
typedef int (*TYPE_nacl_open) (char const *pathname, int flags, mode_t mode);
typedef int (*TYPE_nacl_lseek) (int desc, nacl_abi_off_t *offset, int whence);
typedef int (*TYPE_nacl_stat) (const char *file, struct nacl_abi_stat *st);
typedef int (*TYPE_nacl_lstat) (const char *file, struct nacl_abi_stat *st);

typedef int (*TYPE_nacl_getuid) (void);
typedef int (*TYPE_nacl_geteuid) (void);
typedef int (*TYPE_nacl_getgid) (void);
typedef int (*TYPE_nacl_getegid) (void);
typedef int (*TYPE_nacl_chdir) (const char* pathname);
typedef int (*TYPE_nacl_chmod) (const char* pathname, mode_t mode);
typedef int (*TYPE_nacl_fchmod) (int fd, mode_t mode);
typedef int (*TYPE_nacl_mkdir) (const char* pathname, mode_t mode);
typedef int (*TYPE_nacl_rmdir) (const char* pathname);

typedef int (*TYPE_nacl_send) (int sockfd, size_t len, int flags, const void *buf);
typedef int (*TYPE_nacl_sendto) (int sockfd, const void *buf, size_t len, int flags,
                                     const struct sockaddr *dest_addr, socklen_t addrlen);
typedef int (*TYPE_nacl_recv) (int sockfd, size_t len, int flags, void *buf);
typedef int (*TYPE_nacl_recvfrom) (int sockfd, void* buf, size_t len, int flags,
                                   struct sockaddr *src_addr, socklen_t* addrlen);
typedef int (*TYPE_nacl_imc_accept) (int d);
typedef int (*TYPE_nacl_imc_connect) (int d);
typedef int (*TYPE_nacl_accept) (int sockfd, struct sockaddr *addr, socklen_t addrlen);
typedef int (*TYPE_nacl_connect) (int sockfd, socklen_t addrlen, const struct sockaddr *src_addr);
typedef int (*TYPE_nacl_imc_makeboundsock) (int *dp);
typedef int (*TYPE_nacl_imc_socketpair) (int *d2);
typedef int (*TYPE_nacl_socketpair) (int domain, int type, int protocol, int *fds);
typedef int (*TYPE_nacl_imc_mem_obj_create) (size_t nbytes);

typedef int (*TYPE_nacl_shmget) (key_t key, size_t size, int shmflg);
typedef void *(*TYPE_nacl_shmat) (int shmid, void *shmaddr, int shmflg);
typedef int (*TYPE_nacl_shmdt) (void *shmaddr);
typedef int (*TYPE_nacl_shmctl) (int shmid, int cmd, struct nacl_abi_shmid_ds *buf);

typedef void *(*TYPE_nacl_mmap) (void *start, size_t length,
                                 int prot, int flags, int desc,
                                 nacl_abi_off_t *offset);

typedef int (*TYPE_nacl_munmap) (void *start, size_t length);

typedef int (*TYPE_nacl_mprotect) (void *addr, size_t length, int prot);

typedef void (*TYPE_nacl_thread_exit) (int32_t *stack_flag);
typedef int (*TYPE_nacl_thread_create) (void *start_user_address,
                                        void *stack,
                                        void *thread_ptr,
                                        void *second_thread_ptr);
typedef int (*TYPE_nacl_thread_nice) (const int nice);

typedef int (*TYPE_nacl_mutex_destroy) (int mutex);
typedef int (*TYPE_nacl_mutex_create) (void);
typedef int (*TYPE_nacl_mutex_lock) (int mutex);
typedef int (*TYPE_nacl_mutex_unlock) (int mutex);
typedef int (*TYPE_nacl_mutex_trylock) (int mutex);
typedef int (*TYPE_nacl_cond_create) (void);
typedef int (*TYPE_nacl_cond_wait) (int cv, int mutex);
typedef int (*TYPE_nacl_cond_signal) (int cv);
typedef int (*TYPE_nacl_cond_broadcast) (int cv);
typedef int (*TYPE_nacl_cond_destroy) (int cv);
typedef int (*TYPE_nacl_cond_timed_wait_abs) (int condvar,
                                              int mutex,
                                              const struct timespec *abstime);
typedef int (*TYPE_nacl_sem_create) (int32_t value);
typedef int (*TYPE_nacl_sem_wait) (int sem);
typedef int (*TYPE_nacl_sem_post) (int sem);

typedef int (*TYPE_nacl_getdents) (int desc, void *dirp, size_t count);
typedef int (*TYPE_nacl_gettimeofday) (struct timeval *tv, void *tz);
typedef int (*TYPE_nacl_sched_yield) (void);
typedef int (*TYPE_nacl_sysconf) (int name, int *res);
typedef void *(*TYPE_nacl_sysbrk) (void *p);
typedef pid_t (*TYPE_nacl_getpid) (void);
typedef pid_t (*TYPE_nacl_getppid) (void);
typedef clock_t (*TYPE_nacl_clock) (void);
typedef int (*TYPE_nacl_nanosleep) (const struct timespec *req,
                                    struct timespec *rem);
typedef int (*TYPE_nacl_clock_getres) (clockid_t clk_id,
                                       struct timespec *res);
typedef int (*TYPE_nacl_clock_gettime) (clockid_t clk_id,
                                        struct timespec *tp);
typedef int (*TYPE_nacl_shutdown) (int sockfd, int how);

/* Don't use __attribute__((noreturn)) on this because we want the
   wrapper to handle it if the syscall does happen to return. */
typedef void (*TYPE_nacl_exit) (int status);
typedef void (*TYPE_nacl_null) (void);
typedef int (*TYPE_nacl_tls_init) (void *tdb);
typedef void *(*TYPE_nacl_tls_get) (void);
typedef int (*TYPE_nacl_second_tls_set) (void *new_value);
typedef void *(*TYPE_nacl_second_tls_get) (void);
typedef int (*TYPE_nacl_srpc_get_fd) (void);
typedef int (*TYPE_nacl_dyncode_create) (void *dest, const void *src,
                                       size_t size);
typedef int (*TYPE_nacl_dyncode_modify) (void *dest, const void *src,
                                       size_t size);
typedef int (*TYPE_nacl_dyncode_delete) (void *dest, size_t size);

typedef int (*TYPE_nacl_lind_api) (uint32_t callNum, uint32_t inNum, void* inArgs, uint32_t outNum, void* outArgs);

typedef int (*TYPE_nacl_fork) (void);
typedef int (*TYPE_nacl_execve) (const char* path, const char* argv, const char* envp);
typedef int (*TYPE_nacl_execv) (const char* path, const char* argv);
typedef int (*TYPE_nacl_pipe) (int *pipedes);
typedef int (*TYPE_nacl_pipe2) (int *pipedes, int flags);
typedef int (*TYPE_nacl_waitpid) (int pid, int *stat_loc, int options);
typedef int (*TYPE_nacl_wait) (int *stat_loc);
typedef int (*TYPE_nacl_wait4) (pid_t pid, int *wstatus, int options, struct rusage *rusage);
typedef int (*TYPE_nacl_getcwd) (char* buf, size_t size);
typedef int (*TYPE_nacl_gethostname) (char *name, size_t len);
typedef int (*TYPE_nacl_pread) (int desc, void *buf, size_t count, off_t offset);
typedef int (*TYPE_nacl_pwrite) (int desc, const void *buf, size_t count, off_t offset);
typedef int (*TYPE_nacl_socket) (int domain, int type, int protocol);
typedef int (*TYPE_nacl_flock) (int fd, int operation);
typedef int (*TYPE_nacl_getsockopt) (int sockfd, int level, int optname,
                                     void *optval, socklen_t *optlen);
typedef int (*TYPE_nacl_setsockopt) (int sockfd, int level, int optname,
                                     const void *optval, socklen_t optlen);
typedef int (*TYPE_nacl_getsockname) (int sockfd, struct sockaddr * addr, socklen_t *addrlen);
typedef int (*TYPE_nacl_getpeername) (int sockfd, struct sockaddr * addr, socklen_t *addrlen);
typedef int (*TYPE_nacl_getifaddrs) (char *buf, size_t len);
typedef int (*TYPE_nacl_bind) (int sockfd, socklen_t addrlen, const struct sockaddr *addr);
typedef int (*TYPE_nacl_listen) (int sockfd, int backlog);
typedef int (*TYPE_nacl_fcntl_get) (int fd, int cmd);
typedef int (*TYPE_nacl_fcntl_set) (int fd, int cmd, long set_op);
typedef int (*TYPE_nacl_ioctl) (int fd, unsigned long request, void* arg_ptr);
typedef int (*TYPE_nacl_poll) (struct pollfd *fds, nfds_t nfds, int timeout);
typedef int (*TYPE_nacl_select) (int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, const struct timeval *timeout);
typedef int (*TYPE_nacl_epoll_create) (int size);
typedef int (*TYPE_nacl_epoll_ctl) (int epfd, int op, int fd, struct epoll_event *event);
typedef int (*TYPE_nacl_epoll_wait) (int epfd, struct epoll_event *events, int maxevents, int timeout);
typedef int (*TYPE_nacl_truncate) (const char *path, off_t length);
typedef int (*TYPE_nacl_ftruncate) (int fd, off_t length);

typedef int (*TYPE_nacl_sigaction) (int sig, const struct nacl_abi_sigaction *nacl_act, struct nacl_abi_sigaction *nacl_ocat);
typedef int (*TYPE_nacl_kill) (pid_t pid, int sig);
typedef int (*TYPE_nacl_sigprocmask) (int how, const uint64_t *nacl_set, uint64_t *nacl_oldset);

#endif

#ifndef _NACL_SYSDEP_H
#define _NACL_SYSDEP_H 1

#if !defined(__ASSEMBLER__)
#include <futex_emulation.h>
#include <irt_syscalls.h>
#include <lowlevellock.h>
#include <string.h>

/* Implementation of all syscalls for use in platform- and OS- independent code
   as inline functions.  Each function translates the syscall arguments into IRT
   arguments and allows to intercept each call in user code.
   TODO(khim): implement the interception logic.  */

# define log_unimplemented(x) //no actual logging done, this is because we don't really care about logging here beyond returning ENOSYS

# define INTERNAL_SYSCALL(name, err, nr, args...) \
  INTERNAL_SYSCALL_ ## name ## _ ## nr (&err , ## args)

# define INTERNAL_SYSCALL_NCS(name, err, nr, args...) \
  INTERNAL_SYSCALL_NCS_ ## nr (name, &err , ## args)

__extern_always_inline int
INTERNAL_SYSCALL_NCS_3 (int syscall_nr, int *err, int id1, int id2, int id3)
{
  *err = (38 /* ENOSYS */);
  return 0;
}

# ifdef __i386__
#  define INTERNAL_SYSCALL_chown_3	INTERNAL_SYSCALL_chown32_3
#  define INTERNAL_SYSCALL_fchown_3	INTERNAL_SYSCALL_fchown32_3
#  define INTERNAL_SYSCALL_getegid_0	INTERNAL_SYSCALL_getegid32_0
#  define INTERNAL_SYSCALL_geteuid_0	INTERNAL_SYSCALL_geteuid32_0
#  define INTERNAL_SYSCALL_getgid_0	INTERNAL_SYSCALL_getgid32_0
#  define INTERNAL_SYSCALL_getgroups_2	INTERNAL_SYSCALL_getgroups32_2
#  define INTERNAL_SYSCALL_getresgid_3	INTERNAL_SYSCALL_getresgid32_3
#  define INTERNAL_SYSCALL_getresuid_3	INTERNAL_SYSCALL_getresuid32_3
#  define INTERNAL_SYSCALL_getuid_0	INTERNAL_SYSCALL_getuid32_0
#  define INTERNAL_SYSCALL_lchown_3	INTERNAL_SYSCALL_lchown32_3
#  define INTERNAL_SYSCALL_setfsgid_1	INTERNAL_SYSCALL_setfsgid32_1
#  define INTERNAL_SYSCALL_setfsuid_1	INTERNAL_SYSCALL_setfsuid32_1
#  define INTERNAL_SYSCALL_setgid_1	INTERNAL_SYSCALL_setgid32_1
#  define INTERNAL_SYSCALL_setgroups_2	INTERNAL_SYSCALL_setgroups32_2
#  define INTERNAL_SYSCALL_setregid_2	INTERNAL_SYSCALL_setregid32_2
#  define INTERNAL_SYSCALL_setresgid_3	INTERNAL_SYSCALL_setresgid32_3
#  define INTERNAL_SYSCALL_setresuid_3	INTERNAL_SYSCALL_setresuid32_3
#  define INTERNAL_SYSCALL_setreuid_2	INTERNAL_SYSCALL_setreuid32_2
#  define INTERNAL_SYSCALL_setuid_1	INTERNAL_SYSCALL_setuid32_1
# endif

__extern_always_inline int
INTERNAL_SYSCALL_access_2 (int *err, const char *pathname, int mode)
{
  log_unimplemented("access unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_acct_1 (int *err, const char *filename)
{
  log_unimplemented("acct unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_adjtimex_1 (int *err, struct timex *buf)
{
  log_unimplemented("adjtimex unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_arch_prctl_2 (int *err, int code,
			    union __attribute__ ((__transparent_union__))
			    {
			      long *parg;
			      long larg;
			      int iarg;
			    } addr)
{
  log_unimplemented("arch_prctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_bdflush_2 (int *err, int func,
			    union __attribute__ ((__transparent_union__))
			    {
			      long *parg;
			      long larg;
			      int iarg;
			    } data)
{
  log_unimplemented("bdflush unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

struct __user_cap_header_struct;
struct __user_cap_data_struct;
__extern_always_inline int
INTERNAL_SYSCALL_capget_2 (int *err, struct __user_cap_header_struct *hdrp,
			   struct __user_cap_data_struct *datap)
{
  log_unimplemented("capget unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_capset_2 (int *err, struct __user_cap_header_struct *hdrp,
			   const struct __user_cap_data_struct *datap)
{
  log_unimplemented("capset unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_chdir_1 (int *err, const char *path)
{
  int rv = __nacl_irt_chdir (path);
  if(rv < 0) {
    *err = -rv;
    return -1;
  }
  return rv;
}

__extern_always_inline int
INTERNAL_SYSCALL_chmod_2 (int *err, const char *path, mode_t mode)
{
  int rv = __nacl_irt_chmod (path, mode);
  if(rv < 0) {
    *err = -rv;
    return -1;
  }
  return rv;
}

__extern_always_inline int
INTERNAL_SYSCALL_chown_3 (int *err, const char *path,
			  uid_t owner, gid_t group)
{
  // LIND: chown is faked since we only have one user
  *err = 0;
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_chroot_1 (int *err, const char *path)
{
  log_unimplemented("chroot unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_clock_getres_2 (int *err, clockid_t clk_id,
				 struct timespec *res)
{
  log_unimplemented("clock_getres unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_clock_gettime_2 (int *err, clockid_t clk_id,
				  struct timespec *tp)
{
  log_unimplemented("clock_gettime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_clock_nanosleep_4 (int *err, clockid_t clock_id, int flags,
				    const struct timespec *request,
				    struct timespec *remain)
{
  log_unimplemented("clock_nanosleep unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_clock_settime_2 (int *err, clockid_t clk_id,
				  const struct timespec *tp)
{
  log_unimplemented("clock_settime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

struct pthread;
__extern_always_inline pid_t
INTERNAL_SYSCALL_clone_7 (int *err, int (*fn)(void *), void *child_stack,
			  int flags, void *arg, pid_t *ptid,
			  struct pthread *tls, pid_t *ctid)
{
  log_unimplemented("clone unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline pid_t
INTERNAL_SYSCALL_clone_4(int *err, int (*fn)(void *), void *child_stack,
			  int flags, void *arg)
{
  return INTERNAL_SYSCALL_clone_7 (err, fn, child_stack, flags, arg,
				   NULL, NULL, NULL);
}

__extern_always_inline int
INTERNAL_SYSCALL_close_1 (int *err, unsigned int fd)
{
  *err = __nacl_irt_close(fd);
  return 0;
}

__extern_always_inline __caddr_t
INTERNAL_SYSCALL_create_module_2 (int *err, const char *name, size_t size)
{
  log_unimplemented("create_module unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_delete_module_4 (int *err, const char *name_user,
				  unsigned int flags,
				  const struct timespec *rqtp,
				  struct timespec *rmtp)
{
  log_unimplemented("delete_module unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_epoll_create_1 (int *err, int size)
{
  int fd;
  fd = __nacl_irt_epoll_create (size);
  if(fd < 0) {
    *err = -fd;
    return -1;
  }
  return fd;
}

__extern_always_inline int
INTERNAL_SYSCALL_epoll_create1_1 (int *err, int flags)
{
  int fd;
  *err = __nacl_irt_epoll_create1 (flags, &fd);
  return fd;
}

__extern_always_inline int
INTERNAL_SYSCALL_epoll_ctl_4 (int *err, int epfd, int op, int fd,
			      struct epoll_event *event)
{
  int ret = __nacl_irt_epoll_ctl (epfd, op, fd, event);
  if(ret < 0) {
    *err = -ret;
    return -1;
  }
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_epoll_pwait_6 (int *err, int epfd, struct epoll_event *events,
				int maxevents, int timeout,
				const sigset_t *sigmask, size_t sigset_size)
{
  int count;
  *err = __nacl_irt_epoll_pwait (epfd, events, maxevents, timeout, sigmask,
                                 sigset_size, &count);
  return count;
}

__extern_always_inline int
INTERNAL_SYSCALL_execve_3 (int *err, const char *filename, char *const argv[],
			   char *const envp[])
{
  log_unimplemented("execve unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_epoll_wait_4 (int *err, int epfd, struct epoll_event *events,
			       int maxevents, int timeout)
{
  int ret = __nacl_irt_epoll_wait (epfd, events, maxevents, timeout);
  if(ret < 0) {
    *err = -ret;
    return -1;
  }
  return ret;
}

__extern_always_inline int
INTERNAL_SYSCALL_eventfd2_2 (int *err, unsigned int initval, int flags)
{
  log_unimplemented("eventfd2 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_eventfd_1 (int *err, unsigned int initval)
{
  return INTERNAL_SYSCALL_eventfd2_2 (err, initval, 0);
}

__extern_always_inline int
INTERNAL_SYSCALL_faccessat_3 (int *err, int dirfd, const char *pathname,
			      int mode)
{
  log_unimplemented("faccessat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fchdir_1 (int *err, int fd)
{
  int rv = __nacl_irt_fchdir (fd);
  if(rv < 0) {
    *err = -rv;
    return -1;
  }
  return rv;
}

__extern_always_inline int
INTERNAL_SYSCALL_fchmod_2 (int *err, int fd, mode_t mode)
{
  int rv = __nacl_irt_fchmod (fd, mode);
  if(rv < 0) {
    *err = -rv;
    return -1;
  }
  return rv;
}

__extern_always_inline int
INTERNAL_SYSCALL_fchmodat_3 (int *err, int dirfd, const char *pathname,
			     mode_t mode)
{
  log_unimplemented("fchmodat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fchown_3 (int *err, int fd,
			   uid_t owner, gid_t group)
{
  log_unimplemented("fchown unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fchownat_5 (int *err, int dirfd, const char *pathname,
			     uid_t owner, gid_t group, int flags)
{
  log_unimplemented("fchownat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fcntl_3 (int *err, int fd, int cmd, void *arg)
{
  log_unimplemented("fcntl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fcntl64_3 (int *err, int fd, int cmd,
			    union __attribute__ ((__transparent_union__))
			    {
			      unsigned long ularg;
			      long larg;
			      unsigned int uiarg;
			      int iarg;
			      void *parg;
			    } arg)
{
  log_unimplemented("fcntl64 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fdatasync_1 (int *err, int fd)
{
  log_unimplemented("fdatasync unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_flock_2 (int *err, int fd, int operation)
{
  log_unimplemented("flock unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fgetxattr_4 (int *err, int filedes, const char *name,
			      void *value, size_t size)
{
  log_unimplemented("fgetxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_flistxattr_3 (int *err, int filedes, char *list, size_t size)
{
  log_unimplemented("flistxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fremovexattr_2 (int *err, int filedes, const char *name)
{
  log_unimplemented("fremovexattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fsetxattr_5 (int *err, int filedes, const char *name,
			      const void *value, size_t size, int flags)
{
  log_unimplemented("fsetxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_fsync_1 (int *err, int fd)
{
  log_unimplemented("fsync unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__errordecl (__futex_emulation_unknown_operation,
	     "unknown futex operation or argument");

struct __attribute__ ((__packed__)) decoded_futex_operation
  {
    unsigned int operation	:7;
    unsigned int private	:1;
    unsigned int realtime	:1;
    unsigned int padding	:23;
};

union __attribute__ ((__transparent_union__)) encoded_futex_operation
  {
    unsigned int encoded_futex_operation;
    int const_futex_operation;
    struct decoded_futex_operation decoded_futex_operation;
  };

__extern_always_inline void
INTERNAL_SYSCALL_futex_2 (int *err,
			  union __attribute__ ((__transparent_union__))
			  {
			    volatile int *addr;
			    volatile unsigned int *uaddr;
			  } addr,
			  union encoded_futex_operation futex_operation)
{
  switch (futex_operation.decoded_futex_operation.operation)
    {
      case FUTEX_UNLOCK_PI:
	*err = (38 /* ENOSYS */);
	return;
      default:
	if (__builtin_constant_p (
	    futex_operation.decoded_futex_operation.operation))
	  __futex_emulation_unknown_operation ();
	*err = 0;
    }
}

__extern_always_inline unsigned int
INTERNAL_SYSCALL_futex_3 (int *err,
			  union __attribute__ ((__transparent_union__))
			  {
			    volatile int *addr;
			    volatile unsigned int *uaddr;
			  } addr,
			  union encoded_futex_operation futex_operation,
			  int val)
{
  int count;
  switch (futex_operation.decoded_futex_operation.operation)
    {
      case FUTEX_WAKE:
	*err = -__nacl_futex_wake (addr.addr, val, __FUTEX_BITSET_MATCH_ANY,
				   &count);
	return count;
      default:
	if (__builtin_constant_p (
	    futex_operation.decoded_futex_operation.operation))
	  __futex_emulation_unknown_operation ();
	*err = 0;
    }
    return 0;
}

__extern_always_inline unsigned int
INTERNAL_SYSCALL_futex_4 (int *err,
			  union __attribute__ ((__transparent_union__))
			  {
			    volatile int *addr;
			    volatile unsigned int *uaddr;
			  } addr,
			  union encoded_futex_operation futex_operation,
			  int val1,
			  /* We need to accept 0 here.  May be better to
			     replace 0 with NULL in NPTL code?  */
			  union __attribute__ ((__transparent_union__))
			    {
			      const struct timespec *timeout;
			      int null_timeout;
			    } val2)
{
  switch (futex_operation.decoded_futex_operation.operation)
    {
      case FUTEX_WAIT_ABS:
	*err = -__nacl_futex_wait (addr.addr, val1, __FUTEX_BITSET_MATCH_ANY,
				   val2.timeout);
	return 0;
      /* TODO(khim): hook up PI-locks to some IRT-handleable functions.  */
      case FUTEX_LOCK_PI:
      case FUTEX_UNLOCK_PI:
      case FUTEX_TRYLOCK_PI:
	*err = (38 /* ENOSYS */);
	return 0;
      default:
	if (__builtin_constant_p (
	    futex_operation.decoded_futex_operation.operation))
	  __futex_emulation_unknown_operation ();
	*err = 0;
    }
    return 0;
}

__extern_always_inline unsigned int
INTERNAL_SYSCALL_futex_6 (int *err,
			  union __attribute__ ((__transparent_union__))
			  {
			    volatile int *addr;
			    volatile unsigned int *uaddr;
			  } addr1,
			  union encoded_futex_operation futex_operation,
			  int val1,
			  int val2,
			  union __attribute__ ((__transparent_union__))
			  {
			    volatile int *addr;
			    volatile unsigned int *uaddr;
			  } addr2,
			  int val3)
{
  int count;
  switch (futex_operation.decoded_futex_operation.operation)
    {
      case FUTEX_WAKE_OP:
	*err = -__nacl_futex_wake_op (addr1.addr, addr2.addr,
				      val1, val2, val3, &count);
	return count;
      case FUTEX_CMP_REQUEUE:
	*err = -__nacl_futex_cmp_requeue (addr1.addr, addr2.addr,
					  val1, val2, val3, &count);
	return count;
      default:
	if (__builtin_constant_p (
	    futex_operation.decoded_futex_operation.operation))
	  __futex_emulation_unknown_operation ();
	*err = 0;
    }
    return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_futimesat_3 (int *err, int dirfd, const char *pathname,
			      const struct timeval times[2])
{
  log_unimplemented("futimesat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

struct kernel_sym;
__extern_always_inline ssize_t
INTERNAL_SYSCALL_get_kernel_syms_1 (int *err, struct kernel_sym *table)
{
  log_unimplemented("get_kernel_syms unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getcpu_3 (int *err, unsigned *cpu, unsigned *node,
			   struct getcpu_cache *tcache)
{
  log_unimplemented("getcpu unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline gid_t
INTERNAL_SYSCALL_getegid_0 (int *err)
{
  log_unimplemented("getegid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline uid_t
INTERNAL_SYSCALL_geteuid_0 (int *err)
{
  log_unimplemented("geteuid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline gid_t
INTERNAL_SYSCALL_getgid_0 (int *err)
{
  log_unimplemented("getgid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getgroups_2 (int *err, int size, gid_t *list)
{
  log_unimplemented("getgroups unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getitimer_2 (int *err, int which, struct itimerval *curr_value)
{
  log_unimplemented("getitimer unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getmsg_4 (int *err, int fildes, const struct strbuf *ctlptr,
			   const struct strbuf *dataptr, int *pflags)
{
  log_unimplemented("getmsg unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline pid_t
INTERNAL_SYSCALL_getpgid_1 (int *err, pid_t pid)
{
  log_unimplemented("getpgid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline pid_t
INTERNAL_SYSCALL_getpgrp_0 (int *err)
{
  log_unimplemented("getpgrp unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getpmsg_5 (int *err, int fildes, const struct strbuf *ctlptr,
			   const struct strbuf *dataptr, int *pband, int *pflags)
{
  log_unimplemented("getpmsg unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

/* The return value of getpriority syscall is biased by this value
   to avoid returning negative values.  */
__extern_always_inline int
INTERNAL_SYSCALL_getpriority_2 (int *err, int which, int who)
{
  log_unimplemented("getpriority unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getresgid_3 (int *err, gid_t *rgid, gid_t *egid, gid_t *sgid)
{
  log_unimplemented("getresgid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getresuid_3 (int *err, uid_t *ruid, uid_t *euid, uid_t *ugid)
{
  log_unimplemented("getresuid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getrusage_2 (int *err, int who, struct rusage *usage)
{
  log_unimplemented("getrusage unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline pid_t
INTERNAL_SYSCALL_getsid_1 (int *err, pid_t pid)
{
  log_unimplemented("getsid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline uid_t
INTERNAL_SYSCALL_getuid_0 (int *err)
{
  log_unimplemented("getuid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getxattr_4 (int *err, const char *path, const char *name,
			     void *value, size_t size)
{
  log_unimplemented("getxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_open_3 (int *err, const char *pathname, int flags, mode_t mode)
{
  int newfd;
  newfd = __nacl_irt_open (pathname, flags, mode);
  if (newfd < 0) {
    *err = -newfd;
    return -1;
  } else { return newfd; }
}

__extern_always_inline int
INTERNAL_SYSCALL_openat_4 (int *err, int dirfd, const char *pathname,
			   int flags, mode_t mode)
{
  log_unimplemented("openat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_init_module_3 (int *err, void *umod, unsigned long len,
				const char *uargs)
{
  log_unimplemented("init_module unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_inotify_add_watch_3 (int *err, int fd, const char *pathname,
				      uint32_t mask)
{
  log_unimplemented("inotify_add_watch unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_inotify_init1_1 (int *err, int flags)
{
  log_unimplemented("inotify_init1 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_inotify_init_0 (int * err)
{
  return INTERNAL_SYSCALL_inotify_init1_1 (err, 0);
}

__extern_always_inline int
INTERNAL_SYSCALL_inotify_rm_watch_2 (int *err, int fd, uint32_t wd)
{
  log_unimplemented("inotify_rm_watch unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_ioctl_3 (int *err, int d, int request,
			  union __attribute__ ((__transparent_union__))
			  {
			    unsigned long ularg;
			    long larg;
			    unsigned int uiarg;
			    int iarg;
			    void *parg;
			  } arg)
{
  log_unimplemented("ioctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_ioperm_3 (int *err, unsigned long from, unsigned long num,
			   int turn_on)
{
  log_unimplemented("ioperm unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_iopl_1 (int *err, int level)
{
  log_unimplemented("iopl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_ipc_6 (int *err, unsigned int call, int first, int second,
			int third, void *ptr, long fifth)
{
  log_unimplemented("ipc unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_ipc_5 (int *err, unsigned int call, int first, int second,
			int third, void *ptr)
{
  return INTERNAL_SYSCALL_ipc_6 (err, call, first, second, third, ptr, 0);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_kill_2 (int *err, pid_t pid, int sig)
{
  log_unimplemented("kill unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_laccess_2 (int *err, const char *pathname, int mode)
{
  log_unimplemented("laccess unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_lchown_3 (int *err, const char *path,
			   uid_t owner, gid_t group)
{
  log_unimplemented("lchown unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_lgetxattr_4 (int *err, const char *path, const char *name,
			      void *value, size_t size)
{
  log_unimplemented("lgetxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_link_2 (int *err, const char *oldpath, const char *newpath)
{
  log_unimplemented("link unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_linkat_5 (int *err, int olddfd, const char *oldname,
			   int newdfd, const char *newname, int flags)
{
  log_unimplemented("linkat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_listxattr_3 (int *err, const char *path, char *list,
			      size_t size)
{
  log_unimplemented("listxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_llistxattr_3 (int *err, const char *path, char *list,
			       size_t size)
{
  log_unimplemented("llistxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_lremovexattr_2 (int *err, const char *path, const char *name)
{
  log_unimplemented("lremovexattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_lsetxattr_5 (int *err, const char *path, const char *name,
			      const void *value, size_t size, int flags)
{
  log_unimplemented("lsetxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_madvise_3 (int *err, void *addr, size_t length, int advice)
{
  log_unimplemented("madvise unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mincore_3 (int *err, void *addr, size_t length,
			    unsigned char *vec)
{
  log_unimplemented("mincore unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mkdir_2 (int *err, const char *pathname, mode_t mode)
{
  int ret;
  ret = __nacl_irt_mkdir (pathname, mode);
  if(ret < 0) {
    *err = -ret;
    return -1;
  }
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mkdirat_3 (int *err, int dirfd, const char *pathname,
			    mode_t mode)
{
  log_unimplemented("mkdirat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mknod_3 (int *err, const char *pathname,
			  mode_t mode, dev_t dev)
{
	  log_unimplemented("mknod unimplemented");
  	*err = (38 /* ENOSYS */);
  	return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mknodat_4 (int *err, int dirfd, const char *pathname,
			    mode_t mode, dev_t dev)
{
  log_unimplemented("mknodat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mlock_2 (int *err, const void *addr, size_t len)
{
  log_unimplemented("mlock unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mlockall_1 (int *err, int flags)
{
  log_unimplemented("mlockall unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_modify_ldt_3 (int *err, int func, void *ptr,
			       unsigned long bytecount)
{
  log_unimplemented("modify_ldt unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mprotect_3 (int *err, void *addr, size_t len, int prot)
{
  *err = __nacl_irt_mprotect (addr, len, prot);
  return 0;
}

#if !defined (_LIBC) || defined(IS_IN_librt)
__extern_always_inline mqd_t
INTERNAL_SYSCALL_mq_getsetattr_3 (int *err, mqd_t mqdes,
				  struct mq_attr *newattr,
				  struct mq_attr *oldattr)
{
  log_unimplemented("mq_getsetattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline mqd_t
INTERNAL_SYSCALL_mq_open_4 (int *err, const char *name, int oflag, mode_t mode,
			    struct mq_attr *attr)
{
  log_unimplemented("mq_open unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mq_notify_2 (int *err, mqd_t mqdes,
			      const struct sigevent *notification)
{
  log_unimplemented("mq_notify unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_mq_timedreceive_5 (int *err, mqd_t mqdes, char *msg_ptr,
				    size_t msg_len, unsigned *msg_prio,
				    const struct timespec *abs_timeout)
{
  log_unimplemented("mq_timedreceive unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline mqd_t
INTERNAL_SYSCALL_mq_timedsend_5 (int *err, mqd_t mqdes, const char *msg_ptr,
				 size_t msg_len, unsigned msg_prio,
				 const struct timespec *abs_timeout)
{
  log_unimplemented("mq_timedsend unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_mq_unlink_1 (int *err, const char *name)
{
  log_unimplemented("mq_unlink unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}
#endif

__extern_always_inline int
INTERNAL_SYSCALL_mount_5 (int *err, const char *source, const char *target,
			  const char *filesystemtype, unsigned long mountflags,
			  const void *data)
{
  log_unimplemented("mount unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline void*
INTERNAL_SYSCALL_mremap_5 (int *err, void *old_address, size_t old_size,
			   size_t new_size, int flags, void *new_address)
{
  log_unimplemented("mremap unimplemented");
  *err = (38 /* ENOSYS */);
  return NULL;
}

__extern_always_inline int
INTERNAL_SYSCALL_msgctl_3 (int *err, int msqid, int cmd, struct msqid_ds *buf)
{
  log_unimplemented("msgctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_msgget_2 (int *err, key_t key, int msgflg)
{
  log_unimplemented("msgget unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_msgrcv_5 (int *err, int msqid, void *msgp, size_t msgsz,
			   long msgtyp, int msgflg)
{
  log_unimplemented("msgrcv unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_msgsnd_4 (int *err, int msqid, const void *msgp, size_t msgsz,
			   int msgflg)
{
  log_unimplemented("msgsnd unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_msync_3 (int *err, void *addr, size_t length, int flags)
{
  log_unimplemented("msync unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_munlock_2 (int *err, const void *addr, size_t len)
{
  log_unimplemented("munlock unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_munlockall_0 (int *err)
{
  log_unimplemented("munlockall unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_munmap_2 (int *err, void *addr, size_t length)
{
  *err = __nacl_irt_munmap(addr, length);
  return 0;
}

struct nfsctl_arg;
union nfsctl_res;
__extern_always_inline int
INTERNAL_SYSCALL_nfsservctl_3 (int *err, int cmd, struct nfsctl_arg *argp,
			       union nfsctl_res *resp)
{
  log_unimplemented("nfsservctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_quotactl_4 (int *err, int cmd, const char *special, int id,
			     __caddr_t addr)
{
  log_unimplemented("quotactl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_query_module_5 (int *err, const char *name, int which,
				 void *buf, size_t bufsize, size_t *ret)
{
  log_unimplemented("query_module unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_pause_0 (int *err)
{
  log_unimplemented("pause unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline long
INTERNAL_SYSCALL_personality_1 (int *err, unsigned long persona)
{
  log_unimplemented("personality unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_pipe2_2 (int *err, int pipefd[2], int flags)
{
  log_unimplemented("pipe2 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_pipe_1 (int *err, int pipefd[2])
{
  return INTERNAL_SYSCALL_pipe2_2 (err, pipefd, 0);
}

__extern_always_inline int
INTERNAL_SYSCALL_pivot_root_2 (int *err, const char *new_root,
			       const char *put_old)
{
  log_unimplemented("pivot_root unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_ppoll_5 (int *err, struct pollfd *fds, nfds_t nfds,
			  const struct timespec *timeout,
			  const sigset_t *sigmask, size_t sigset_size)
{
  int count;
  *err = __nacl_irt_ppoll (fds, nfds, timeout, sigmask, sigset_size, &count);
  return count;
}

__extern_always_inline int
INTERNAL_SYSCALL_prctl_5 (int *err, int option, unsigned long arg2,
			  unsigned long arg3, unsigned long arg4,
			  unsigned long arg5)
{
  log_unimplemented("prctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_pselect6_6 (int *err, int nfds, fd_set *readfds,
                             fd_set *writefds, fd_set *exceptfds,
                             const struct timeval *timeout,
                             void *sigmask)
{
  int count;
  *err = __nacl_irt_pselect (nfds, readfds, writefds, exceptfds, timeout,
                             sigmask, &count);
  return count;
}

__extern_always_inline long
INTERNAL_SYSCALL_ptrace_4 (int *err, enum __ptrace_request request, pid_t pid,
			   void *addr, void *data)
{
  log_unimplemented("ptrace unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_putmsg_4 (int *err, int fildes, const struct strbuf *ctlptr,
			   const struct strbuf *dataptr, int flags)
{
  log_unimplemented("putmsg unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_putpmsg_5 (int *err, int fildes, const struct strbuf *ctlptr,
			   const struct strbuf *dataptr, int band, int flags)
{
  log_unimplemented("putpmsg unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_readahead_3 (int *err, int fd, __off64_t offset, size_t count)
{
  log_unimplemented("readahead unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_readahead_4 (int *err, int fd,
			      __LONG_LONG_PAIR(long offset_high,
					       long offset_low), size_t count)
{
  __off64_t offset = ((__off64_t)offset_high) << 32 | offset_low;
  return INTERNAL_SYSCALL_readahead_3 (err, fd, offset, count);
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_readv_3 (int *err, int fd, const
			  struct iovec *iov, int iovcnt)
{
  log_unimplemented("readv unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_readlink_3 (int *err, const char *path,
			     char *buf, size_t bufsiz)
{
  log_unimplemented("readlink unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_readlinkat_4 (int *err, int dirfd, const char *pathname,
			       char *buf, size_t bufsiz)
{
  log_unimplemented("readlinkat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_reboot_4 (int *err, int magic1, int magic2, int cmd, void *arg)
{
  log_unimplemented("reboot unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_reboot_3 (int *err, int magic1, int magic2, int howto)
{
  return INTERNAL_SYSCALL_reboot_4 (err, magic1, magic2, howto, NULL);
}

__extern_always_inline int
INTERNAL_SYSCALL_remap_file_pages_5 (int *err, void *addr, size_t size,
				     int prot, ssize_t pgoff, int flags)
{
  log_unimplemented("remap_file_pages unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_removexattr_2 (int *err, const char *path, const char *name)
{
  log_unimplemented("removexattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_rename_2 (int *err, const char *oldpath, const char *newpath)
{
  log_unimplemented("rename unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_renameat_4 (int *err, int olddfd, const char *oldname,
			     int newdfd, const char *newname)
{
  log_unimplemented("renameat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_rmdir_1 (int *err, const char *pathname)
{
  int ret;
  ret = __nacl_irt_rmdir (pathname);
  if(ret < 0) {
    *err = -ret;
    return -1;
  }
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_rt_sigpending_2 (int *err, sigset_t *set, size_t sigsetsize)
{
  log_unimplemented("rt_sigpending unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_rt_sigprocmask_4 (int *err, int how, const sigset_t *set,
				   sigset_t *oldset, size_t sigsetsize)
{
  log_unimplemented("rt_sigprocmask unimplemented");
  *err = (0 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_rt_sigqueueinfo_3 (int *err, pid_t pid, int sig,
				    siginfo_t *info)
{
  log_unimplemented("rt_sigqueueinfo unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_rt_sigsuspend_2 (int *err, const sigset_t *mask,
				  size_t sigsetsize)
{
  log_unimplemented("rt_sigsuspend unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_rt_sigtimedwait_4 (int *err, const sigset_t *set,
				    siginfo_t *info,
				    const struct timespec *timeout,
				    size_t sigsetsize)
{
  log_unimplemented("rt_sigtimedwait unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_getaffinity_3 (int *err, pid_t pid, size_t cpusetsize,
				      cpu_set_t *mask)
{
  log_unimplemented("sched_getaffinity unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_getparam_2 (int *err, pid_t pid,
				   struct sched_param *param)
{
  log_unimplemented("sched_getparam unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_get_priority_min_1 (int *err, int policy)
{
  log_unimplemented("sched_get_priority_min unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_get_priority_max_1 (int *err, int policy)
{
  log_unimplemented("sched_get_priority_max unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_getscheduler_1 (int *err, pid_t pid)
{
  log_unimplemented("sched_getscheduler unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_rr_get_interval_2 (int *err, pid_t pid,
					  struct timespec * tp)
{
  log_unimplemented("sched_rr_get_interval unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_setaffinity_3 (int *err, pid_t pid, size_t cpusetsize,
				      const cpu_set_t *mask)
{
  log_unimplemented("sched_setaffinity unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_setparam_2 (int *err, pid_t pid,
				   struct sched_param *param)
{
  log_unimplemented("sched_setparam unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sched_setscheduler_3 (int *err, pid_t pid, int policy,
				       const struct sched_param *param)
{
  log_unimplemented("sched_setscheduler unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_semctl_4 (int *err, int semid, int semnum, int cmd,
#ifdef _SEM_SEMUN_UNDEFINED
			   int semun)
#else
			   union semun semun)
#endif
{
  log_unimplemented("semctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_semget_3 (int *err, key_t key, int nsems, int semflg)
{
  log_unimplemented("semget unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_semtimedop_4 (int *err, int semid, struct sembuf *sops,
			       unsigned nsops, struct timespec *timeout)
{
  log_unimplemented("semtimedop unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_semop_3 (int *err, int semid, struct sembuf *sops,
			  unsigned nsops)
{
  return INTERNAL_SYSCALL_semtimedop_4 (err, semid, sops, nsops, NULL);
}

__extern_always_inline int
INTERNAL_SYSCALL_setdomainname_2 (int *err, const char *name, size_t len)
{
  log_unimplemented("setdomainname unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setfsgid_1 (int *err, gid_t gid)
{
  log_unimplemented("setfsgid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setfsuid_1 (int *err, uid_t uid)
{
  log_unimplemented("setfsuid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setgid_1 (int *err, gid_t gid)
{
  // LIND: setgid/uid are faked
  *err = 0;
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setgroups_2 (int *err, int size, const gid_t *list)
{
  log_unimplemented("setgroups unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sethostname_2 (int *err, const char *name, size_t len)
{
  log_unimplemented("sethostname unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setitimer_3 (int *err, int which,
			      const struct itimerval *new_value,
			      struct itimerval *old_value)
{
  log_unimplemented("setitimer unimplemented");
  *err = 0; // Lind fake setitimer
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setpgid_2 (int *err, pid_t pid, pid_t pgid)
{
  log_unimplemented("setpgid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setpriority_3 (int *err, int which, int who, int prio)
{
  log_unimplemented("setpriority unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setregid_2 (int *err, gid_t rgid, gid_t egid)
{
  log_unimplemented("setregid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setresgid_3 (int *err, gid_t rgid, gid_t egid, gid_t sgid)
{
  log_unimplemented("setresgid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setresuid_3 (int *err, uid_t ruid, uid_t euid, uid_t suid)
{
  log_unimplemented("setresuid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setreuid_2 (int *err, uid_t ruid, uid_t euid)
{
  log_unimplemented("setreuid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_settimeofday_2 (int *err, const struct timeval *tv,
				 const struct timezone *tz)
{
  log_unimplemented("settimeofday unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_set_robust_list_2 (int *err, struct robust_list_head *head,
				    size_t len)
{
  log_unimplemented("set_robust_list unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline pid_t
INTERNAL_SYSCALL_setsid_0 (int *err)
{
  log_unimplemented("setsid unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setuid_1 (int *err, uid_t uid)
{
  // LIND: setgid/uid are faked
  *err = 0;
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setxattr_5 (int *err, const char *path, const char *name,
			     const void *value, size_t size, int flags)
{
  log_unimplemented("setxattr unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline void*
INTERNAL_SYSCALL_shmat_3 (int *err, int shmid, const void *shmaddr, int shmflg)
{
  log_unimplemented("shmat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_shmctl_3 (int *err, int shmid, int cmd, struct shmid_ds *buf)
{
  log_unimplemented("shmctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_shmdt_1 (int *err, const void *shmaddr)
{
  log_unimplemented("shmdt unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_shmget_3 (int *err, key_t key, size_t size, int shmflg)
{
  log_unimplemented("shmget unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sigaltstack_2 (int *err, const stack_t *ss, stack_t *oss)
{
  log_unimplemented("sigaltstack unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_signalfd4_4 (int *err, int fd, const sigset_t *mask,
			      size_t sigsetsize, int flags)
{
  log_unimplemented("signalfd4 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_signalfd_3 (int *err, int fd, const sigset_t *mask,
			     size_t sigsetsize)
{
  return INTERNAL_SYSCALL_signalfd4_4 (err, fd, mask, sigsetsize, 0);
}

__extern_always_inline int
INTERNAL_SYSCALL_socket_3 (int *err, int domain, int type, int protocol)
{
  int sd;
  sd = __nacl_irt_socket (domain, type, protocol);
  if(sd < 0) {
    *err = -sd;
    return -1;
  } else { return sd; }
}

__extern_always_inline int
INTERNAL_SYSCALL_accept_3 (int *err, int sockfd, struct sockaddr* addr,
                           socklen_t* addr_len)
{
  int rv = __nacl_irt_accept (sockfd, addr, addr_len);
  if(rv < 0) {
    *err = -rv;
    return -1;
  }
  return rv;
}

__extern_always_inline int
INTERNAL_SYSCALL_bind_3 (int *err, int sockfd, struct sockaddr* addr,
                         socklen_t addr_len)
{
  int rv = __nacl_irt_bind (sockfd, addr, addr_len);
  if(rv < 0) {
    *err = -rv;
    return -1;
  } else { return 0; }
}

__extern_always_inline int
INTERNAL_SYSCALL_getpeername_3 (int *err, int sockfd, struct sockaddr* addr,
                                socklen_t* addr_len)
{
  int rv = __nacl_irt_getpeername (sockfd, addr, addr_len);
  if(rv < 0) {
    *err = -rv;
    return -1;
  }
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getsockname_3 (int *err, int sockfd, struct sockaddr* addr,
                                socklen_t* addr_len)
{
  int ret = __nacl_irt_getsockname (sockfd, addr, addr_len);
  if(ret < 0) {
    *err = -ret;
    return -1;
  }
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_getsockopt_5 (int *err, int sockfd, int level, int optname,
                               void *optval, socklen_t *optlen)
{
  int ret = __nacl_irt_getsockopt (sockfd, level, optname, optval, optlen);
  if(ret < 0) {
    *err = -ret;
    return -1;
  }
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_setsockopt_5 (int *err, int sockfd, int level, int optname,
                               const void *optval, socklen_t optlen)
{
  int ret = __nacl_irt_setsockopt (sockfd, level, optname, optval, optlen);
  if(ret < 0) {
    *err = -ret;
    return -1;
  }
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_listen_2 (int *err, int sockfd, int backlog)
{
  int rv = __nacl_irt_listen (sockfd, backlog);
  if( rv < 0 ){
    *err = -rv;
    return -1;
  } else { return 0; }
}

__extern_always_inline int
INTERNAL_SYSCALL_connect_3 (int *err, int sockfd, struct sockaddr* addr,
                            socklen_t addr_len)
{
  int rv = __nacl_irt_connect (sockfd, addr, addr_len);
  if(rv < 0) {
    *err = -rv;
    return -1;
  } else { return 0; }
}

__extern_always_inline int
INTERNAL_SYSCALL_socketpair_4 (int *err, int domain, int type, int protocol,
                             int sv[2])
{
  *err = __nacl_irt_socketpair (domain, type, protocol, sv);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_shutdown_2 (int *err, int sockfd, int how)
{
  *err = __nacl_irt_shutdown (sockfd, how);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_send_4 (int *err, int sockfd, const void *buf, size_t len, int flags)
{
  int ret = __nacl_irt_send (sockfd, buf, len, flags);
  if(ret < 0) {
    *err = -ret;
    return -1;
  }
  return ret;
}

__extern_always_inline int
INTERNAL_SYSCALL_sendto_6 (int *err, int sockfd, const void *buf, size_t len,
                           int flags, const struct sockaddr *dest_addr,
						   socklen_t addrlen)
{
  int ret = __nacl_irt_sendto (sockfd, buf, len, flags, dest_addr, addrlen);
  if(ret < 0) {
    *err = -ret;
    return -1;
  } else { return 0; }
}

__extern_always_inline int
INTERNAL_SYSCALL_recv_4 (int *err, int sockfd, void *buf, size_t len, int flags)
{
  int ret = __nacl_irt_recv (sockfd, buf, len, flags);
  if(ret < 0) {
    *err = -ret;
    return -1;
  }
  return ret;
}

__extern_always_inline int
INTERNAL_SYSCALL_recvfrom_6 (int *err, int sockfd, void *buf, size_t len, int flags,
                           struct sockaddr *dest_addr, socklen_t *addrlen)
{
  int ret;
  *err = __nacl_irt_recvfrom (sockfd, buf, len, flags, dest_addr, addrlen, &ret);
  return ret;
}

__extern_always_inline int
INTERNAL_SYSCALL_sendmsg_3 (int *err, int sockfd, const struct msghdr *msg, int flags)
{
  log_unimplemented("sendmsg unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_recvmsg_3 (int *err, int sockfd, struct msghdr *msg, int flags)
{
  log_unimplemented("recvmsg unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_splice_6 (int *err, int fd_in, loff_t *off_in, int fd_out,
			   loff_t *off_out, size_t len, unsigned int flags)
{
  log_unimplemented("splice unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_stime_1 (int *err, time_t *t)
{
  log_unimplemented("stime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_swapoff_1 (int *err, const char *path)
{
  log_unimplemented("swapoff unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_swapon_2 (int *err, const char *path, int swapflags)
{
  log_unimplemented("swapon unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_symlink_2 (int *err, const char *oldpath, const char *newpath)
{
  log_unimplemented("symlink unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_symlinkat_3 (int *err, const char *oldpath,
			      int newdirfd, const char *newpath)
{
  log_unimplemented("symlinkat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sync_0 (int *err)
{
  log_unimplemented("sync unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sync_file_range_6 (int *err, int fd,
				    __LONG_LONG_PAIR(long offset_high,
						     long offset_low),
				    __LONG_LONG_PAIR(long nbytes_high,
						     long nbytes_low),
				    unsigned int flags)
{
#if 0
  __off64_t offset = ((__off64_t)offset_high) << 32 | offset_low;
  __off64_t nbytes = ((__off64_t)nbytes_high) << 32 | nbytes_low;
#endif
  log_unimplemented("sync_file_range unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL__sysctl_1 (int *err, struct __sysctl_args *args)
{
  log_unimplemented("sysctl unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_sysinfo_1 (int *err, struct sysinfo *info)
{
  log_unimplemented("sysinfo unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_tee_4 (int *err, int fd_in, int fd_out, size_t len,
			unsigned int flags)
{
  log_unimplemented("tee unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_syslog_3 (int *err, int type, char *bufp, int len)
{
  log_unimplemented("syslog unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_tgkill_3 (int *err, gid_t tgid, pid_t tid, int sig)
{
  log_unimplemented("tgkill unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timer_create_3 (int *err, clockid_t clockid,
				 struct sigevent *evp,
				 __kernel_timer_t *timerid)
{
  log_unimplemented("timer_create unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timer_delete_1 (int *err, __kernel_timer_t timerid)
{
  log_unimplemented("timer_delete unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timer_getoverrun_1 (int *err, __kernel_timer_t timerid)
{
  log_unimplemented("timer_getoverrun unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timer_gettime_2 (int *err, __kernel_timer_t timerid,
				  struct itimerspec *curr_value)
{
  log_unimplemented("timer_gettime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timer_settime_4 (int *err, __kernel_timer_t timerid, int flags,
				  const struct itimerspec *new_value,
				  struct itimerspec * old_value)
{
  log_unimplemented("timer_settime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timerfd_create_2 (int *err, int clockid, int flags)
{
  log_unimplemented("timerfd_create unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timerfd_gettime_2 (int *err, int fd,
				    struct itimerspec *curr_value)
{
  log_unimplemented("timerfd_gettime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_timerfd_settime_4 (int *err, int fd, int flags,
				    const struct itimerspec *new_value,
				    struct itimerspec *old_value)
{
  log_unimplemented("timerfd_settime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline clock_t
INTERNAL_SYSCALL_times_1 (int *err, struct tms *buf)
{
  log_unimplemented("times unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_tkill_2 (int *err, pid_t tid, int sig)
{
  log_unimplemented("tkill unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline mode_t
INTERNAL_SYSCALL_umask_1 (int *err, mode_t mask)
{
  // Lind: ignore setting umask, ignore setting umaskreturn full permissions as previous mask
  *err = 0;
  return 0777;
}

__extern_always_inline int
INTERNAL_SYSCALL_umount2_2 (int *err, const char *target, int flags)
{
  log_unimplemented("umount2 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_umount_1 (int *err, const char *target)
{
  return INTERNAL_SYSCALL_umount2_2 (err, target, 0);
}

__extern_always_inline int
INTERNAL_SYSCALL_uname_1 (int *err, struct utsname *buf)
{
  //log_unimplemented("uname unimplemented");
  //*err = (38 /* ENOSYS */);
#define CPSTR(d, s) memcpy(d, s, sizeof(s))
  CPSTR(buf->sysname, "Linux");
  CPSTR(buf->nodename, "ubuntu");
  CPSTR(buf->release, "3.8.0-35-generic");
  CPSTR(buf->version, "#50-Ubuntu SMP Tue Dec 3 01:24:59 UTC 2013");
  CPSTR(buf->machine, "x86_64");
#undef CPSTR
  *err = 0;
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_unlink_1 (int *err, const char *pathname)
{
  log_unimplemented("unlink unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_unlinkat_3 (int *err, int dirfd, const char *pathname,
			     int flags)
{
  log_unimplemented("unlinkat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_unshare_1 (int *err, int flags)
{
  log_unimplemented("unshare unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_uselib_1 (int *err, const char *library)
{
  log_unimplemented("uselib unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_ustat_2 (int *err, dev_t dev, struct ustat *ubuf)
{
  log_unimplemented("ustat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_utime_2 (int *err, const char *filename,
		          const struct utimbuf *times)
{
  log_unimplemented("utime unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_utimes_2 (int *err, const char *filename,
			   const struct timeval times[2])
{
  log_unimplemented("utimes unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_utimensat_4 (int *err, int dirfd, const char *pathname,
			      const struct timespec times[2], int flags)
{
  log_unimplemented("utimensat unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_vhangup_0 (int *err)
{
  log_unimplemented("vhangup unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

#ifdef __i386__
__extern_always_inline int
INTERNAL_SYSCALL_vm86_2 (int *err, unsigned long fn,
			 struct vm86plus_struct *v86)
{
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline int
INTERNAL_SYSCALL_vm86old_1 (int *err, struct vm86_struct *info)
{
  *err = (38 /* ENOSYS */);
  return 0;
}
#endif

__extern_always_inline ssize_t
INTERNAL_SYSCALL_vmsplice_4 (int *err, int fd, const struct iovec *iov,
			     unsigned long nr_segs, unsigned int flags)
{
  log_unimplemented("vmsplice unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline pid_t
INTERNAL_SYSCALL_wait3_3 (int *err, int *status, int options,
			  struct rusage *rusage)
{
  log_unimplemented("wait3 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline pid_t
INTERNAL_SYSCALL_wait4_4 (int *err, pid_t pid, int *status, int options,
			  struct rusage *rusage)
{
  log_unimplemented("wait4 unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_write_3 (int *err, int fd, const void *buf, size_t count)
{
  size_t nwrote;
  *err = __nacl_irt_write (fd, buf, count, &nwrote);
  return nwrote;
}

__extern_always_inline ssize_t
INTERNAL_SYSCALL_writev_3 (int *err, int fd, const
			   struct iovec *iov, int iovcnt)
{
  log_unimplemented("writev unimplemented");
  *err = (38 /* ENOSYS */);
  return 0;
}

# ifdef __i386__
#  undef INTERNAL_SYSCALL_chown_3
#  undef INTERNAL_SYSCALL_fchown_3
#  undef INTERNAL_SYSCALL_getegid_0
#  undef INTERNAL_SYSCALL_geteuid_0
#  undef INTERNAL_SYSCALL_getgid_0
#  undef INTERNAL_SYSCALL_getgroups_2
#  undef INTERNAL_SYSCALL_getresgid_3
#  undef INTERNAL_SYSCALL_getresuid_3
#  undef INTERNAL_SYSCALL_getuid_0
#  undef INTERNAL_SYSCALL_lchown_3
#  undef INTERNAL_SYSCALL_setfsgid_1
#  undef INTERNAL_SYSCALL_setfsuid_1
#  undef INTERNAL_SYSCALL_setgid_1
#  undef INTERNAL_SYSCALL_setgroups_2
#  undef INTERNAL_SYSCALL_setregid_2
#  undef INTERNAL_SYSCALL_setresgid_3
#  undef INTERNAL_SYSCALL_setresuid_3
#  undef INTERNAL_SYSCALL_setreuid_2
#  undef INTERNAL_SYSCALL_setuid_1
# endif
#endif

#include_next <sysdep.h>

#if !defined(__ASSEMBLER__) && defined(THREAD_SELF) && defined(CLOCK_IDFIELD_SIZE)
#include <tls.h>

/*
 * We don't support redefinition of this function. We always use 30 bits
 * of the address of pthread structure as TID.
 */
__extern_always_inline pid_t
INTERNAL_SYSCALL_gettid_0 (int *err)
{
  *err = 0;
  /* Native Client does not have a notion of a thread ID, so we make
     one up.  This must be small enough to leave space for number
     identifying the clock.  Use CLOCK_IDFIELD_SIZE to guarantee
     that.  */
  return ((unsigned int) THREAD_SELF) >> CLOCK_IDFIELD_SIZE;
}

/* We can not return error code - this function is not supposed to fail.
   It should return pid (which is equal to tid for the main process).
   It's only ever called from main process so we just return TID.  */
__extern_always_inline int
INTERNAL_SYSCALL_set_tid_address_1 (int *err, volatile int *tidptr)
{
  return INTERNAL_SYSCALL_gettid_0 (err);
}
#endif

#undef INTERNAL_SYSCALL_DECL
# define INTERNAL_SYSCALL_DECL(err) int err

#undef INTERNAL_SYSCALL_ERRNO
# define INTERNAL_SYSCALL_ERRNO(val, err) (err)

#undef INTERNAL_SYSCALL_ERROR_P
# define INTERNAL_SYSCALL_ERROR_P(val, err) (err)

/*
 * Define a macro which expands inline into the wrapper code for an IRT call.
 */
# undef INLINE_SYSCALL
# define INLINE_SYSCALL(name, nr, args...) \
  ({									      \
    INTERNAL_SYSCALL_DECL (err);					      \
    unsigned long int resultvar = INTERNAL_SYSCALL (name, err, nr , ## args); \
    if (__builtin_expect (err, 0))					      \
      {									      \
	__set_errno (err);						      \
	resultvar = (unsigned long int) -1;				      \
      }									      \
    (long int) resultvar; })

#undef INTERNAL_VSYSCALL
# define INTERNAL_VSYSCALL INTERNAL_SYSCALL

/*
 * Nacl uses AT_SYSINFO for IRT. Thus sysinfo can never be usable
 * and it's safe to disable this machinery.
 */
#undef NEED_DL_SYSINFO

#ifndef __x86_64__
#undef	PSEUDO
#define	PSEUDO(name, syscall_name, args)	\
  .text;					\
  ENTRY (name)					\
    mov $-38, %eax;				\
  L(pseudo_end):				\
    NACLRET

#undef	PSEUDO_END
#define	PSEUDO_END(name)			\
    SYSCALL_ERROR_HANDLER			\
  END (name)

#undef  PSEUDO_NOERRNO
#define PSEUDO_NOERRNO(name, syscall_name, args)\
  .text;					\
  ENTRY (name)					\
    mov $-38, %eax

#undef  PSEUDO_END_NOERRNO
#define PSEUDO_END_NOERRNO(name)		\
  END (name)

#undef ret_NOERRNO
#define ret_NOERRNO NACLRET

/* The function has to return the error code.  */
#undef  PSEUDO_ERRVAL
#define PSEUDO_ERRVAL(name, syscall_name, args)	\
  .text;					\
  ENTRY (name)					\
    mov $38, %eax

#undef  PSEUDO_END_ERRVAL
#define PSEUDO_END_ERRVAL(name)			\
  END (name)

#undef SYSCALL_ERROR_HANDLER_TLS_STORE
#define SYSCALL_ERROR_HANDLER_TLS_STORE(src, destoff)	\
  movl %gs:0, %eax;					\
  movl src, (%eax,destoff)

#endif
#endif

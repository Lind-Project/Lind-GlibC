
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>

#include <kernel_stat.h>
#include <nacl_stat.h>
#include <nacl_syscalls.h>
#include "strace.h"
#include <errno.h>
#include <sys/statfs.h>
#include <stddef.h>

#include "nacl_util.h"
#include "strace.h"
#include "lind_syscalls.h"


void __nacl_abi_stat_to_stat (struct nacl_abi_stat *nacl_st,
                                struct stat *st)
{
  st->st_dev = nacl_st->nacl_abi_st_dev;
  st->st_mode = nacl_st->nacl_abi_st_mode;
  st->st_nlink = nacl_st->nacl_abi_st_nlink;
  st->st_uid = nacl_st->nacl_abi_st_uid;
  st->st_gid = nacl_st->nacl_abi_st_gid;
  st->st_rdev = nacl_st->nacl_abi_st_rdev;
  st->st_size = nacl_st->nacl_abi_st_size;
  st->st_blksize = nacl_st->nacl_abi_st_blksize;
  st->st_blocks = nacl_st->nacl_abi_st_blocks;
  st->st_atim.tv_sec = nacl_st->nacl_abi_st_atime;
  st->st_atim.tv_nsec = 0;
  st->st_mtim.tv_sec = nacl_st->nacl_abi_st_mtime;
  st->st_mtim.tv_nsec = 0;
  st->st_ctim.tv_sec = nacl_st->nacl_abi_st_ctime;
  st->st_ctim.tv_nsec = 0;
  st->st_ino = nacl_st->nacl_abi_st_ino;
}

int __fxstat (int vers, int fd, struct stat *buf)
{
   if (buf == NULL) {
    errno = EFAULT;
    return -1;
  }


  nacl_strace( concat("fstatfs fd=",nacl_itoa(fd)) );
 
  if (fd < 10) {
    struct nacl_abi_stat nacl_buf;
    int result = NACL_SYSCALL (fstat) (fd, &nacl_buf);
    if (result < 0) {
      errno = -result;
      return -1;
    }
    __nacl_abi_stat_to_stat (&nacl_buf, buf);
    return result;
  }

  int lind_rc = lind_fstat_rpc(fd, buf);

  if (lind_rc < 0) {
    __set_errno (-lind_rc);
     return -1;
  }
  
  return lind_rc;

}
hidden_def(__fxstat)
#ifdef SHARED
extern __typeof (__fxstat64) __fxstat64 __attribute__ ((alias ("__GI___fxstat")));
#endif

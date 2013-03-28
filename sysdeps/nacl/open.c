#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sysdep.h>

#include <stdlib.h>


#include <unistd.h>
#include <nacl_rpc.h>
#include <nacl_syscalls.h>
/* #include <stdio-common/_itoa.h> */


#include "strace.h"
#include "nacl_util.h"
#include "lind_syscalls.h"
/*testing */ 


/* static int use_rpc_cached = RPC_DISABLED; */
/* static int __nacl_use_rpc (void) */
/* { */
/*   if (use_rpc_cached == RPC_NOT_CACHED) */
/*     { */
/*       use_rpc_cached = getenv("NACL_FILE_RPC") != NULL */
/*         ? RPC_ENABLED : RPC_DISABLED; */
/*     } */
/*   return use_rpc_cached == RPC_ENABLED; */
/* } */


/* struct open_message */
/* { */
/*   char method_id[4]; */
/*   int flags; */
/*   mode_t mode; */
/* }; */

/* static const char open_method_id[4] = "Open"; */

/* static int nacl_open_rpc (const char *filename, int flags, mode_t mode) */
/* { */

  
/*   /\* TODO(mseaborn): When we implement more POSIX-over-IPC calls, the */
/*      marshalling will be made generic rather than open-coded. *\/ */
/*   struct open_message header; */
/*   memcpy (header.method_id, open_method_id, sizeof (open_method_id)); */
/*   header.flags = flags; */
/*   header.mode = mode; */

/*   struct NaClImcMsgIoVec iov[2]; */
/*   iov[0].base = &header; */
/*   iov[0].length = sizeof (header); */
/*   iov[1].base = (char *) filename; */
/*   iov[1].length = strlen (filename); */
/*   struct NaClImcMsgHdr msg; */
/*   msg.iov = iov; */
/*   msg.iov_length = 2; */
/*   msg.descv = NULL; */
/*   msg.desc_length = 0; */

/*   if (imc_sendmsg (NACL_PLUGIN_ASYNC_FROM_CHILD_FD, &msg, 0) < 0) */
/*     return -1; */

/*   char buf[4]; */
/*   int fd; */
/*   iov[0].base = buf; */
/*   iov[0].length = sizeof (buf); */
/*   msg.iov = iov; */
/*   msg.iov_length = 1; */
/*   msg.descv = &fd; */
/*   msg.desc_length = 1; */
/*   int got = imc_recvmsg (NACL_PLUGIN_ASYNC_TO_CHILD_FD, &msg, 0); */
/*   /\* TODO(mseaborn): Check data portion of message and extract an */
/*      errno value in the case of an error. *\/ */
/*   if (got >= 0 && msg.desc_length == 1) */
/*     return fd; */
/*   else */
/*     { */
/*       errno = ENOENT; */
/*       return -1; */
/*     } */
/* } */

int __open (const char *filename, int flags, ...)
{
  /* By the time we are opening files, we are ready to capture all straces. */
  set_ready_to_log(); 

  int mode = 0;

  if(flags & O_CREAT) {
    va_list arg;
    va_start(arg, flags);
    mode = va_arg(arg, int);
    va_end(arg);
  }
  
  nacl_strace(concat("open ",filename));

  int lind_rc = lind_open_rpc(flags, mode, filename);
  if( lind_rc >= 0) {
     nacl_strace(concat("opened as ", nacl_itoa(lind_rc)));
     return lind_rc;
  } /* else we try the nacl open */
  nacl_strace("lind open failed, trying NaCl's");
  int result = INLINE_SYSCALL (open, 3, filename, flags, mode);
  if (result < 0) {
     errno = -lind_rc;
     return -1;
  }
  char * r; 
  char * str = concat("opened as ", aitoa(&r,result));
  nacl_strace(str);
  free(r);
  free(str);
  return result;
}
libc_hidden_def (__open)
weak_alias (__open, open)
strong_alias (__open, __libc_open)
strong_alias (__open, __open_nocancel)

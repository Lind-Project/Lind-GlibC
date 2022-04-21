#include <sys/shm.h>
#include <errno.h>

#include <irt_syscalls.h>


/* Detach shared memory segment starting at address specified by SHMADDR
   from the caller's data segment.  */

int __shmdt (const void *shmaddr) {

    int result;

    result = __nacl_irt_shmdt(shmaddr);
    if (result != 0) {
      errno = result;
      return -1;
    }

    return 0;
}

weak_alias (__shmdt, shmdt)

#include <sys/shm.h>
#include <errno.h>

#include <irt_syscalls.h>


/* Attach the shared memory segment associated with SHMID to the data
   segment of the calling process.  SHMADDR and SHMFLG determine how
   and where the segment is attached.  */

void *__shmat (int shmid, const void *shmaddr, int shmflg) {

    int result;

    result = __nacl_irt_shmat(shmid, &shmaddr, shmflg);
    if (result != 0) {
      errno = result;
      return (void *)-1;
    }
    return shmaddr;
}

weak_alias (__shmat, shmat)
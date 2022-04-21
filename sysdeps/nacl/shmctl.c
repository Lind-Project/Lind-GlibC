#include <sys/shm.h>
#include <errno.h>

#include <irt_syscalls.h>


/* Provide operations to control over shared memory segments.  */


int __shmctl (int shmid, int cmd, struct shmid_ds *buf) {

    int result;

    result = __nacl_irt_shmctl(shmid, cmd, buf);
    if (result < 0) {
      __set_errno (-result);
      return -1;
    }
    return result;
}

weak_alias (__shmctl, shmctl)

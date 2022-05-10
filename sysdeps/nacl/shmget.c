#include <sys/shm.h>
#include <errno.h>

#include <irt_syscalls.h>


/* Return an identifier for an shared memory segment of at least size SIZE
   which is associated with KEY.  */

int __shmget (key_t key, size_t size, int shmflg) {

    int result;

    result = __nacl_irt_shmget(key, size, shmflg);
    if (result < 0) {
      __set_errno (-result);
      return -1;
    }
    return result;
}

weak_alias (__shmget, shmget)

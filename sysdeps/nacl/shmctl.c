#include <sys/shm.h>
#include <errno.h>

#include <nacl_stat.h>
#include <irt_syscalls.h>

void __nacl_abi_shmidstat_to_shmidstat (struct nacl_abi_shmid_ds *nacl_shmid_ds,
                                struct shmid_ds *shmid_ds)
{
  shmid_ds->shm_perm.__key = nacl_shmid_ds->nacl_abi_shm_perm.nacl_abi_shm_key;
  shmid_ds->shm_perm.uid = nacl_shmid_ds->nacl_abi_shm_perm.nacl_abi_shm_uid;
  shmid_ds->shm_perm.gid = nacl_shmid_ds->nacl_abi_shm_perm.nacl_abi_shm_gid;
  shmid_ds->shm_perm.cuid = nacl_shmid_ds->nacl_abi_shm_perm.nacl_abi_shm_cuid;
  shmid_ds->shm_perm.cgid = nacl_shmid_ds->nacl_abi_shm_perm.nacl_abi_shm_cgid;
  shmid_ds->shm_perm.mode = nacl_shmid_ds->nacl_abi_shm_perm.nacl_abi_shm_mode;
  shmid_ds->shm_segsz = nacl_shmid_ds->nacl_abi_shm_segsz;
  shmid_ds->shm_atime = nacl_shmid_ds->nacl_abi_shm_atime;
  shmid_ds->shm_dtime = nacl_shmid_ds->nacl_abi_shm_dtime;
  shmid_ds->shm_ctime = nacl_shmid_ds->nacl_abi_shm_ctime;
  shmid_ds->shm_cpid = nacl_shmid_ds->nacl_abi_shm_cpid;
  shmid_ds->shm_lpid = nacl_shmid_ds->nacl_abi_shm_lpid;
  shmid_ds->shm_nattch = nacl_shmid_ds->nacl_abi_shm_nattch;
}


/* Provide operations to control over shared memory segments.  */

int __shmctl (int shmid, int cmd, struct shmid_ds *buf) {

    int result;

    struct nacl_abi_shmid_ds nacl_buf;

    if (cmd == IPC_STAT)  {
      result = __nacl_irt_shmctl(shmid, cmd, &nacl_buf);
      __nacl_abi_shmidstat_to_shmidstat(&nacl_buf, buf);
    } else {
       result = __nacl_irt_shmctl(shmid, cmd, NULL);
    }

    if (result < 0) {
      __set_errno (-result);
      return -1;
    }

    return result;
}

weak_alias (__shmctl, shmctl)

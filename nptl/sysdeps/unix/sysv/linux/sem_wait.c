/* sem_wait -- wait on a semaphore.  Generic futex-using version.
   Copyright (C) 2003, 2007 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Paul Mackerras <paulus@au.ibm.com>, 2003.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <errno.h>
#include <sysdep.h>
#include <lowlevellock.h>
#include <internaltypes.h>
#include <semaphore.h>

#include <pthreadP.h>
#include <shlib-compat.h>
#include <irt_syscalls.h>


void
attribute_hidden
__sem_wait_cleanup (void *arg)
{
  struct new_sem *isem = (struct new_sem *) arg;

  atomic_decrement (&isem->nwaiters);
}


int
__new_sem_wait (sem_t *sem)
{
  unsigned int semptr = (unsigned int) sem;
  int result = __nacl_irt_sem_wait(semptr);
  
  if (result < 0) {
      __set_errno (-result);
      return -1;
  }

  return result;
}
versioned_symbol (libpthread, __new_sem_wait, sem_wait, GLIBC_2_1);


#if SHLIB_COMPAT (libpthread, GLIBC_2_0, GLIBC_2_1)
int
attribute_compat_text_section
__old_sem_wait (sem_t *sem)
{
  int *futex = (int *) sem;
  int err;

  do
    {
      if (atomic_decrement_if_positive (futex) > 0)
	return 0;

      /* Enable asynchronous cancellation.  Required by the standard.  */
      int oldtype = __pthread_enable_asynccancel ();

      /* Always assume the semaphore is shared.  */
      err = lll_futex_wait (futex, 0, LLL_SHARED);

      /* Disable asynchronous cancellation.  */
      __pthread_disable_asynccancel (oldtype);
    }
  while (err == 0 || err == -EWOULDBLOCK);

  __set_errno (-err);
  return -1;
}

compat_symbol (libpthread, __old_sem_wait, sem_wait, GLIBC_2_0);
#endif

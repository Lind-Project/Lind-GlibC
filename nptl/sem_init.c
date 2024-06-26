/* Copyright (C) 2002, 2007 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@redhat.com>, 2002.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <errno.h>
#include <semaphore.h>
#include <lowlevellock.h>
#include <shlib-compat.h>
#include "semaphoreP.h"
#include <kernel-features.h>
#include <irt_syscalls.h>


int
__new_sem_init (sem, pshared, value)
     sem_t *sem;
     int pshared;
     unsigned int value;
{
  unsigned int semptr = (unsigned int) sem;
  int result = __nacl_irt_sem_init(semptr, pshared, value);
  
  if (result < 0) {
      __set_errno (-result);
      return -1;
  }

  return result;
}
versioned_symbol (libpthread, __new_sem_init, sem_init, GLIBC_2_1);



#if SHLIB_COMPAT(libpthread, GLIBC_2_0, GLIBC_2_1)
int
attribute_compat_text_section
__old_sem_init (sem, pshared, value)
     sem_t *sem;
     int pshared;
     unsigned int value;
{
  /* Parameter sanity check.  */
  if (__builtin_expect (value > SEM_VALUE_MAX, 0))
    {
      __set_errno (EINVAL);
      return -1;
    }

  /* Map to the internal type.  */
  struct old_sem *isem = (struct old_sem *) sem;

  /* Use the value the user provided.  */
  isem->value = value;

  /* We cannot store the PSHARED attribute.  So we always use the
     operations needed for shared semaphores.  */

  return 0;
}
compat_symbol (libpthread, __old_sem_init, sem_init, GLIBC_2_0);
#endif

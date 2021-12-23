/*
 * Copyright 2008 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can
 * be found in the LICENSE file.
 */

#ifndef _NACL_DIRENT_H
#define _NACL_DIRENT_H

typedef int64_t nacl_abi_off_t;
typedef uint64_t nacl_abi_ino_t;

/* From native_client/src/trusted/service_runtime/include/sys/dirent.h */
/* TODO(mikhailt): extract the shared part of the dirent declarations to
   native_client/src/shared */

/* We need a way to define the maximum size of a name. */
#ifndef MAXNAMLEN
# ifdef NAME_MAX
#  define MAXNAMLEN NAME_MAX
# else
#  define MAXNAMLEN 255
# endif
#endif

/* dirent represents a single directory entry. */
struct nacl_abi_dirent
  {
    nacl_abi_ino_t nacl_abi_d_ino;
    nacl_abi_off_t nacl_abi_d_off;
    uint16_t       nacl_abi_d_reclen;
    char           nacl_abi_d_name[MAXNAMLEN + 1];
  };

#endif  /* _NACL_DIRENT_H */

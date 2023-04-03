#ifndef _NACL_SIGPROCMASK_H
#define _NACL_SIGPROCMASK_H

#include <signal.h>
#include <stdint.h>

void __sigset_t_to_uint(const sigset_t *set, uint64_t *nacl_set);
void __uint_to_sigset_t(const uint64_t *nacl_set, sigset_t *set);

#endif

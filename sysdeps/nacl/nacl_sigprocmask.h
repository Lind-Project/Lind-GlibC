#ifndef _NACL_SIGPROCMASK_H
#define _NACL_SIGPROCMASK_H

#include <signal.h>
#include <stdint.h>

// Because we cannot determine how sigset_t works under the hood and different
// platforms have different implementations, we decide to convert sigset_t to
// a uint64_t bitmask, which is a lot easier to work with in NaCl and
// Safeposix. The conversion is done using sigsetops like sigaddset(),
// sigdelset, and sigismember().
//
// Eg. Assume a sigset_t set has SIGUSR1 signal(we can check this using
// sigismember(&set, SIGUSR1)). Because SIGUSR1's signal number is 10, it
// corresponds to the 10th bit in the uint64_t set.
//
// Check sysdeps/nacl/sigprocmask.c for the implementation of the following
// functions.

void __sigset_t_to_uint(const sigset_t *set, uint64_t *nacl_set);
void __uint_to_sigset_t(const uint64_t *nacl_set, sigset_t *set);
void __remove_unwanted_signals(uint64_t *nacl_set);

#endif

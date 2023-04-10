#ifndef _NACL_SIGNAL_H
#define _NACL_SIGNAL_H

#include <signal.h>
#include <stdint.h>

struct nacl_sigset {
	unsigned long int val[16];
};

struct nacl_abi_sigaction {
	uint32_t __sa_handler;
	uint64_t sa_mask;
	int32_t sa_flags;
};

void __sigset_t_to_uint(const sigset_t *set, uint64_t *nacl_set);
void __uint_to_sigset_t(const uint64_t *nacl_set, sigset_t *set);
void __remove_unwanted_signals(uint64_t *nacl_set);

void __sigaction_to_nacl_abi_sigaction(const struct sigaction *act, struct nacl_abi_sigaction *nacl_act);
void __nacl_abi_sigaction_to_sigaction(const struct nacl_abi_sigaction *nacl_act, struct sigaction *act);

#endif

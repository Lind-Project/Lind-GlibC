#ifndef _NACL_SIGACTION_H
#define _NACL_SIGACTION_H

#include <signal.h>
#include <stdint.h>
#include <nacl_sigprocmask.h>

struct nacl_sigset {
	unsigned long int val[16];
};

struct nacl_abi_sigaction {
	uint32_t __sa_handler;
	uint64_t sa_mask;
	int32_t sa_flags;
};

void __sigaction_to_nacl_abi_sigaction(const struct sigaction *act, struct nacl_abi_sigaction *nacl_act);
void __nacl_abi_sigaction_to_sigaction(const struct nacl_abi_sigaction *nacl_act, struct sigaction *act);

#endif

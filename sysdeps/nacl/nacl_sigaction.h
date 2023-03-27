#ifndef _NACL_SIGACTION_H
#define _NACL_SIGACTION_H

#include <signal.h>
#include <stdint.h>

struct nacl_sigset {
	unsigned long int val[16];
};

struct nacl_abi_sigaction {
	__sighandler_t __sa_handler;
	struct nacl_sigset sa_mask;
	int sa_flags;
};

void __sigaction_to_nacl_abi_sigaction(struct sigaction *act, struct nacl_abi_sigaction *nacl_act);
void __nacl_abi_sigaction_to_sigaction(struct nacl_abi_sigaction *nacl_act, struct sigaction *act);

#endif

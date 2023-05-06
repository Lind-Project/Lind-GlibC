#include <unistd.h>
#include <stddef.h>

#include <irt_syscalls.h>

unsigned int __alarm(unsigned int seconds) {
  return __nacl_irt_alarm(seconds);
}

weak_alias(__alarm, alarm)
weak_alias(__alarm, __libc_alarm)

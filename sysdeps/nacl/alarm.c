#include <unistd.h>

#include <irt_syscalls.h>

unsigned int alarm(unsigned int seconds) {
  return __nacl_irt_alarm(seconds);
}

weak_alias (alarm, __alarm)
weak_alias (alarm, __lib_alarm)

libc_hidden_def (alarm)

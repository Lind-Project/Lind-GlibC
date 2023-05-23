#include <unistd.h>
#include <sys/time.h>

unsigned int alarm(unsigned int seconds) {
  struct itimerval timer;
  struct itimerval old_timer;

  timer.it_value.tv_sec = seconds;
  timer.it_value.tv_usec = 0;
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 0;

  setitimer(ITIMER_REAL, &timer, &old_timer);

  return old_timer.it_value.tv_sec;
}

weak_alias (alarm, __alarm)
weak_alias (alarm, __lib_alarm)

libc_hidden_def (alarm)

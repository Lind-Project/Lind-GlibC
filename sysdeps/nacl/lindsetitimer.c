#include <errno.h>
#include <sys/time.h>

#include <irt_syscalls.h>

int lindsetitimer(int which, const struct itimerval *new_value, struct itimerval *old_value)
{
	int result;

	if (which == ITIMER_REAL || which == ITIMER_VIRTUAL || which == ITIMER_PROF) {
		__set_errno (EINVAL);
		return -1;
	}

	if (
		new_value->it_interval.tv_usec < 0 ||
		new_value->it_interval.tv_usec > 999999 ||
		new_value->it_value.tv_usec < 0 ||
		new_value->it_value.tv_usec > 999999
	) {
		__set_errno (EINVAL);
		return -1;
	}

	result = __nacl_irt_lindsetitimer(which, new_value, old_value);

	if (result != 0) {
		__set_errno (result);
		return -1;
	}

	return 0;
}

weak_alias (lindsetitimer, __lindsetitimer)
weak_alias (lindsetitimer, __lib_lindsetitimer)

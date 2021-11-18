#include <time.h>

#if !defined(LIBSOL10_COMPAT_HAVE_TIMELOCAL) || !defined(LIBSOL10_COMPAT_HAVE_TIMEGM)
static int _is_leap_year(int year)
{
	return (year % 400 == 0)
		|| (year % 4 == 0 && year % 100 != 0);
}

static time_t _tm_to_sec(struct tm* tm)
{
	int i, year;
	time_t val;

	val = tm->tm_sec
		+ tm->tm_min * 60
		+ tm->tm_hour * 3600
		+ tm->tm_yday * 86400;

	year = 1900 + tm->tm_year;
	for (i = 1970; i < year; i++) {
		if (_is_leap_year(i)) {
			val += 366 * 86400;
		} else {
			val += 365 * 86400;
		}
	}

	return val;
}
#endif

#ifndef LIBSOL10_COMPAT_HAVE_TIMELOCAL
time_t timelocal(struct tm* tm)
{
	time_t val;
	tzset();
	val = _tm_to_sec(tm);
	val += timezone;
	return val;
}
#endif /* LIBSOL10_COMPAT_HAVE_TIMELOCAL */

#ifndef LIBSOL10_COMPAT_HAVE_TIMEGM
time_t timegm(struct tm* tm)
{
	return _tm_to_sec(tm);
}
#endif /* LIBSOL10_COMPAT_HAVE_TIMEGM */

#ifndef _LIBSOL10_COMPAT_TIME_H_
#define _LIBSOL10_COMPAT_TIME_H_

#include "libsol10-compat-config.h"

#include_next <time.h>

#ifndef LIBSOL10_COMPAT_HAVE_TIMELOCAL
time_t timelocal(struct tm *tm);
#endif /* LIBSOL10_COMPAT_HAVE_TIMELOCAL */
#ifndef LIBSOL10_COMPAT_HAVE_TIMEGM
time_t timegm(struct tm* tm);
#endif /* LIBSOL10_COMPAT_HAVE_TIMEGM */

#endif /* _LIBSOL10_COMPAT_TIME_H_ */

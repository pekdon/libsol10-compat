#ifndef _LIBSOL10_COMPAT_ERR_H_
#define _LIBSOL10_COMPAT_ERR_H_

#include "libsol10-compat-config.h"

#ifdef LIBSOL10_COMPAT_HAVE_ERR

#include_next <err.h>

#else /* ! LIBSOL10_COMPAT_HAVE_ERR */

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void warn(const char *fmt, ...);
extern void vwarn(const char *fmt, va_list ap);

extern void warnx(const char *fmt, ...);
extern void vwarnx(const char *fmt, va_list ap);

extern void err(int eval, const char *fmt, ...)
	  __attribute__ ((__noreturn__));
extern void verr(int eval, const char *fmt, va_list ap)
	  __attribute__ ((__noreturn__));
extern void errx(int eval, const char *fmt, ...)
	  __attribute__ ((__noreturn__));
extern void verrx(int eval, const char *fmt, va_list ap)
	  __attribute__ ((__noreturn__));

#ifdef __cplusplus
}
#endif

#endif /* LIBSOL10_COMPAT_HAVE_ERR */

#endif /* _LIBSOL10_COMPAT_ERR_H_ */

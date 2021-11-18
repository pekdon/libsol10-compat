#include <err.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LIBSOL10_COMPAT_HAVE_ERR_H

#define PROGNAME "" /* FIXME: get current name */

static void _print_error(const char *fmt, va_list ap, int do_err)
{
	fprintf(stderr, "%s: ", PROGNAME);
	if (fmt != NULL) {
		vfprintf(stderr, fmt, ap);
	}
	if (do_err) {
		if (fmt != NULL) {
			fprintf(stderr, ": ");
		}
		fprintf(stderr, "%s", strerror(errno));
	}
	fprintf(stderr, "\n");
}

void warn(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vwarn(fmt, ap);
	va_end(ap);
}

void vwarn(const char *fmt, va_list ap)
{
	_print_error(fmt, ap, 1);
}

void warnx(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vwarn(fmt, ap);
	va_end(ap);

}

void vwarnx(const char *fmt, va_list ap)
{
	_print_error(fmt, ap, 0);
}

void err(int eval, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	verr(eval, fmt, ap);
	va_end(ap);
}

void verr(int eval, const char *fmt, va_list ap)
{
	_print_error(fmt, ap, 1);
	exit(eval);
}

void errx(int eval, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	verrx(eval, fmt, ap);
	va_end(ap);
}

void verrx(int eval, const char *fmt, va_list ap)
{
	_print_error(fmt, ap, 0);
	exit(eval);
}

#endif /* LIBSOL10_COMPAT_HAVE_ERR_H */

#ifndef _LIBSOL10_COMPAT_STDIO_H_
#define _LIBSOL10_COMPAT_STDIO_H_

#include "libsol10-compat-config.h"

#include_next <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIBSOL10_COMPAT_HAVE_GETDELIM
extern ssize_t getdelim(char **lineptr, size_t *n, int delimiter,
			FILE *stream);
#endif /* LIBSOL10_COMPAT_HAVE_GETDELIM */
#ifndef LIBSOL10_COMPAT_HAVE_GETLINE
extern ssize_t getline(char **lineptr, size_t *n, FILE *stream);
#endif /* LIBSOL10_COMPAT_HAVE_GETLINE */

#ifdef __cplusplus
}
#endif

#endif /* _LIBSOL10_COMPAT_STDLIB_H_ */

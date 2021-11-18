#ifndef _LIBSOL10_COMPAT_STRINGS_H_
#define _LIBSOL10_COMPAT_STRINGS_H_

#include "libsol10-compat-config.h"

#ifdef LIBSOL10_COMPAT_HAVE_STRINGS_H
#include_next <strings.h>
#endif /* LIBSOL10_COMPAT_HAVE_STRINGS_H */

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIBSOL10_COMPAT_HAVE_STRNCASECMP
extern int strncasecmp(const char* s1, const char* s2, size_t n);
#endif /* LIBSOL10_COMPAT_HAVE_STRNCASECMP */

#ifdef __cplusplus
}
#endif

#endif /* _LIBSOL10_COMPAT_STRINGS_H_ */

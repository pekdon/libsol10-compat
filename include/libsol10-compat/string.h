#ifndef _LIBSOL10_COMPAT_STRING_H_
#define _LIBSOL10_COMPAT_STRING_H_

#include "libsol10-compat-config.h"

#include_next <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIBSOL10_COMPAT_HAVE_STRNLEN
extern size_t strnlen(const char* s, size_t n);
#endif /* LIBSOL10_COMPAT_HAVE_STRNLEN */
#ifndef LIBSOL10_COMPAT_HAVE_STRNDUP
extern char* strndup(const char* s, size_t n);
#endif /* LIBSOL10_COMPAT_HAVE_STRNDUP */
#ifndef LIBSOL10_COMPAT_HAVE_STRLCAT
extern size_t strlcat(char* dst, const char* src, size_t dstsize);
#endif /* LIBSOL10_COMPAT_HAVE_STRLCAT */
#ifndef LIBSOL10_COMPAT_HAVE_STRSEP
extern char* strsep(char **stringp, const char *delim);
#endif /* LIBSOL10_COMPAT_HAVE_STRSEP */

#ifdef _GNU_SOURCE
#ifndef LIBSOL10_COMPAT_HAVE_STRCASESTR
extern char* strcasestr(const char* haystack, const char* needle);
#endif /* LIBSOL10_COMPAT_HAVE_STRCASESTR */
#ifndef LIBSOL10_COMPAT_HAVE_MEMMEM
extern void* memmem(const void* haystack, size_t haystackn,
		    const void* needle, size_t needlen);
#endif /* LIBSOL10_COMPAT_HAVE_MEMMEM */
#endif /* _GNU_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* _LIBSOL10_COMPAT_STRING_H_ */

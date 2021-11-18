#ifndef _LIBSOL10_COMPAT_UNISTD_H_
#define _LIBSOL10_COMPAT_UNISTD_H_

#include "libsol10-compat-config.h"

#include_next <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIBSOL10_COMPAT_HAVE_FACCESSAT
extern int faccessat(int dirfd, const char *path, int mode, int flags);
#endif /* LIBSOL10_COMPAT_HAVE_FACCESSAT */
#ifndef LIBSOL10_COMPAT_HAVE_READLINKAT
extern ssize_t readlinkat(int dirfd, const char *path,
			  char *buf, size_t bufsiz);
#endif /* LIBSOL10_COMPAT_HAVE_READLINKAT */

#ifdef __cplusplus
}
#endif

#endif /* _LIBSOL10_COMPAT_UNISTD_H_ */

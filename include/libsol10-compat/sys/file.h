#ifndef _LIBSOL10_COMPAT_SYS_FILE_H_
#define _LIBSOL10_COMPAT_SYS_FILE_H_

#include "libsol10-compat-config.h"

#ifdef LIBSOL10_COMPAT_HAVE_SYS_FILE_H
#include_next <sys/random.h>
#endif /* LIBSOL10_COMPAT_HAVE_SYS_FILE_H */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIBSOL10_COMPAT_HAVE_FLOCK

#define LOCK_SH 1
#define LOCK_EX 2
#define LOCK_UN 4
#define LOCK_NB 8

extern int flock(int fd, int operation);
#endif /* LIBSOL10_COMPAT_HAVE_FLOCK */

#ifdef __cplusplus
}
#endif

#endif /* _LIBSOL10_COMPAT_SYS_FILE_H_ */

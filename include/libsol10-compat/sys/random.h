#ifndef _LIBSOL10_COMPAT_SYS_RANDOM_H_
#define _LIBSOL10_COMPAT_SYS_RANDOM_H_

#include "libsol10-compat-config.h"
#include <sys/types.h> /* ssize_t */

#ifdef LIBSOL10_COMPAT_HAVE_SYS_RANDOM_H
#include_next <sys/random.h>
#endif /* LIBSOL10_COMPAT_HAVE_SYS_RANDOM_H */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIBSOL10_COMPAT_HAVE_GETRANDOM
#define GRND_NONBLOCK 1
#define GRND_RANDOM 2

extern ssize_t getrandom(void* buf, size_t n, unsigned int flags);
#endif /* LIBSOL10_COMPAT_HAVE_GETRANDOM */

#ifdef __cplusplus
}
#endif

#endif /* _LIBSOL10_COMPAT_SYS_RANDOM_H_ */

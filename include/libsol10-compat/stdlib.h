#ifndef _LIBSOL10_COMPAT_STDLIB_H_
#define _LIBSOL10_COMPAT_STDLIB_H_

#include "libsol10-compat-config.h"

#include_next <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIBSOL10_COMPAT_HAVE_POSIX_MEMALIGN
extern int posix_memalign(void** ptr_ret, size_t alignment, size_t size);
#endif /* LIBSOL10_COMPAT_HAVE_POSIX_MEMALIGN */

#ifdef __cplusplus
}
#endif

#endif /* _LIBSOL10_COMPAT_STDLIB_H_ */

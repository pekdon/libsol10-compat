#ifndef _LIBSOL10_COMPAT_DIRENT_H_
#define _LIBSOL10_COMPAT_DIRENT_H_

#include "libsol10-compat-config.h"

#include_next <dirent.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIBSOL10_COMPAT_HAVE_DIRFD
extern int dirfd(DIR *dirp);
#endif /* LIBSOL10_COMPAT_HAVE_DIRFD */

#ifdef __cplusplus
}
#endif

#endif /* _LIBSOL10_COMPAT_DIRENT_H_ */

#ifndef _LIBSOL10_COMPAT_SYS_FEATURE_TESTS_H_
#define _LIBSOL10_COMPAT_SYS_FEATURE_TESTS_H_

/*
 * sys/feature_tests.h generates an error if compiling with a C99 and not
 * using 200112L POSIX_C_SOURCE, 200809L and newer does not work.
 */

#if __STDC_VERSION__ - 0 >= 199901L
/* ensure _XOPEN_SOURCE and _POSIX_C_SOURCE are in sync with c99 */
#if defined(_XOPEN_SOURCE) || defined(_POSIX_C_SOURCE)
#undef _XOPEN_SOURCE
#undef _POSIX_C_SOURCE
#define _XOPEN_SOURCE 600
#define _POSIX_C_SOURCE 200112L
#endif
#else
#if (_XOPEN_SOURCE - 0) > 500
#undef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif
#if (_POSIX_C_SOURCE - 0) > 199506L
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199506L
#endif
#endif

#include_next <sys/feature_tests.h>

#endif /* _LIBSOL10_COMPAT_SYS_FEATURE_TESTS_H_ */

#ifndef _LIBSOL10_COMPAT_FCNTL_H_
#define _LIBSOL10_COMPAT_FCNTL_H_

#include_next <fcntl.h>

#ifdef __cplusplus
extern "C" {
#endif

/* when used with C++, function names can clash, ensure calling code
 * can be modified to skip these macros. */
#if !defined(__cplusplus) || defined(LIBSOL10_COMPAT_ENABLE_MACROS)
#if !defined(LIBSOL10_COMPAT_DISABLE_MACROS)

#ifdef F_DUPFD_CLOEXEC
#define LIBSOL10_COMPAT_HAVE_FCNTL
#else
#define fcntl(FD, ...) sol_fcntl((FD), __VA_ARGS__)
#define F_DUPFD_CLOEXEC 1030
#endif /* F_DUPFD_CLOEXEC */

#ifdef O_CLOEXEC
#define LIBSOL10_COMPAT_HAVE_OPEN
#else
#define open(PATH, ...)	sol_open((PATH), __VA_ARGS__)
#define O_CLOEXEC 02000000
#endif /* O_CLOEXEC */

#endif
#endif

extern int sol_fcntl(int fd, int cmd, ...);
extern int sol_open(const char *path, int oflag, ...);

#ifdef __cplusplus
}
#endif

#endif /* _LIBSOL10_COMPAT_FCNTL_H_ */

#ifndef _LIBSOL10_COMPAT_TERMIOS_H_
#define _LIBSOL10_COMPAT_TERMIOS_H_

#include "libsol10-compat-config.h"

#include_next <termios.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIBSOL10_COMPAT_HAVE_OPENPTY
int openpty(int *amaster, int *aslave, char *name,
	    struct termios *termp, struct winsize *winp);
#endif

#ifndef LIBSOL10_COMPAT_HAVE_LOGIN_TTY
int login_tty(int fd);
#endif

#ifndef LIBSOL10_COMPAT_HAVE_FORKPTY
pid_t forkpty(int *amaster, char *name,
              struct termios *termp, struct winsize *winp);
#endif /* LIBSOL10_COMPAT_HAVE_FORKPTY */

#ifdef __cplusplus
}
#endif

#endif /* _LIBSOL10_COMPAT_TERMIOS_H_ */

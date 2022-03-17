#ifndef _LIBSOL10_COMPAT_PATHS_H_
#define _LIBSOL10_COMPAT_PATHS_H_

#include "libsol10-compat-config.h"

#ifdef LIBSOL10_COMPAT_HAVE_PATHS_H
#include_next <paths.h>
#endif /* LIBSOL10_COMPAT_HAVE_PATHS_H */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIBSOL10_COMPAT_HAVE_PATHS_H

#define _PATH_BSHELL	"/bin/sh"
#define _PATH_DEVNULL	"/dev/null"
#define _PATH_KMEM	"/dev/kmem"
#define _PATH_LASTLOG	"/var/adm/lastlog"
#define _PATH_MAN	"/usr/share/man"
#define _PATH_MEM       "/dev/mem"
#define _PATH_MNTTAB	"/etc/vfstab"
#define _PATH_PRESERVE	"/var/lib"
#define _PATH_SENDMAIL	"/usr/sbin/sendmail"
#define _PATH_SHELLS	"/etc/shells"
#define _PATH_TTY	"/dev/tty"
#define _PATH_VI	"/usr/bin/vi"

#define _PATH_DEV	"/dev/"
#define _PATH_TMP	"/tmp/"
#define _PATH_VARDB	"/var/db/"
#define _PATH_VARRUN	"/var/run/"
#define _PATH_VARTMP	"/var/tmp/"

#endif /* LIBSOL10_COMPAT_HAVE_PATHS_H */

#ifdef __cplusplus
}
#endif

#endif /* _LIBSOL10_COMPAT_PATHS_H_ */

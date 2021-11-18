#ifndef _LIBSOL10_COMPAT_SYSLOG_H_
#define _LIBSOL10_COMPAT_SYSLOG_H_

#include "libsol10-compat-config.h"

#include_next <syslog.h>

#ifndef LOG_AUTHPRIV
#define LOG_AUTHPRIV LOG_AUTH
#endif /* ! LOG_AUTHPRIV */

#endif /* _LIBSOL10_COMPAT_SYSLOG_H_ */

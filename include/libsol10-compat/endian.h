#ifndef _LIBSOL10_COMPAT_ENDIAN_H_
#define _LIBSOL10_COMPAT_ENDIAN_H_

#ifdef LIBSOL10_COMPAT_HAVE_ENDIAN_H

#include_next <endian.h>

#else /* ! LIBSOL10_COMPAT_HAVE_ENDIAN_H */

#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN 4321

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#	define __BYTE_ORDER __LITTLE_ENDIAN
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#	define __BYTE_ORDER __BIG_ENDIAN
#else
#error "unknown endianness"
#endif

#endif /* LIBSOL10_COMPAT_HAVE_ENDIAN_H */

#endif /* _LIBSOL10_COMPAT_ENDIAN_H_ */

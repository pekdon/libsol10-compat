#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>

#ifndef LIBSOL10_COMPAT_HAVE_FCNTL

/* ensure sol_* wrappers recurse */
#undef fcntl

static int _f_dupfd_cloexec(int fd, int arg)
{
	int dfd, flags;

	dfd = fcntl(fd, F_DUPFD, arg);
	if (dfd == -1) {
		return -1;
	}

	flags = fcntl(fd, F_GETFL);
	flags |= FD_CLOEXEC;
	fcntl(dfd, F_SETFL, flags);

	return dfd;
}

int sol_fcntl(int fd, int cmd, ...)
{
	int res;
	va_list ap;
	va_start(ap, cmd);

	switch (cmd) {
	case F_DUPFD:
	case F_DUP2FD:
	case F_SETFD:
	case F_SETFL:
	case F_SETOWN:
	{
		int iarg = va_arg(ap, int);
		res = fcntl(fd, cmd, iarg);
		break;
	}

	case F_GETFD:
	case F_GETFL:
	case F_GETOWN:
	case F_GETXFL:
		res = fcntl(fd, cmd);
		break;

#if F_FREESP != F_FREESP64
	case F_FREESP:
	case F_GETLK:
	case F_SETLK:
	case F_SETLKW:
	{
		struct flock *fl = va_arg(ap, struct flock*);
		res = fcntl(fd, cmd, fl);
		break;
	}
#endif /* F_FREESP != F_FREESP64 */
	case F_FREESP64:
	case F_GETLK64:
	case F_SETLK64:
	case F_SETLKW64:
	{
		struct flock64 *fl = va_arg(ap, struct flock64*);
		res = fcntl(fd, cmd, fl);
		break;
	}

	case F_SHARE:
	case F_UNSHARE:
	{
		fshare_t *fs = va_arg(ap, fshare_t*);
		res = fcntl(fd, cmd, fs);
		break;
	}

	/* fcntls not supported in Solaris 10 */
	case F_DUPFD_CLOEXEC:
	{
		int iarg = va_arg(ap, int);
		res = _f_dupfd_cloexec(fd, iarg);
		break;
	}

	default:
		assert(0);
	}

	va_end(ap);

	return res;
}

#endif /* LIBSOL10_COMPAT_HAVE_FCNTL */

#ifndef LIBSOL10_COMPAT_HAVE_OPEN

#undef open

int sol_open(const char *path, int oflag, ...)
{
	int fd;
	va_list ap;
	int cloexec = 0;
	mode_t mode = 0;

	va_start(ap, oflag);
	mode = va_arg(ap, mode_t);
	va_end(ap);

	if (oflag & O_CLOEXEC) {
		oflag &= ~O_CLOEXEC;
		cloexec = 1;
	}
	fd = open(path, oflag, mode);
	if (fd >= 0 && cloexec) {
		int flags = fcntl(fd, F_GETFD, 0);
		if (flags >= 0) {
			flags |= FD_CLOEXEC;
			fcntl(fd, F_SETFD, flags);
		}
	}
	return fd;
}

#endif /* LIBSOL10_COMPAT_HAVE_OPEN */

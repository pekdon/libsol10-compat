#include <sys/file.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef LIBSOL10_COMPAT_HAVE_FLOCK
int flock(int fd, int operation)
{
	struct flock64 lock = {0};
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;

	switch (operation & (LOCK_SH|LOCK_EX|LOCK_UN)) {
	case LOCK_SH:
		lock.l_type = F_RDLCK;
		break;
	case LOCK_EX:
		lock.l_type = F_WRLCK;
		break;
	case LOCK_UN:
		lock.l_type = F_UNLCK;
		break;
	default:
		errno = EINVAL;
		return -1;
	}

	return fcntl(fd, (operation & LOCK_NB) ? F_SETLK64 : F_SETLKW64, &lock);
}
#endif /* LIBSOL10_COMPAT_HAVE_FLOCK */

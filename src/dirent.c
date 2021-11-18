#include <sys/types.h>
#include <dirent.h>

#ifndef LIBSOL10_COMPAT_HAVE_DIRFD

int dirfd(DIR *dirp)
{
#ifdef __XOPEN_OR_POSIX
	return dirp->d_fd;
#else
	return dirp->dd_fd;
#endif
}

#endif /* LIBSOL10_COMPAT_HAVE_DIRFD */

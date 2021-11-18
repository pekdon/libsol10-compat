#include <sys/fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *_resolve_path(int dirfd, const char *path)
{
	char *resolved_path;
	if (path[0] == '/') {
		/* absolute path, no need to expand. */
		resolved_path = strdup(path);
	} else {
		char buf[PATH_MAX];
		if (dirfd == AT_FDCWD) {
			getcwd(buf, sizeof(buf));
		} else {
			/* FIXME: support this without breaking cwd for
			 * other threads: /proc/self/fd/%d ? */
			char cwd[PATH_MAX];
			getcwd(cwd, sizeof(cwd));
			fchdir(dirfd);
			getcwd(buf, sizeof(buf));
			chdir(cwd);
		}
		strlcat(buf, "/", sizeof(buf));
		strlcat(buf, path, sizeof(buf));

		resolved_path = malloc(PATH_MAX);
		realpath(buf, resolved_path);
	}
	return resolved_path;
}


#ifndef LIBSOL10_COMPAT_HAVE_FACCESSAT
int faccessat(int dirfd, const char *path, int mode, int flags)
{
	int res = -1;
	/* FIXME: AT_SYMLINK_NOFOLLOW (if resolved_path is a symlink, lstat) */
	/* FIXME: AT_EACCESS not supported */
	if (flags != 0) {
		return res;
	}

	char *resolved_path = _resolve_path(dirfd, path);
	if (resolved_path != NULL) {
		res = access(resolved_path, mode);
		free(resolved_path);
	}
	return res;
}
#endif /* LIBSOL10_COMPAT_HAVE_FACCESSAT */

#ifndef LIBSOL10_COMPAT_HAVE_READLINKAT
ssize_t readlinkat(int dirfd, const char *path,
		   char *buf, size_t bufsiz)
{
	ssize_t res = -1;
	char *resolved_path = _resolve_path(dirfd, path);
	if (resolved_path != NULL) {
		res = readlink(resolved_path, buf, bufsiz);
		free(resolved_path);
	}
	return res;
}
#endif /* LIBSOL10_COMPAT_HAVE_READLINKAT */
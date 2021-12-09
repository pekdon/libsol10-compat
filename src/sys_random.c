#include <sys/random.h>
#include <fcntl.h>
#include <unistd.h>

#if !defined(LIBSOL10_COMPAT_HAVE_GETRANDOM) || !defined(LIBSOL10_COMPAT_HAVE_GETENTROPY)
static int _read_bytes(const char *path, int nonblock, void* buf, size_t n)
{
	int fd, flags;
	ssize_t nread;

	flags = O_RDONLY;
	if (nonblock) {
		flags |= O_NONBLOCK;
	}
	fd = open(path, flags);
	if (fd == -1) {
		return -1;
	}

	nread = read(fd, buf, n);

	close(fd);

	return nread;
}
#endif

#ifndef LIBSOL10_COMPAT_HAVE_GETRANDOM
ssize_t getrandom(void* buf, size_t n, unsigned int flags)
{
	const char *source_path =
		(flags & GRND_RANDOM) ? "/dev/random" : "/dev/urandom";
	int nonblock = (flags & GRND_NONBLOCK) == GRND_NONBLOCK;
	return _read_bytes(source_path, nonblock, buf, n);
}
#endif /* LIBSOL10_COMPAT_HAVE_GETRANDOM */

#ifndef LIBSOL10_COMPAT_HAVE_GETENTROPY
int getentropy(void* buf, size_t n)
{
	const char *source_path = "/dev/urandom";
	if (_read_bytes("/dev/urandom", 0, buf, n) != n) {
		return -1;
	}
	return 0;
}
#endif /* LIBSOL10_COMPAT_HAVE_GETENTROPY */

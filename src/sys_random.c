#include <sys/random.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef LIBSOL10_COMPAT_HAVE_GETRANDOM
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

ssize_t getrandom(void* buf, size_t n, unsigned int flags)
{
	const char *source_path =
		(flags & GRND_RANDOM) ? "/dev/random" : "/dev/urandom";
	int nonblock = (flags & GRND_NONBLOCK) == GRND_NONBLOCK;
	return _read_bytes(source_path, nonblock, buf, n);
}
#endif /* LIBSOL10_COMPAT_HAVE_GETRANDOM */
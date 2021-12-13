#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif /* _GNU_SOURCE */

#include <time.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/random.h>
#include <assert.h>
#include <dirent.h>
#include <endian.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <termios.h>
#include <unistd.h>

static int flush_fork(void)
{
	fflush(stdout);
	fflush(stderr);
	return fork();
}

static void progress(const char *fmt, ...)
{
	fprintf(stdout, "%d (%d): ", time(NULL), getpid());

	va_list ap;
	va_start(ap, fmt);
	vfprintf(stdout, fmt, ap);
	va_end(ap);

	fprintf(stdout, "\n");
}

void test_dirent(void)
{
	/* dirfd */
	progress("dirent.h dirfd");
	DIR *dh;
	dh = opendir(".");
	assert(dh != NULL);
	assert(dirfd(dh) >= 0);
	closedir(dh);
}

void test_endian(void)
{
#ifdef __BYTE_ORDER
	progress("endian.h #define");
#if __BYTE_ORDER == __LITTLE_ENDIAN
	assert(__BYTE_ORDER == __LITTLE_ENDIAN);
	assert(__BYTE_ORDER != __BIG_ENDIAN);
#else
	assert(__BYTE_ORDER != __LITTLE_ENDIAN);
	assert(__BYTE_ORDER == __BIG_ENDIAN);
#endif
#endif
}

void test_err(void)
{
	/* err */

	/* warn */
}

void test_fcntl(void)
{
	/* fcntl F_DUPFD_CLOEXEC */

	/* open O_CLOEXEC */
}

void test_stdio(void)
{
	/* getdelim */
	progress("stdio.h getdelim");
	{
		size_t linecapp = 0;
		char *line = NULL;
		FILE *fp = fopen("data/getdelim.data", "r");
		assert(fp);

		/* initial alloc test */
		assert(11 == getdelim(&line, &linecapp, ',', fp));
		assert(0 == strcmp(line, "0123456789,"));
		assert(linecapp > 11);

		/* same buffer test */
		size_t old_linecapp = linecapp;
		assert(11 == getdelim(&line, &linecapp, '\n', fp));
		assert(0 == strcmp(line, "abcdefghij\n"));
		assert(old_linecapp == linecapp);

		/* grow buffer test */
		assert(101 == getdelim(&line, &linecapp, '\n', fp));
		assert(0 == strcmp(line, "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\n"));
		assert(linecapp >= old_linecapp);

		/* until EOF test */
		old_linecapp = linecapp;
		assert(6 == getdelim(&line, &linecapp, '!', fp));
		assert(0 == strcmp(line, "short\n"));
		assert(old_linecapp == linecapp);

		/* until EOF test, not assert NUL terminated line, implementation
                   dependent. */
		assert(-1 == getdelim(&line, &linecapp, '\n', fp));
		assert(old_linecapp == linecapp);

		fclose(fp);
		free(line);
	}

	/* getline */
	progress("stdio.h getline");
	{
		size_t linecapp = 80;
		char *line = malloc(linecapp);
		FILE *fp = fopen("data/getline.data", "r");
		assert(fp);

		/* re-use buffer */
		assert(11 == getline(&line, &linecapp, fp));
		assert(0 == strcmp(line, "0123456789\n"));
		assert(80 == linecapp);

		/* EOF test, not assert NUL terminated line, implementation
                   dependent. */
		assert(-1 == getline(&line, &linecapp, fp));
		assert(80 == linecapp);

		fclose(fp);
		free(line);
	}
}

void test_stdlib(void)
{
	/* posix_memalign */
	progress("stdlib.h posix_memalign");
	{
		void *mem;
		for (int i = 0; i < 64; i++) {
			assert(0 == posix_memalign(&mem, sizeof(void*), i));
			assert(0 == (((uint64_t) mem) % sizeof(void*)));
			free(mem);
		}
	}
}

void test_string(void)
{
	/* strnlen */
	progress("string.h strnlen");
	assert(4 == strnlen("test", 5));
	assert(2 == strnlen("test", 2));

	/* strndup */
	progress("string.h strndup");
	{
		char *copy;
		copy = strndup("test", 5);
		assert(NULL != copy);
		assert(0 == strcmp(copy, "test"));
		free(copy);
		copy = strndup("test", 2);
		assert(NULL != copy);
		assert(0 == strcmp(copy, "te"));
		free(copy);
	}

	/* strcasestr */
	progress("string.h strcasestr");
	{
		char *pos;
		pos = strcasestr("my TeSt string", "test");
		assert(NULL != pos);
		assert(0 == strcmp(pos, "TeSt string"));
		pos = strcasestr("my end test", "test");
		assert(NULL != pos);
		assert(0 == strcmp(pos, "test"));
		assert(NULL == strcasestr("my test", "missing"));
	}

	/* memmem */
	progress("string.h memmem");
	{
		void *pos;
		pos = memmem("my test string", 14, "test", 4);
		assert(NULL != pos);
		assert(0 == strcmp(pos, "test string"));
		pos = memmem("my end string", 14, "string", 6);
		assert(NULL != pos);
		assert(0 == strcmp(pos, "string"));
		assert(NULL == memmem("my test string", 14, "missing", 7));
	}
}

void test_strings(void)
{
	/* strncasecmp */
	progress("strings.h strncasecmp");
	assert(0 == strncasecmp("TEST", "test", 5));
	assert(0 == strncasecmp("te", "TEST", 2));
	assert(0 != strncasecmp("test", "other", 5));
	assert(-115 == strncasecmp("te", "test", 5));
	assert(115 == strncasecmp("test", "te", 5));
}

static void test_sys_file_child(int pfd[], int op)
{
	int fd = open("data/flock", O_RDWR|O_CREAT, 0664);
	assert(fd > -1);
	int tmp;
	assert(sizeof(int) == read(pfd[0], &tmp, sizeof(int)));
	progress("waiting for lock %d", getpid());
	flock(fd, op);
	progress("locked %d", getpid());
	assert(sizeof(int) == write(pfd[1], &tmp, sizeof(int)));
	assert(sizeof(int) == read(pfd[0], &tmp, sizeof(int)));
	sleep(1);
	flock(fd, LOCK_UN);
	progress("unlocked %d", getpid());
	assert(sizeof(int) == write(pfd[1], &tmp, sizeof(int)));
	close(fd);
	write(pfd[1], &fd, sizeof(int));
	close(pfd[1]);
	exit(0);
}

void test_sys_file(void)
{
	/* flock */
	progress("sys/file.h flock");
	int p1[2];
	assert(0 == pipe(p1));
	pid_t c1 = flush_fork();
	assert(c1 > -1);
	if (c1 == 0) {
		test_sys_file_child(p1, LOCK_EX);
	}
	int p2[2];
	assert(0 == pipe(p2));
	pid_t c2 = flush_fork();
	assert(c2 > -1);
	if (c2 == 0) {
		test_sys_file_child(p2, LOCK_EX);
	}

	/* c1 and c2 waiting for flock */
	int tmp = 0;
	assert(sizeof(int) == write(p1[1], &tmp, sizeof(int)));
	/* locked, after read succeeds */
	assert(sizeof(int) == read(p1[0], &tmp, sizeof(int)));
	/* try to grab lock, blocks */
	assert(sizeof(int) == write(p2[1], &tmp, sizeof(int)));
	/* signal unlock */
	assert(sizeof(int) == write(p1[1], &tmp, sizeof(int)));
	/* locked, after read succeeds */
	assert(sizeof(int) == read(p2[0], &tmp, sizeof(int)));
	/* signal unlock */
	assert(sizeof(int) == write(p2[1], &tmp, sizeof(int)));

	int c1_ret, c2_ret;
	assert(c1 == waitpid(c1, &c1_ret, 0));
	assert(c2 == waitpid(c2, &c2_ret, 0));
	assert(0 == WEXITSTATUS(c1_ret));
	assert(0 == WEXITSTATUS(c2_ret));
}

void test_sys_random(void)
{
	/* getrandom */
	progress("sys/random.h getrandom");
	ssize_t n;
	char buf[128], zerobuf[128];
	memset(zerobuf, 0, sizeof(zerobuf));

	memset(buf, 0, sizeof(buf));
	n = getrandom(buf, sizeof(buf), 0);
	assert(n > 0);
	assert(memcmp(buf, zerobuf, 128) != 0);
	memset(buf, 0, sizeof(buf));
	n = getrandom(buf, sizeof(buf), GRND_RANDOM);
	assert(n > 0);
	assert(memcmp(buf, zerobuf, 128) != 0);

	/* getentropy */
	progress("sys/random.h getentropy");
	memset(buf, 0, sizeof(buf));
	assert(getentropy(buf, sizeof(buf)) == 0);
	assert(memcmp(buf, zerobuf, 128) != 0);
}

void test_termios(void)
{
	/* openpty */
	progress("termios.h openpty");
	{
		int primary, slave;
		assert(0 == openpty(&primary, &slave, NULL, NULL, NULL));
		close(primary);
		close(slave);
	}

	/* forkpty */
	progress("termios.h forkpty");
	{
		int primary;
		pid_t pid = forkpty(&primary, NULL, NULL, NULL);
		assert(pid > -1);
		if (pid == 0) {
			char *const argv[] = { "/bin/sh", NULL };
			execv(argv[0], argv);
			exit(1);
		}
		sleep(1);
		size_t len;
		char buf[512];
		memset(buf, '\0', sizeof(buf));
		len = read(primary, buf, sizeof(buf) - 1);
		progress("io read %d: \"%s\"", len, buf);
		write(primary, "uptime\n", 7);
		sleep(1);
		memset(buf, '\0', sizeof(buf));
		len = read(primary, buf, sizeof(buf) - 1);
		progress("io read %d: \"%s\"", len, buf);
		write(primary, "exit\n", 5);
		memset(buf, '\0', sizeof(buf));
		len = read(primary, buf, sizeof(buf) - 1);
		progress("io read %d: \"%s\"", len, buf);
		close(primary);
		int ret;
		assert(pid == waitpid(pid, &ret, 0));
		assert(0 == WEXITSTATUS(ret));
	}
}

void test_time(void)
{
	time_t loc, gm;
	struct tm tm;
	const int expected_time = 158122921;

	tm.tm_sec = 1;
	tm.tm_min = 2;
	tm.tm_hour = 3;
	tm.tm_mday = 5;
	tm.tm_mon = 0;
	tm.tm_year = 75;
	tm.tm_wday = 6;
	tm.tm_yday = 4;
	tm.tm_isdst = 0;

	tzset();

	/* timelocal */
	progress("time.h timelocal");
	loc = timelocal(&tm);
	/* currently fails on FreeBSD */
#ifndef __FreeBSD__
	assert(loc == expected_time + timezone);
#endif /* __FreeBSD__ */

	/* timegm */
	progress("time.h timegm");
	gm = timegm(&tm);
	assert(gm == expected_time);
}

void test_unistd(void)
{
	/* faccessat(AT_CWD, "test_all.c"
	 * faccessat(fd, "/absolute/path"
	 * faccessat(fd, "../relative/path"
	 */

	/* readlinkat(AT_CWD, "test_all.c"
	 * readlinkat(fd, "/absolute/path"
	 * readlinkat(fd, "../relative/path"
	 */
}

int in_argv(const char *search, int argc, char *argv[])
{
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], search) == 0) {
			return 1;
		}
	}
	return 0;
}

struct suite {
	void(*fun)();
	const char *name;
};

int main(int argc, char *argv[])
{
	int all = (argc == 1) || in_argv("all", argc, argv);
	struct suite suites[] = {
		{test_dirent, "dirent.h"},
		{test_endian, "endian.h"},
		{test_err, "err.h"},
		{test_fcntl, "fcntl.h"},
		{test_stdio, "stdio.h"},
		{test_stdlib, "stdlib.h"},
		{test_string, "string.h"},
		{test_strings, "strings.h"},
		{test_sys_file, "sys/file.h"},
		{test_sys_random, "sys/random.h"},
		{test_termios, "termios.h"},
		{test_time, "time.h"},
		{test_unistd, "unistd.h"},
		{NULL, NULL}
	};
	for (int i = 0; suites[i].name; i++) {
		if (all || in_argv(suites[i].name, argc, argv)) {
			progress(">>> %s", suites[i].name);
			suites[i].fun();
			progress("<<< %s", suites[i].name);
		}
	}
	progress("DONE");
	return 0;
}

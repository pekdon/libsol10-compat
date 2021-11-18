#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif /* _GNU_SOURCE */

#include <assert.h>
#include <dirent.h>
#include <endian.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/random.h>
#include <time.h>
#include <sys/fcntl.h>
#include <unistd.h>

void test_dirent(void)
{
	/* dirfd */
	DIR *dh;
	dh = opendir(".");
	assert(dh != NULL);
	assert(dirfd(dh) >= 0);
	closedir(dh);
}

void test_endian(void)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
	assert(__BYTE_ORDER == __LITTLE_ENDIAN);
	assert(__BYTE_ORDER != __BIG_ENDIAN);
#else
	assert(__BYTE_ORDER != __LITTLE_ENDIAN);
	assert(__BYTE_ORDER == __BIG_ENDIAN);
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

	/* getline */
}

void test_stdlib(void)
{
	/* posix_memalign */
}

void test_string(void)
{
	/* strnlen */
	assert(4 == strnlen("test", 5));
	assert(2 == strnlen("test", 2));

	/* strndup */
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
	assert(0 == strncasecmp("TEST", "test", 5));
	assert(0 == strncasecmp("te", "TEST", 2));
	assert(0 != strncasecmp("test", "other", 5));
	assert(-115 == strncasecmp("te", "test", 5));
	assert(115 == strncasecmp("test", "te", 5));
}

void test_sys_file(void)
{
	/* flock */
}

void test_sys_random(void)
{
	/* getrandom */
	ssize_t n;
	char *buf[128], zerobuf[128];
	memset(buf, 0, sizeof(buf));
	memset(zerobuf, 0, sizeof(zerobuf));

	n = getrandom(buf, sizeof(buf), 0);
	assert(n > 0);
	assert(memcmp(buf, zerobuf, 128) != 0);
	n = getrandom(buf, sizeof(buf), GRND_RANDOM);
	assert(n > 0);
	assert(memcmp(buf, zerobuf, 128) != 0);
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

	loc = timelocal(&tm);
	gm = timegm(&tm);

	tzset();
	assert(gm == expected_time);
	assert(loc == expected_time + timezone);
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

int main(int argc, char *argv[])
{
	test_dirent();
	test_endian();
	test_err();
	test_fcntl();
	test_stdio();
	test_stdlib();
	test_string();
	test_strings();
	test_sys_file();
	test_sys_random();
	test_time();
	test_unistd();
	printf("OK\n");
	return 0;
}

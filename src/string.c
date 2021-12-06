#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#ifndef LIBSOL10_COMPAT_HAVE_STRNLEN
size_t strnlen(const char* s, size_t n)
{
	const char *end = memchr(s, '\0', n);
	if (end == NULL) {
		return n;
	}
	return end - s;

}
#endif /* LIBSOL10_COMPAT_HAVE_STRNLEN */

#ifndef LIBSOL10_COMPAT_HAVE_STRNDUP
char* strndup(const char* s, size_t n)
{
	char *sc;
	const char *end;

	end = memchr(s, '\0', n);
	if (end != NULL) {
		n = end - s;
	}
	sc = malloc(n + 1);
	memcpy(sc, s, n);
	sc[n] = '\0';
	return sc;
}
#endif /* LIBSOL10_COMPAT_HAVE_STRNDUP */

#ifndef LIBSOL10_COMPAT_HAVE_STRNCASECMP
int strncasecmp(const char* s1, const char* s2, size_t n)
{
	int diff;
	size_t i, n1, n2;

	n1 = strnlen(s1, n);
	n2 = strnlen(s2, n);
	n = n1 < n2 ? n1 : n2;
	for (i = 0; i < n; i++) {
		diff = tolower(s1[i]) - tolower(s2[i]);
		if (diff != 0) {
			return diff;
		}
	}

	if (n1 < n2) {
		return -1;
	} else if (n1 > n2) {
		return 1;
	} else {
		return 0;
	}
}
#endif /* LIBSOL10_COMPAT_HAVE_STRNCASECMP */

#ifndef LIBSOL10_COMPAT_HAVE_STRCASESTR
char* strcasestr(const char* haystack, const char* needle)
{
	const char *p;
	size_t haystackn, needlen;

	haystackn = strlen(haystack);
	needlen = strlen(needle);

	p = haystack;
	while (haystackn >= needlen) {
		if (strncasecmp(p, needle, needlen) == 0) {
		    return (char*) p;
		}
		p++;
		haystackn--;
	}
	return NULL;
}
#endif /* LIBSOL10_COMPAT_HAVE_STRCASESTR */

#ifndef LIBSOL10_COMPAT_HAVE_MEMMEM
void* memmem(const void* haystack, size_t haystackn,
	     const void* needle, size_t needlen)
{
	const char *p = (const char*) haystack;
	while (haystackn >= needlen) {
		if (memcmp(p, needle, needlen) == 0) {
			return (void*) p;
		}
		p++;
		haystackn--;
	}
	return NULL;
}
#endif /* LIBSOL10_COMPAT_HAVE_MEMMEM */

#ifndef LIBSOL10_COMPAT_HAVE_STRLCAT
size_t strlcat(char* dst, const char* src, size_t dstsize)
{
	size_t src_len = strlen(src);
	if (dstsize == 0) {
		return src_len;
	}

	size_t dst_len = 0;
	for (; dst_len < dstsize; dst_len++) {
		if (dst[dst_len] == '\0') {
			break;
		}
	}

	if (dst_len < dstsize) {
		size_t len = dstsize - dst_len - 1;
		memcpy(dst + dst_len, src, len);
		dst[dst_len + len] = '\0';
	}

	return dst_len + src_len;
}
#endif /* LIBSOL10_COMPAT_HAVE_STRLCAT */

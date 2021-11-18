#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define BUF_INC 128

#ifndef LIBSOL10_COMPAT_HAVE_GETDELIM
ssize_t getdelim(char **lineptr, size_t *n, int delimiter, FILE *restrict fp)
{
	char *cur_pos, *new_lineptr;
	size_t new_lineptr_len;
	int c;

	if (lineptr == NULL || n == NULL || fp == NULL) {
		errno = EINVAL;
		return -1;
	}

	if (*lineptr == NULL) {
		*lineptr = malloc(BUF_INC);
		if (*lineptr  == NULL) {
		    errno = ENOMEM;
		    return -1;
		}
		*n = BUF_INC;
	}

	cur_pos = *lineptr;
	for (;;) {
		c = getc(fp);
		if (ferror(fp) || (c == EOF && cur_pos == *lineptr)) {
		    return -1;
		}

		if (c == EOF) {
		    break;
		}

		if ((*lineptr + *n - cur_pos) < 2) {
			if (SSIZE_MAX / 2 < *n) {
				errno = EOVERFLOW;
				return -1;
			}
			new_lineptr_len = *n + BUF_INC;
			new_lineptr = realloc(*lineptr, new_lineptr_len);
			if (new_lineptr == NULL) {
				errno = ENOMEM;
				return -1;
			}
			cur_pos = new_lineptr + (cur_pos - *lineptr);
			*lineptr = new_lineptr;
			*n = new_lineptr_len;
		}
		*cur_pos++ = (char)c;
		if (c == delimiter) {
		    break;
		}
	}

	*cur_pos = '\0';
	return (ssize_t)(cur_pos - *lineptr);
}
#endif /* LIBSOL10_COMPAT_HAVE_GETDELIM */

#ifndef LIBSOL10_COMPAT_HAVE_GETLINE
ssize_t getline(char **lineptr, size_t *n, FILE *restrict fp)
{
	return getdelim(lineptr, n, '\n', fp);
}
#endif /* LIBSOL10_COMPAT_HAVE_GETLINE */

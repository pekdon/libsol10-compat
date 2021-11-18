#include <stdlib.h>

#ifndef LIBSOL10_COMPAT_HAVE_POSIX_MEMALIGN

int posix_memalign(void** ptr_ret, size_t alignment, size_t size)
{
	void *ptr = memalign(alignment, size);
	if (ptr == NULL) {
		return 1;
	}
	*ptr_ret = ptr;
	return 0;
}

#endif /* LIBSOL10_COMPAT_HAVE_POSIX_MEMALIGN */
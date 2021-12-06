bin_PROGRAMS = test_all
AM_CPPFLAGS = -I$(top_srcdir)/include/libsol10-compat

test_all_SOURCES = test_all.c
test_all_LDFLAGS = -L../src/.libs -lsol10_compat

check:
	./test_all

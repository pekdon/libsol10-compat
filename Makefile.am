ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = foreign

dist_doc_DATA = README

EXTRA_DIST = libsol10-compat.pc.in packages
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libsol10-compat.pc

SUBDIRS = include pkgsrc src util
if TESTS
SUBDIRS += test
endif

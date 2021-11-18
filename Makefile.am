ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = foreign

dist_doc_DATA = README

EXTRA_DIST = libsol10-compat.pc.in
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libsol10-compat.pc

SUBDIRS = include src util
if TESTS
SUBDIRS += test
endif

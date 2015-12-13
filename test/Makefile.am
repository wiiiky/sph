
AM_CPPFLAGS = \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	-DPACKAGE_TEST_DIR=\""$(top_srcdir)/test"\" \
	-I$(top_srcdir)/src

AM_CFLAGS = \
	-Wall \
	-g

AM_LDFLAGS = \
	-L$(top_srcdir)/src \
	-lsph

noinst_PROGRAMS = \
	test-buffer

TESTS = \
	test-buffer

test_buffer_SOURCES = \
	test-buffer.c


clean-local:
	-astyle --style=google -n *.c
	-rm -rf *~

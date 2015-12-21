
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
	test-buffer \
	test-mod

TESTS = \
	test-buffer \
	test-mod

test_buffer_SOURCES = \
	test-buffer.c

test_mod_SOURCES = \
	test-mod.c

all-local: test_mod.so

test_mod.so: test_mod.so.c
	$(CC) $(AM_CPPFLAGS) $(AM_CFLAGS) -shared -fPIC $? -o $@

clean-local:
	-astyle --style=google -n *.c
	-rm -rf *~ *.so

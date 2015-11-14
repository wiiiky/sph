AM_CFLAGS = -Wall -Werror


lib_LTLIBRARIES=libsph.la

libsph_la_SOURCES = \
	socket.c \
	loop.c \
	utils.c

libsph_la_LDFLAGS = -lev
libsph_lainclude_HEADERS = \
	sph.h \
	socket.h \
	loop.h \
	utils.h \
    jacques.h

libsph_laincludedir = $(includedir)/sph

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = sph.pc

clean-local:
	-astyle --style=google -n *.c *.h
	-rm -rf *~

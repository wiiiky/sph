AUTOMAKE_OPTIONS = foreign

VERSION_INFO = 4:0:0

EXTRA_DIST = LICENSE Changes libev.m4 autogen.sh \
	     ev_vars.h ev_wrap.h \
	     ev_epoll.c ev_select.c ev_poll.c ev_kqueue.c ev_port.c ev_win32.c \
	     ev.3 ev.pod Symbols.ev Symbols.event

man_MANS = ev.3

lib_LTLIBRARIES = libjac.la

libjac_la_SOURCES = ev.c event.c socket.c
libjac_la_LDFLAGS = -version-info $(VERSION_INFO)

libjac_lainclude_HEADERS = \
	ev.h ev++.h event.h libjac.h hook.h mod.h socket.h
libjac_laincludedir = $(includedir)/libjac

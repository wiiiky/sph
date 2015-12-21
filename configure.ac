#This line defines the name of the output tarball
AC_INIT([sph],[0.1])
#this line defines what compilation flags will be used
AM_INIT_AUTOMAKE
# DEFINE YOUR OWN HEADERS CHECK - DO NOT DELETE THIS LINE
#this line defines what libraries should be used during building
AC_CHECK_LIB([pthread],[pthread_create])
AC_CHECK_LIB([pthread],[pthread_join])
AC_CHECK_LIB([libev],[ev_loop_new])
# DEFINE YOUR OWN LIBRARY CHECK - DO NOT DELETE THIS LINE
AC_PROG_CC
AC_PREFIX_DEFAULT(/usr)

AC_PROG_INSTALL
AC_PROG_LIBTOOL

AC_CONFIG_MACRO_DIRS([m4])
#This line defines where Makefiles are stored for projects and sources
AC_CONFIG_FILES([Makefile])
AC_OUTPUT([
    src/Makefile
    src/sph.pc
    tests/Makefile
])

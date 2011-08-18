#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([danbooru-cpp-grabber], [0.1], [itakingiteasy@gmail.com])
AC_CONFIG_SRCDIR([src/Main.cpp])
AC_CONFIG_HEADERS([config.h])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE

CPPFLAGS="${CPPFLAGS} -I\$(top_srcdir)/include"


case $host in
  *mingw*) 
    AM_CONDITIONAL(MINGW, true)
    CXXFLAGS="-static-libgcc -static-libstdc++"
    LDFLAGS="-static"
  ;;
  *)
    AM_CONDITIONAL(MINGW, false)
  ;;
esac





# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL



# Checks for libraries.
AC_SEARCH_LIBS([dlopen], [dl dld])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.


AC_CONFIG_FILES([Makefile
                 src/Makefile
                 include/Makefile
                 include/danbooru-cpp-grabber/Makefile
                 modules/Makefile
                 modules/Downloaders/Makefile
                 modules/Downloaders/Curl/Makefile
])

AC_OUTPUT

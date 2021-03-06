#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.60])
AC_INIT([egg],[0.5.0],[pth@patrickhead.net])
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror])
LT_INIT

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([ ctype.h errno.h getopt.h libgen.h stdio.h stdlib.h string.h sys/stat.h sys/types.h time.h unistd.h ])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_MODE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset mkdir strchr strdup strtol])

# Checks for required packages
PKG_CHECK_MODULES(GRAY, libgray >= 0.1)

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  include/Makefile
  doc/Makefile
  doc/reference-manual/Makefile
  doc/user-guide/Makefile
  doc/man-pages/Makefile
  tools/Makefile
  misc/Makefile
])

AC_OUTPUT

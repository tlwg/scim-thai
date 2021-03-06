#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(scim-thai,
        m4_esyscmd([build-aux/git-version-gen]),
        [https://github.com/tlwg/scim-thai/issues])
AC_CONFIG_SRCDIR([src/scim_thai_imengine.h])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([dist-xz no-dist-gzip])

# gettext
AM_GNU_GETTEXT_VERSION([0.18.1])
AM_GNU_GETTEXT([external])
GETTEXT_PACKAGE=scim-thai
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [The gettext domain])

# Checks for programs.

AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

# libtool option to control which symbols are exported
# right now, symbols starting with _ are not exported
LIBTOOL_EXPORT_OPTIONS='-export-symbols-regex "^[[^_]].*"'
AC_SUBST(LIBTOOL_EXPORT_OPTIONS)

# Checks for libraries.

dnl *************
dnl     SCIM
dnl *************
SCIM_VERSION=0.99.8

PKG_CHECK_MODULES(SCIM,[scim >= $SCIM_VERSION])

# Check if we should build setup module
PKG_CHECK_MODULES(SCIM_GTKUTILS,[scim-gtkutils >= $SCIM_VERSION],
		  		[SCIM_HAS_GTKUTILS=yes],
				[SCIM_HAS_GTKUTILS=no])

AC_SUBST(SCIM_VERSION)

AM_CONDITIONAL(SCIM_BUILD_SETUP, [test "$SCIM_HAS_GTKUTILS" = "yes"])

if test "$SCIM_HAS_GTKUTILS" = "yes"; then
  SCIM_BUILD_SETUP=1
  PKG_CHECK_MODULES(GTK, [gtk+-3.0 >= 3.16])
else
  SCIM_BUILD_SETUP=0
fi

AC_SUBST(SCIM_BUILD_SETUP)

dnl *************
dnl    libthai
dnl *************

PKG_CHECK_MODULES(LIBTHAI, libthai)

# Checks for header files.

AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_FUNC_MALLOC

# Extra args.

AC_ARG_ENABLE(debug,
	      [  --enable-debug     Turn on debugging],
	      [case "${enableval}" in
	       yes) debug=yes ;;
	       no)  debug=no ;;
	       *) AC_MSG_ERROR(bad value ${enableval} for --enable-debug) ;;
       	      esac],[debug=no])

if test "x$debug" = "xyes"; then
  test "$cflags_set" = set || CFLAGS="$CFLAGS -g"
  test "$cppflags_set" = set || CPPFLAGS="$CXXFLAGS -g"
  SCIM_DEBUG_FLAGS="-DENABLE_DEBUG=1"
else
  SCIM_DEBUG_FLAGS=""
fi
AC_SUBST(SCIM_DEBUG_FLAGS)

RAW_PKG_CONFIG="$PKG_CONFIG --define-variable=prefix='\${prefix}'"
SCIM_ICONDIR=`$RAW_PKG_CONFIG --variable=icondir scim`
SCIM_MODULEDIR=`$RAW_PKG_CONFIG --variable=moduledir scim`

if test "x$SCIM_ICONDIR" = "x"; then
  SCIM_ICONDIR=${datadir}/scim/icons
fi

if test "x$SCIM_MODULEDIR" = "x"; then
  SCIM_MODULEDIR=${libdir}/scim-1.0
fi

AC_SUBST(SCIM_ICONDIR)
AC_SUBST(SCIM_MODULEDIR)
        
AC_CONFIG_FILES([Makefile po/Makefile.in
                 data/Makefile
                 src/Makefile])
AC_OUTPUT

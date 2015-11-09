AC_PREREQ([2.69])
AC_INIT([ncexplorer], [1.0], [pedro.vicente@space-research.org])
AM_INIT_AUTOMAKE
AM_SILENT_RULES([no])
AC_PROG_CXX

WX_CONFIG=wx-config
AC_ARG_WITH([wx-config],
            [AS_HELP_STRING([--with-wx-config=PATH],[Use the given PATH to wx-config])],
            [
              if test "$withval" != "yes" -a "$withval" != ""; then
              WX_CONFIG=$withval
              fi
            ],
            [])
AC_MSG_CHECKING([wxWidgets version])
if wxversion=`$WX_CONFIG --version`; then
    AC_MSG_RESULT([$wxversion])
else
    AC_MSG_ERROR([wxWidgets is required.])
fi
WX_CPPFLAGS="`$WX_CONFIG --cppflags`"
WX_LIBS="`$WX_CONFIG --libs`"

NC_CONFIG=nc-config
AC_ARG_WITH([nc-config],
            [AS_HELP_STRING([--with-nc-config=PATH],[Use the given PATH to nc-config])],
            [
              if test "$withval" != "yes" -a "$withval" != ""; then
              NC_CONFIG=$withval
              fi
            ],
            [])
AC_MSG_CHECKING([netCDF version])
if ncversion=`$NC_CONFIG --version`; then
    AC_MSG_RESULT([$ncversion])
else
    AC_MSG_ERROR([netCDF is required.])
fi
NC_CPPFLAGS="-I`$NC_CONFIG --includedir`"
NC_LIBS="`$NC_CONFIG --libs`"

CPPFLAGS="$CPPFLAGS $WX_CPPFLAGS $NC_CPPFLAGS"
NC_EXPLORER_LIBS="$WX_LIBS $NC_LIBS"
AC_SUBST(NC_EXPLORER_LIBS)
AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT

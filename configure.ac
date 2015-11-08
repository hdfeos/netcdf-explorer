AC_PREREQ([2.69])
AC_INIT([ncexplorer], [1.0], [pedro.vicente@space-research.org])
AM_INIT_AUTOMAKE
AM_SILENT_RULES([no])
AC_PROG_CXX

AC_MSG_CHECKING([wxWidgets version])
if wxversion=`wx-config --version`; then
    AC_MSG_RESULT([$wxversion])
else
    AC_MSG_ERROR([wxWidgets is required.])
fi
WX_CPPFLAGS="`wx-config --cppflags`"
WX_LIBS="`wx-config --libs`"

AC_MSG_CHECKING([netCDF version])
if ncversion=`nc-config --version`; then
    AC_MSG_RESULT([$ncversion])
else
    AC_MSG_ERROR([netCDF is required.])
fi
NC_LIBS="`nc-config --libs`"

CPPFLAGS="$CPPFLAGS $WX_CPPFLAGS"
NC_EXPLORER_LIBS="$WX_LIBS $NC_LIBS"
AC_SUBST(NC_EXPLORER_LIBS)
AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT

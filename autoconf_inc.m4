dnl ### begin block 00_header[explorer.bkl] ###
dnl
dnl This macro was generated by
dnl Bakefile 0.2.9 (http://www.bakefile.org)
dnl Do not modify, all changes will be overwritten!

BAKEFILE_AUTOCONF_INC_M4_VERSION="0.2.9"

dnl ### begin block 20_COND_BUILD_debug[explorer.bkl] ###
    COND_BUILD_debug="#"
    if test "x$BUILD" = "xdebug" ; then
        COND_BUILD_debug=""
    fi
    AC_SUBST(COND_BUILD_debug)
dnl ### begin block 20_COND_BUILD_debug_DEBUG_INFO_default[explorer.bkl] ###
    COND_BUILD_debug_DEBUG_INFO_default="#"
    if test "x$BUILD" = "xdebug" -a "x$DEBUG_INFO" = "xdefault" ; then
        COND_BUILD_debug_DEBUG_INFO_default=""
    fi
    AC_SUBST(COND_BUILD_debug_DEBUG_INFO_default)
dnl ### begin block 20_COND_BUILD_release[explorer.bkl] ###
    COND_BUILD_release="#"
    if test "x$BUILD" = "xrelease" ; then
        COND_BUILD_release=""
    fi
    AC_SUBST(COND_BUILD_release)
dnl ### begin block 20_COND_BUILD_release_DEBUG_INFO_default[explorer.bkl] ###
    COND_BUILD_release_DEBUG_INFO_default="#"
    if test "x$BUILD" = "xrelease" -a "x$DEBUG_INFO" = "xdefault" ; then
        COND_BUILD_release_DEBUG_INFO_default=""
    fi
    AC_SUBST(COND_BUILD_release_DEBUG_INFO_default)
dnl ### begin block 20_COND_DEBUG_FLAG_0[explorer.bkl] ###
    COND_DEBUG_FLAG_0="#"
    if test "x$DEBUG_FLAG" = "x0" ; then
        COND_DEBUG_FLAG_0=""
    fi
    AC_SUBST(COND_DEBUG_FLAG_0)
dnl ### begin block 20_COND_DEBUG_INFO_0[explorer.bkl] ###
    COND_DEBUG_INFO_0="#"
    if test "x$DEBUG_INFO" = "x0" ; then
        COND_DEBUG_INFO_0=""
    fi
    AC_SUBST(COND_DEBUG_INFO_0)
dnl ### begin block 20_COND_DEBUG_INFO_1[explorer.bkl] ###
    COND_DEBUG_INFO_1="#"
    if test "x$DEBUG_INFO" = "x1" ; then
        COND_DEBUG_INFO_1=""
    fi
    AC_SUBST(COND_DEBUG_INFO_1)
dnl ### begin block 20_COND_DEPS_TRACKING_0[explorer.bkl] ###
    COND_DEPS_TRACKING_0="#"
    if test "x$DEPS_TRACKING" = "x0" ; then
        COND_DEPS_TRACKING_0=""
    fi
    AC_SUBST(COND_DEPS_TRACKING_0)
dnl ### begin block 20_COND_DEPS_TRACKING_1[explorer.bkl] ###
    COND_DEPS_TRACKING_1="#"
    if test "x$DEPS_TRACKING" = "x1" ; then
        COND_DEPS_TRACKING_1=""
    fi
    AC_SUBST(COND_DEPS_TRACKING_1)
dnl ### begin block 20_COND_MONOLITHIC_0[explorer.bkl] ###
    COND_MONOLITHIC_0="#"
    if test "x$MONOLITHIC" = "x0" ; then
        COND_MONOLITHIC_0=""
    fi
    AC_SUBST(COND_MONOLITHIC_0)
dnl ### begin block 20_COND_MONOLITHIC_0_SHARED_1[explorer.bkl] ###
    COND_MONOLITHIC_0_SHARED_1="#"
    if test "x$MONOLITHIC" = "x0" -a "x$SHARED" = "x1" ; then
        COND_MONOLITHIC_0_SHARED_1=""
    fi
    AC_SUBST(COND_MONOLITHIC_0_SHARED_1)
dnl ### begin block 20_COND_MONOLITHIC_0_USE_MEDIA_1[explorer.bkl] ###
    COND_MONOLITHIC_0_USE_MEDIA_1="#"
    if test "x$MONOLITHIC" = "x0" -a "x$USE_MEDIA" = "x1" ; then
        COND_MONOLITHIC_0_USE_MEDIA_1=""
    fi
    AC_SUBST(COND_MONOLITHIC_0_USE_MEDIA_1)
dnl ### begin block 20_COND_MONOLITHIC_0_USE_WEBVIEW_1[explorer.bkl] ###
    COND_MONOLITHIC_0_USE_WEBVIEW_1="#"
    if test "x$MONOLITHIC" = "x0" -a "x$USE_WEBVIEW" = "x1" ; then
        COND_MONOLITHIC_0_USE_WEBVIEW_1=""
    fi
    AC_SUBST(COND_MONOLITHIC_0_USE_WEBVIEW_1)
dnl ### begin block 20_COND_MONOLITHIC_1[explorer.bkl] ###
    COND_MONOLITHIC_1="#"
    if test "x$MONOLITHIC" = "x1" ; then
        COND_MONOLITHIC_1=""
    fi
    AC_SUBST(COND_MONOLITHIC_1)
dnl ### begin block 20_COND_MONOLITHIC_1_USE_STC_1[explorer.bkl] ###
    COND_MONOLITHIC_1_USE_STC_1="#"
    if test "x$MONOLITHIC" = "x1" -a "x$USE_STC" = "x1" ; then
        COND_MONOLITHIC_1_USE_STC_1=""
    fi
    AC_SUBST(COND_MONOLITHIC_1_USE_STC_1)
dnl ### begin block 20_COND_OFFICIAL_BUILD_0_PLATFORM_WIN32_1[explorer.bkl] ###
    COND_OFFICIAL_BUILD_0_PLATFORM_WIN32_1="#"
    if test "x$OFFICIAL_BUILD" = "x0" -a "x$PLATFORM_WIN32" = "x1" ; then
        COND_OFFICIAL_BUILD_0_PLATFORM_WIN32_1=""
    fi
    AC_SUBST(COND_OFFICIAL_BUILD_0_PLATFORM_WIN32_1)
dnl ### begin block 20_COND_OFFICIAL_BUILD_1_PLATFORM_WIN32_1[explorer.bkl] ###
    COND_OFFICIAL_BUILD_1_PLATFORM_WIN32_1="#"
    if test "x$OFFICIAL_BUILD" = "x1" -a "x$PLATFORM_WIN32" = "x1" ; then
        COND_OFFICIAL_BUILD_1_PLATFORM_WIN32_1=""
    fi
    AC_SUBST(COND_OFFICIAL_BUILD_1_PLATFORM_WIN32_1)
dnl ### begin block 20_COND_PLATFORM_MACOSX_1[explorer.bkl] ###
    COND_PLATFORM_MACOSX_1="#"
    if test "x$PLATFORM_MACOSX" = "x1" ; then
        COND_PLATFORM_MACOSX_1=""
    fi
    AC_SUBST(COND_PLATFORM_MACOSX_1)
dnl ### begin block 20_COND_PLATFORM_MAC_0[explorer.bkl] ###
    COND_PLATFORM_MAC_0="#"
    if test "x$PLATFORM_MAC" = "x0" ; then
        COND_PLATFORM_MAC_0=""
    fi
    AC_SUBST(COND_PLATFORM_MAC_0)
dnl ### begin block 20_COND_PLATFORM_MAC_1[explorer.bkl] ###
    COND_PLATFORM_MAC_1="#"
    if test "x$PLATFORM_MAC" = "x1" ; then
        COND_PLATFORM_MAC_1=""
    fi
    AC_SUBST(COND_PLATFORM_MAC_1)
dnl ### begin block 20_COND_PLATFORM_OS2_1[explorer.bkl] ###
    COND_PLATFORM_OS2_1="#"
    if test "x$PLATFORM_OS2" = "x1" ; then
        COND_PLATFORM_OS2_1=""
    fi
    AC_SUBST(COND_PLATFORM_OS2_1)
dnl ### begin block 20_COND_PLATFORM_UNIX_0[explorer.bkl] ###
    COND_PLATFORM_UNIX_0="#"
    if test "x$PLATFORM_UNIX" = "x0" ; then
        COND_PLATFORM_UNIX_0=""
    fi
    AC_SUBST(COND_PLATFORM_UNIX_0)
dnl ### begin block 20_COND_PLATFORM_UNIX_1[explorer.bkl] ###
    COND_PLATFORM_UNIX_1="#"
    if test "x$PLATFORM_UNIX" = "x1" ; then
        COND_PLATFORM_UNIX_1=""
    fi
    AC_SUBST(COND_PLATFORM_UNIX_1)
dnl ### begin block 20_COND_PLATFORM_WIN32_0[explorer.bkl] ###
    COND_PLATFORM_WIN32_0="#"
    if test "x$PLATFORM_WIN32" = "x0" ; then
        COND_PLATFORM_WIN32_0=""
    fi
    AC_SUBST(COND_PLATFORM_WIN32_0)
dnl ### begin block 20_COND_PLATFORM_WIN32_1[explorer.bkl] ###
    COND_PLATFORM_WIN32_1="#"
    if test "x$PLATFORM_WIN32" = "x1" ; then
        COND_PLATFORM_WIN32_1=""
    fi
    AC_SUBST(COND_PLATFORM_WIN32_1)
dnl ### begin block 20_COND_SHARED_1[explorer.bkl] ###
    COND_SHARED_1="#"
    if test "x$SHARED" = "x1" ; then
        COND_SHARED_1=""
    fi
    AC_SUBST(COND_SHARED_1)
dnl ### begin block 20_COND_TOOLKIT_COCOA[explorer.bkl] ###
    COND_TOOLKIT_COCOA="#"
    if test "x$TOOLKIT" = "xCOCOA" ; then
        COND_TOOLKIT_COCOA=""
    fi
    AC_SUBST(COND_TOOLKIT_COCOA)
dnl ### begin block 20_COND_TOOLKIT_MAC[explorer.bkl] ###
    COND_TOOLKIT_MAC="#"
    if test "x$TOOLKIT" = "xMAC" ; then
        COND_TOOLKIT_MAC=""
    fi
    AC_SUBST(COND_TOOLKIT_MAC)
dnl ### begin block 20_COND_TOOLKIT_MSW[explorer.bkl] ###
    COND_TOOLKIT_MSW="#"
    if test "x$TOOLKIT" = "xMSW" ; then
        COND_TOOLKIT_MSW=""
    fi
    AC_SUBST(COND_TOOLKIT_MSW)
dnl ### begin block 20_COND_TOOLKIT_OSX_CARBON[explorer.bkl] ###
    COND_TOOLKIT_OSX_CARBON="#"
    if test "x$TOOLKIT" = "xOSX_CARBON" ; then
        COND_TOOLKIT_OSX_CARBON=""
    fi
    AC_SUBST(COND_TOOLKIT_OSX_CARBON)
dnl ### begin block 20_COND_TOOLKIT_OSX_COCOA[explorer.bkl] ###
    COND_TOOLKIT_OSX_COCOA="#"
    if test "x$TOOLKIT" = "xOSX_COCOA" ; then
        COND_TOOLKIT_OSX_COCOA=""
    fi
    AC_SUBST(COND_TOOLKIT_OSX_COCOA)
dnl ### begin block 20_COND_TOOLKIT_OSX_IPHONE[explorer.bkl] ###
    COND_TOOLKIT_OSX_IPHONE="#"
    if test "x$TOOLKIT" = "xOSX_IPHONE" ; then
        COND_TOOLKIT_OSX_IPHONE=""
    fi
    AC_SUBST(COND_TOOLKIT_OSX_IPHONE)
dnl ### begin block 20_COND_UNICODE_1[explorer.bkl] ###
    COND_UNICODE_1="#"
    if test "x$UNICODE" = "x1" ; then
        COND_UNICODE_1=""
    fi
    AC_SUBST(COND_UNICODE_1)
dnl ### begin block 20_COND_USE_CAIRO_1[explorer.bkl] ###
    COND_USE_CAIRO_1="#"
    if test "x$USE_CAIRO" = "x1" ; then
        COND_USE_CAIRO_1=""
    fi
    AC_SUBST(COND_USE_CAIRO_1)
dnl ### begin block 20_COND_USE_EXCEPTIONS_0[explorer.bkl] ###
    COND_USE_EXCEPTIONS_0="#"
    if test "x$USE_EXCEPTIONS" = "x0" ; then
        COND_USE_EXCEPTIONS_0=""
    fi
    AC_SUBST(COND_USE_EXCEPTIONS_0)
dnl ### begin block 20_COND_USE_EXCEPTIONS_1[explorer.bkl] ###
    COND_USE_EXCEPTIONS_1="#"
    if test "x$USE_EXCEPTIONS" = "x1" ; then
        COND_USE_EXCEPTIONS_1=""
    fi
    AC_SUBST(COND_USE_EXCEPTIONS_1)
dnl ### begin block 20_COND_USE_GUI_0[explorer.bkl] ###
    COND_USE_GUI_0="#"
    if test "x$USE_GUI" = "x0" ; then
        COND_USE_GUI_0=""
    fi
    AC_SUBST(COND_USE_GUI_0)
dnl ### begin block 20_COND_USE_GUI_1[explorer.bkl] ###
    COND_USE_GUI_1="#"
    if test "x$USE_GUI" = "x1" ; then
        COND_USE_GUI_1=""
    fi
    AC_SUBST(COND_USE_GUI_1)
dnl ### begin block 20_COND_USE_GUI_1_wxUSE_LIBJPEG_builtin[explorer.bkl] ###
    COND_USE_GUI_1_wxUSE_LIBJPEG_builtin="#"
    if test "x$USE_GUI" = "x1" -a "x$wxUSE_LIBJPEG" = "xbuiltin" ; then
        COND_USE_GUI_1_wxUSE_LIBJPEG_builtin=""
    fi
    AC_SUBST(COND_USE_GUI_1_wxUSE_LIBJPEG_builtin)
dnl ### begin block 20_COND_USE_GUI_1_wxUSE_LIBPNG_builtin[explorer.bkl] ###
    COND_USE_GUI_1_wxUSE_LIBPNG_builtin="#"
    if test "x$USE_GUI" = "x1" -a "x$wxUSE_LIBPNG" = "xbuiltin" ; then
        COND_USE_GUI_1_wxUSE_LIBPNG_builtin=""
    fi
    AC_SUBST(COND_USE_GUI_1_wxUSE_LIBPNG_builtin)
dnl ### begin block 20_COND_USE_GUI_1_wxUSE_LIBTIFF_builtin[explorer.bkl] ###
    COND_USE_GUI_1_wxUSE_LIBTIFF_builtin="#"
    if test "x$USE_GUI" = "x1" -a "x$wxUSE_LIBTIFF" = "xbuiltin" ; then
        COND_USE_GUI_1_wxUSE_LIBTIFF_builtin=""
    fi
    AC_SUBST(COND_USE_GUI_1_wxUSE_LIBTIFF_builtin)
dnl ### begin block 20_COND_USE_PLUGINS_0[explorer.bkl] ###
    COND_USE_PLUGINS_0="#"
    if test "x$USE_PLUGINS" = "x0" ; then
        COND_USE_PLUGINS_0=""
    fi
    AC_SUBST(COND_USE_PLUGINS_0)
dnl ### begin block 20_COND_USE_RTTI_0[explorer.bkl] ###
    COND_USE_RTTI_0="#"
    if test "x$USE_RTTI" = "x0" ; then
        COND_USE_RTTI_0=""
    fi
    AC_SUBST(COND_USE_RTTI_0)
dnl ### begin block 20_COND_USE_RTTI_1[explorer.bkl] ###
    COND_USE_RTTI_1="#"
    if test "x$USE_RTTI" = "x1" ; then
        COND_USE_RTTI_1=""
    fi
    AC_SUBST(COND_USE_RTTI_1)
dnl ### begin block 20_COND_USE_THREADS_0[explorer.bkl] ###
    COND_USE_THREADS_0="#"
    if test "x$USE_THREADS" = "x0" ; then
        COND_USE_THREADS_0=""
    fi
    AC_SUBST(COND_USE_THREADS_0)
dnl ### begin block 20_COND_USE_THREADS_1[explorer.bkl] ###
    COND_USE_THREADS_1="#"
    if test "x$USE_THREADS" = "x1" ; then
        COND_USE_THREADS_1=""
    fi
    AC_SUBST(COND_USE_THREADS_1)
dnl ### begin block 20_COND_WXUNIV_1[explorer.bkl] ###
    COND_WXUNIV_1="#"
    if test "x$WXUNIV" = "x1" ; then
        COND_WXUNIV_1=""
    fi
    AC_SUBST(COND_WXUNIV_1)
dnl ### begin block 20_COND_wxUSE_EXPAT_builtin[explorer.bkl] ###
    COND_wxUSE_EXPAT_builtin="#"
    if test "x$wxUSE_EXPAT" = "xbuiltin" ; then
        COND_wxUSE_EXPAT_builtin=""
    fi
    AC_SUBST(COND_wxUSE_EXPAT_builtin)
dnl ### begin block 20_COND_wxUSE_LIBJPEG_builtin[explorer.bkl] ###
    COND_wxUSE_LIBJPEG_builtin="#"
    if test "x$wxUSE_LIBJPEG" = "xbuiltin" ; then
        COND_wxUSE_LIBJPEG_builtin=""
    fi
    AC_SUBST(COND_wxUSE_LIBJPEG_builtin)
dnl ### begin block 20_COND_wxUSE_LIBPNG_builtin[explorer.bkl] ###
    COND_wxUSE_LIBPNG_builtin="#"
    if test "x$wxUSE_LIBPNG" = "xbuiltin" ; then
        COND_wxUSE_LIBPNG_builtin=""
    fi
    AC_SUBST(COND_wxUSE_LIBPNG_builtin)
dnl ### begin block 20_COND_wxUSE_LIBTIFF_builtin[explorer.bkl] ###
    COND_wxUSE_LIBTIFF_builtin="#"
    if test "x$wxUSE_LIBTIFF" = "xbuiltin" ; then
        COND_wxUSE_LIBTIFF_builtin=""
    fi
    AC_SUBST(COND_wxUSE_LIBTIFF_builtin)
dnl ### begin block 20_COND_wxUSE_REGEX_builtin[explorer.bkl] ###
    COND_wxUSE_REGEX_builtin="#"
    if test "x$wxUSE_REGEX" = "xbuiltin" ; then
        COND_wxUSE_REGEX_builtin=""
    fi
    AC_SUBST(COND_wxUSE_REGEX_builtin)
dnl ### begin block 20_COND_wxUSE_ZLIB_builtin[explorer.bkl] ###
    COND_wxUSE_ZLIB_builtin="#"
    if test "x$wxUSE_ZLIB" = "xbuiltin" ; then
        COND_wxUSE_ZLIB_builtin=""
    fi
    AC_SUBST(COND_wxUSE_ZLIB_builtin)
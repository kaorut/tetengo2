# Autoconf Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

#### General ####
AC_PREREQ([2.69])
AC_INIT([Tetengo2], [0.0.0], [kaorut@mc.pikara.ne.jp])
AM_INIT_AUTOMAKE([gnu dist-bzip2 dist-zip])
AC_CONFIG_SRCDIR([tetengo2_config.h-original])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    Makefile
    docsrc/Makefile
    precompiled/Makefile
    tetengo2/Makefile
    tetengo2/include/Makefile
    tetengo2/include/tetengo2/Makefile
    tetengo2/res.test/Makefile
    tetengo2/src/Makefile
    tetengo2/test/Makefile
    tetengo2_detail/Makefile
    tetengo2_detail/include/Makefile
    tetengo2_detail/include/tetengo2/Makefile
    tetengo2_detail/src/Makefile
    tetengo2_gui/Makefile
    tetengo2_gui/include/Makefile
    tetengo2_gui/include/tetengo2/Makefile
    tetengo2_gui/test/Makefile
    tools/Makefile
    vsprops/Makefile
])

AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

AC_ARG_ENABLE(
    precompilation,
    AS_HELP_STRING(
        [--enable-precompilation],
        [enables precompilation.]
    ),
    PRECOMPILE_CPPFLAGS=" -I\$(top_builddir)/precompiled -I\$(top_srcdir)/precompiled -include precompiled.h";
    PRECOMPILE_BUILT_SOURCES="\$(top_builddir)/precompiled/precompiled.h.gch"
)
AC_SUBST([PRECOMPILE_CPPFLAGS])
AC_SUBST([PRECOMPILE_BUILT_SOURCES])

#### Checks for programs ####
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_RANLIB
AC_ARG_WITH(
    doxygen,
    AS_HELP_STRING(
        [--with-doxygen=DIR],
        [
            Specify the directory of Doxygen. If set, ``$DIR/doxygen'' is
            used. Otherwise, ``doxygen'' is used.
        ]
    ),
    DOXYGEN=$withval/doxygen
)
AC_CHECK_PROG(DOXYGEN, doxygen, doxygen)
test -z $DOXYGEN && \
    AC_MSG_WARN([You cannot generate documentation for lack of Doxygen.])

#### Checks for libraries ####
AC_CHECK_FUNC(sem_open, , [AC_CHECK_LIB(rt, sem_open)])
AC_CHECK_LIB(pthread, pthread_cancel)
AC_CHECK_LIB(bz2, BZ2_bzCompressInit)
AC_CHECK_FUNC(iconv, , [AC_CHECK_LIB(iconv, libiconv)])

AX_BOOST_BASE([1.63.0])
AX_BOOST_CHRONO
AX_BOOST_DATE_TIME
AX_BOOST_FILESYSTEM
AX_BOOST_SYSTEM
AX_BOOST_THREAD
AX_BOOST_UNIT_TEST_FRAMEWORK
AC_SUBST([LDFLAGS], "$LDFLAGS $BOOST_LDFLAGS")
AC_SUBST([LIBS], "$BOOST_CHRONO_LIB $LIBS")
AC_SUBST([LIBS], "$BOOST_DATE_TIME_LIB $LIBS")
AC_SUBST([LIBS], "$BOOST_FILESYSTEM_LIB $LIBS")
AC_SUBST([LIBS], "$BOOST_SYSTEM_LIB $LIBS")
AC_SUBST([LIBS], "$BOOST_THREAD_LIB $LIBS")
AC_SUBST([UNITTEST_LIBS], "$BOOST_UNIT_TEST_FRAMEWORK_LIB")

#### Checks for header files ####
AC_CXX_HAVE_STD
AC_CXX_HAVE_STL
AC_HEADER_STDC
AC_SUBST([CPPFLAGS], "$CPPFLAGS $PRECOMPILE_CPPFLAGS")
AC_SUBST([CPPFLAGS], "$CPPFLAGS $BOOST_CPPFLAGS")

#### Checks for typedefs, structures, and compiler characteristics ####
AC_SUBST([CXXFLAGS], "$CXXFLAGS -Werror -Wall -Wextra -pedantic-errors")

#### Checks for library functions ####

#### Output ####
AC_OUTPUT

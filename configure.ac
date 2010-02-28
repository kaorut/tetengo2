# Autoconf Settings
# Copyright (C) 2007-2010 kaoru
# $Id$

#### General ####
AC_PREREQ([2.61])
AC_INIT([bobura], [0.0.0], [kaorut@mc.pikara.ne.jp])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([bobura_config.h-original])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    Makefile
    precompiled/Makefile
    bobura/Makefile
    bobura/src/Makefile
    bobura/test/Makefile
    bobura_model/Makefile
    bobura_model/include/Makefile
    bobura_model/test/Makefile
    tetengo2/Makefile
    tetengo2/include/Makefile
    tetengo2/test/Makefile
    tetengo2/res.test/Makefile
])

AC_ARG_ENABLE(
    precompilation,
    AS_HELP_STRING(
        [--enable-precompilation],
        [enables precompilation.]
    ),
    PRECOMPILE_CPPFLAGS=" -I\$(top_srcdir)/precompiled -include precompiled.h"
)
AC_SUBST(PRECOMPILE_CPPFLAGS)


#### Checks for programs ####
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
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
AX_BOOST_BASE([1.41]) 
AX_BOOST_FILESYSTEM
AX_BOOST_PROGRAM_OPTIONS
AX_BOOST_SIGNALS
AX_BOOST_SYSTEM
AX_BOOST_UNIT_TEST_FRAMEWORK

#### Checks for header files ####
AC_CXX_HAVE_STD
AC_CXX_HAVE_STL
AC_HEADER_STDC

#### Checks for typedefs, structures, and compiler characteristics ####
AC_CXX_TEMPLATES

#### Checks for library functions ####

#### Output ####
AC_OUTPUT

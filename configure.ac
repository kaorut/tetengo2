# Autoconf Settings
# Copyright (C) 2007-2009 kaoru
# $Id$

#### General ####
AC_PREREQ([2.64])
AC_INIT([bobura], [0.0.0], [kaorut@mc.pikara.ne.jp])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([bobura_config.h-original])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    Makefile
])

#### Checks for programs ####
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP

#### Checks for libraries ####
AX_BOOST_BASE([1.41]) 

#### Checks for header files ####

#### Checks for typedefs, structures, and compiler characteristics ####
AC_HEADER_STDBOOL
AC_HEADER_STDC
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

#### Checks for library functions ####

#### Output ####
AC_OUTPUT

# Automake Settings
# Copyright (C) 2007-2010 kaoru
# $Id$

headers =

extra_headers =

sources = \
    master.cpp \
    test_bobura.about_dialog.cpp \
    test_bobura.bobura.cpp \
    test_bobura.command.about.cpp \
    test_bobura.command.exit.cpp \
    test_bobura.command.nop.cpp \
    test_bobura.main_window.cpp \
    test_bobura.message.about_dialog_observers.cpp \
    test_bobura.message.main_window_observers.cpp \
    test_bobura.settings.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

check_PROGRAMS = bobura.test
EXTRA_DIST = $(extra_headers) $(extra_sources)

TESTS = bobura.test

bobura_test_CPPFLAGS = \
    $(PRECOMPILE_CPPFLAGS) \
    $(BOOST_CPPFLAGS) \
    -I$(top_srcdir)/bobura/src \
    -I$(top_srcdir)/bobura_model/include \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2/test
bobura_test_LDFLAGS = $(BOOST_LDFLAGS)
bobura_test_LDADD = \
    $(BOOST_FILESYSTEM_LIB) \
    $(BOOST_PROGRAM_OPTIONS_LIB) \
    $(BOOST_SIGNALS_LIB) \
    $(BOOST_SYSTEM_LIB) \
    $(BOOST_UNIT_TEST_FRAMEWORK_LIB)
bobura_test_SOURCES = $(headers) $(sources)

$(top_srcdir)/precompiled/precompiled.h.gch: $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_srcdir)/precompiled; $(MAKE) all; popd


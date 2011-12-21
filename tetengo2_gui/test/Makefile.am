# Automake Settings
# Copyright (C) 2007-2011 kaoru
# $Id$

headers =

extra_headers =

sources = \
    master.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

check_PROGRAMS = tetengo2_gui.test
EXTRA_DIST = $(extra_headers) $(extra_sources)

TESTS = tetengo2_gui.test

tetengo2_gui_test_CPPFLAGS = \
    $(PRECOMPILE_CPPFLAGS) \
    $(BOOST_CPPFLAGS) \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_gui/include
tetengo2_gui_test_LDFLAGS = $(BOOST_LDFLAGS)
tetengo2_gui_test_LDADD = \
    $(BOOST_DATE_TIME_LIB) \
    $(BOOST_FILESYSTEM_LIB) \
    $(BOOST_PROGRAM_OPTIONS_LIB) \
    $(BOOST_SYSTEM_LIB) \
    $(BOOST_THREAD_LIB) \
    $(BOOST_UNIT_TEST_FRAMEWORK_LIB)
tetengo2_gui_test_SOURCES = $(headers) $(sources)

clean-local:
	-rm -rf messages.test

$(top_srcdir)/precompiled/precompiled.h.gch: $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_srcdir)/precompiled; $(MAKE) all; popd


# Automake Settings
# Copyright (C) 2007-2012 kaoru
# $Id$

headers =

extra_headers =

sources = \
    master.cpp \
    test_bobura.about_dialog.cpp \
    test_bobura.application.cpp \
    test_bobura.command.about.cpp \
    test_bobura.command.exit.cpp \
    test_bobura.command.file_property.cpp \
    test_bobura.command.load_from_file.cpp \
    test_bobura.command.new_file.cpp \
    test_bobura.command.nop.cpp \
    test_bobura.confirm_file_save.cpp \
    test_bobura.file_property_dialog.cpp \
    test_bobura.main_window.cpp \
    test_bobura.message.about_dialog.cpp \
    test_bobura.message.file_property_dialog.cpp \
    test_bobura.message.main_window.cpp \
    test_bobura.message.timetable_model.cpp \
    test_bobura.message.timetable_model_observer_set.cpp \
    test_bobura.settings.cpp \
    test_bobura.timetable_model.cpp

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
    -I$(top_srcdir)/tetengo2_detail/include \
    -I$(top_srcdir)/tetengo2_gui/include
bobura_test_LDFLAGS = $(BOOST_LDFLAGS)
bobura_test_LDADD = \
    $(BOOST_FILESYSTEM_LIB) \
    $(BOOST_PROGRAM_OPTIONS_LIB) \
    $(BOOST_SYSTEM_LIB) \
    $(BOOST_THREAD_LIB) \
    $(BOOST_UNIT_TEST_FRAMEWORK_LIB)
bobura_test_SOURCES = $(headers) $(sources)

$(top_srcdir)/precompiled/precompiled.h.gch: $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_srcdir)/precompiled; $(MAKE) all; popd


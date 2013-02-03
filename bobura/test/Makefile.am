# Automake Settings
# Copyright (C) 2007-2013 kaoru
# $Id$

headers =

extra_headers =

sources = \
    master.cpp \
    test_bobura.about_dialog.cpp \
    test_bobura.diagram_picture_box.cpp \
    test_bobura.diagram_view.cpp \
    test_bobura.file_property_dialog.cpp \
    test_bobura.font_color_dialog.cpp \
    test_bobura.load_save.confirm_file_save.cpp \
    test_bobura.load_save.load_from_file.cpp \
    test_bobura.load_save.new_file.cpp \
    test_bobura.load_save.save_to_file.cpp \
    test_bobura.main_window.cpp \
    test_bobura.message.about_dialog.cpp \
    test_bobura.message.diagram_picture_box.cpp \
    test_bobura.message.file_property_dialog.cpp \
    test_bobura.message.font_color_dialog.cpp \
    test_bobura.message.main_window.cpp \
    test_bobura.message.oudia_diagram_dialog.cpp \
    test_bobura.message.timetable_model.cpp \
    test_bobura.message.timetable_model_observer_set.cpp \
    test_bobura.message.train_kind_dialog.cpp \
    test_bobura.oudia_diagram_dialog.cpp \
    test_bobura.settings.cpp \
    test_bobura.timetable_model.cpp \
    test_bobura.view.diagram.header.cpp \
    test_bobura.view.diagram.item.cpp \
    test_bobura.view.diagram.station_line.cpp \
    test_bobura.view.diagram.time_line.cpp \
    test_bobura.view.diagram.train_line.cpp \
    test_bobura.view.diagram.utility.cpp \
    test_bobura.view.scale_list.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

check_PROGRAMS = bobura.test
EXTRA_DIST = $(extra_headers) $(extra_sources)

TESTS = bobura.test

bobura_test_DEPENDENCIES = \
    $(top_builddir)/tetengo2/src/libtetengo2.a
bobura_test_CPPFLAGS = \
    $(PRECOMPILE_CPPFLAGS) \
    $(BOOST_CPPFLAGS) \
    -I$(top_srcdir)/bobura/src \
    -I$(top_srcdir)/bobura_model/include \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include \
    -I$(top_srcdir)/tetengo2_gui/include
bobura_test_LDFLAGS = \
    -L$(top_builddir)/tetengo2/src \
    $(BOOST_LDFLAGS)
bobura_test_LDADD = \
    -ltetengo2 \
    $(BOOST_FILESYSTEM_LIB) \
    $(BOOST_IOSTREAMS_LIB) \
    $(BOOST_PROGRAM_OPTIONS_LIB) \
    $(BOOST_SYSTEM_LIB) \
    $(BOOST_THREAD_LIB) \
    $(BOOST_UNIT_TEST_FRAMEWORK_LIB)
bobura_test_SOURCES = $(headers) $(sources)

$(top_srcdir)/precompiled/precompiled.h.gch: $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_srcdir)/precompiled; $(MAKE) all; popd

$(top_builddir)/tetengo2/src/libtetengo2.a:
	pushd $(top_srcdir)/tetengo2/src; $(MAKE) all; popd


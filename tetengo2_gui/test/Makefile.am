# Automake Settings
# Copyright (C) 2007-2011 kaoru
# $Id$

headers =

extra_headers =

sources = \
    master.cpp \
    test_tetengo2.gui.abstract_popup_menu.cpp \
    test_tetengo2.gui.abstract_window.cpp \
    test_tetengo2.gui.alert.cpp \
    test_tetengo2.gui.button.cpp \
    test_tetengo2.gui.control.cpp \
    test_tetengo2.gui.cursor.cpp \
    test_tetengo2.gui.dialog.cpp \
    test_tetengo2.gui.dialog_message_loop.cpp \
    test_tetengo2.gui.drawing.background.cpp \
    test_tetengo2.gui.drawing.canvas.cpp \
    test_tetengo2.gui.drawing.color.cpp \
    test_tetengo2.gui.drawing.font.cpp \
    test_tetengo2.gui.drawing.picture.cpp \
    test_tetengo2.gui.drawing.picture_reader.cpp \
    test_tetengo2.gui.drawing.solid_background.cpp \
    test_tetengo2.gui.drawing.transparent_background.cpp \
    test_tetengo2.gui.drawing.widget_canvas.cpp \
    test_tetengo2.gui.fixture.cpp \
    test_tetengo2.gui.image.cpp \
    test_tetengo2.gui.label.cpp \
    test_tetengo2.gui.link_label.cpp \
    test_tetengo2.gui.measure.cpp \
    test_tetengo2.gui.main_menu.cpp \
    test_tetengo2.gui.menu.cpp \
    test_tetengo2.gui.menu_command.cpp \
    test_tetengo2.gui.menu_observer_set.cpp \
    test_tetengo2.gui.menu_separator.cpp \
    test_tetengo2.gui.message_loop.cpp \
    test_tetengo2.gui.message_loop_break.cpp \
    test_tetengo2.gui.mouse_observer_set.cpp \
    test_tetengo2.gui.paint_observer_set.cpp \
    test_tetengo2.gui.popup_menu.cpp \
    test_tetengo2.gui.recursive_menu_iterator.cpp \
    test_tetengo2.gui.system_cursor.cpp \
    test_tetengo2.gui.unit.em.cpp \
    test_tetengo2.gui.unit.pixel.cpp \
    test_tetengo2.gui.unit.unit.cpp \
    test_tetengo2.gui.widget.cpp \
    test_tetengo2.gui.window.cpp \
    test_tetengo2.gui.window_observer_set.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

check_PROGRAMS = tetengo2_gui.test
EXTRA_DIST = $(extra_headers) $(extra_sources)

TESTS = tetengo2_gui.test

tetengo2_gui_test_CPPFLAGS = \
    $(PRECOMPILE_CPPFLAGS) \
    $(BOOST_CPPFLAGS) \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include \
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

$(top_srcdir)/precompiled/precompiled.h.gch: $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_srcdir)/precompiled; $(MAKE) all; popd


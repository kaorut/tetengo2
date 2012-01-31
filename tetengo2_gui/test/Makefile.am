# Automake Settings
# Copyright (C) 2007-2012 kaoru
# $Id$

headers =

extra_headers =

sources = \
    master.cpp \
    test_tetengo2.gui.alert.cpp \
    test_tetengo2.gui.common_dialog.file_open.cpp \
    test_tetengo2.gui.common_dialog.message_box.cpp \
    test_tetengo2.gui.cursor.cursor_base.cpp \
    test_tetengo2.gui.cursor.system.cpp \
    test_tetengo2.gui.drawing.background.cpp \
    test_tetengo2.gui.drawing.canvas.cpp \
    test_tetengo2.gui.drawing.color.cpp \
    test_tetengo2.gui.drawing.font.cpp \
    test_tetengo2.gui.drawing.picture.cpp \
    test_tetengo2.gui.drawing.picture_reader.cpp \
    test_tetengo2.gui.drawing.solid_background.cpp \
    test_tetengo2.gui.drawing.system_color_set.cpp \
    test_tetengo2.gui.drawing.transparent_background.cpp \
    test_tetengo2.gui.drawing.widget_canvas.cpp \
    test_tetengo2.gui.fixture.cpp \
    test_tetengo2.gui.measure.cpp \
    test_tetengo2.gui.menu.abstract_popup.cpp \
    test_tetengo2.gui.menu.command.cpp \
    test_tetengo2.gui.menu.menu_bar.cpp \
    test_tetengo2.gui.menu.menu_base.cpp \
    test_tetengo2.gui.menu.popup.cpp \
    test_tetengo2.gui.menu.recursive_iterator.cpp \
    test_tetengo2.gui.menu.separator.cpp \
    test_tetengo2.gui.menu.shortcut_key.cpp \
    test_tetengo2.gui.menu.shortcut_key_table.cpp \
    test_tetengo2.gui.message.dialog_message_loop.cpp \
    test_tetengo2.gui.message.focus_observer_set.cpp \
    test_tetengo2.gui.message.keyboard_observer_set.cpp \
    test_tetengo2.gui.message.menu_observer_set.cpp \
    test_tetengo2.gui.message.message_loop.cpp \
    test_tetengo2.gui.message.message_loop_break.cpp \
    test_tetengo2.gui.message.mouse_observer_set.cpp \
    test_tetengo2.gui.message.paint_observer_set.cpp \
    test_tetengo2.gui.message.window_observer_set.cpp \
    test_tetengo2.gui.unit.em.cpp \
    test_tetengo2.gui.unit.pixel.cpp \
    test_tetengo2.gui.unit.unit.cpp \
    test_tetengo2.gui.virtual_key.cpp \
    test_tetengo2.gui.widget.abstract_window.cpp \
    test_tetengo2.gui.widget.button.cpp \
    test_tetengo2.gui.widget.control.cpp \
    test_tetengo2.gui.widget.dialog.cpp \
    test_tetengo2.gui.widget.image.cpp \
    test_tetengo2.gui.widget.label.cpp \
    test_tetengo2.gui.widget.link_label.cpp \
    test_tetengo2.gui.widget.text_box.cpp \
    test_tetengo2.gui.widget.widget.cpp \
    test_tetengo2.gui.widget.window.cpp

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


# Automake Settings
# Copyright (C) 2007-2011 kaoru
# $Id$

headers = \
    stub_tetengo2.encoding.utf8.h \
    stub_tetengo2.gui.abstract_popup_menu.h \
    stub_tetengo2.gui.abstract_window.h \
    stub_tetengo2.gui.alert.h \
    stub_tetengo2.gui.button.h \
    stub_tetengo2.gui.control.h \
    stub_tetengo2.gui.dialog.h \
    stub_tetengo2.gui.drawing.canvas.h \
    stub_tetengo2.gui.drawing.picture.h \
    stub_tetengo2.gui.drawing.picture_reader.h \
    stub_tetengo2.gui.drawing.transparent_background.h \
    stub_tetengo2.gui.drawing.widget_canvas.h \
    stub_tetengo2.gui.font.h \
    stub_tetengo2.gui.gui_initializer_finalizer.h \
    stub_tetengo2.gui.image.h \
    stub_tetengo2.gui.label.h \
    stub_tetengo2.gui.main_menu.h \
    stub_tetengo2.gui.menu.h \
    stub_tetengo2.gui.menu_command.h \
    stub_tetengo2.gui.menu_separator.h \
    stub_tetengo2.gui.message_loop.h \
    stub_tetengo2.gui.popup_menu.h \
    stub_tetengo2.gui.quit_message_loop.h \
    stub_tetengo2.gui.unit.win32.em.h \
    stub_tetengo2.gui.widget.h \
    stub_tetengo2.gui.window.h

extra_headers =

sources = \
    master.cpp \
    test_tetengo2.encoder.cpp \
    test_tetengo2.generator.cpp \
    test_tetengo2.message_catalog.cpp \
    test_tetengo2.message_catalog_parser.cpp \
    test_tetengo2.messages.cpp \
    test_tetengo2.text.cpp \
    test_tetengo2.encoding.encoding.cpp \
    test_tetengo2.encoding.ascii.cpp \
    test_tetengo2.encoding.locale.cpp \
    test_tetengo2.gui.drawing.background.cpp \
    test_tetengo2.gui.drawing.color.cpp \
    test_tetengo2.gui.measure.cpp \
    test_tetengo2.gui.menu_observer_set.cpp \
    test_tetengo2.gui.mouse_observer_set.cpp \
    test_tetengo2.gui.paint_observer_set.cpp \
    test_tetengo2.gui.recursive_menu_iterator.cpp \
    test_tetengo2.gui.unit.pixel.cpp \
    test_tetengo2.gui.window_observer_set.cpp \
    test_tetengo2.meta.assoc_list.cpp \
    test_tetengo2.operators.cpp

extra_sources = \
    test_tetengo2.encoding.win32.utf8.cpp \
    test_tetengo2.gui.drawing.win32.gdiplus.canvas.cpp \
    test_tetengo2.gui.drawing.win32.gdiplus.picture.cpp \
    test_tetengo2.gui.drawing.win32.gdiplus.picture_reader.cpp \
    test_tetengo2.gui.drawing.win32.gdiplus.transparent_background.cpp \
    test_tetengo2.gui.drawing.win32.gdiplus.window_canvas.cpp \
    test_tetengo2.gui.unit.win32.em.cpp \
    test_tetengo2.gui.win32.abstract_popup_menu.cpp \
    test_tetengo2.gui.win32.abstract_window.cpp \
    test_tetengo2.gui.win32.alert.cpp \
    test_tetengo2.gui.win32.button.cpp \
    test_tetengo2.gui.win32.control.cpp \
    test_tetengo2.gui.win32.dialog.cpp \
    test_tetengo2.gui.win32.dialog_message_loop.cpp \
    test_tetengo2.gui.win32.font.cpp \
    test_tetengo2.gui.win32.gui_initializer_finalizer.cpp \
    test_tetengo2.gui.win32.image.cpp \
    test_tetengo2.gui.win32.label.cpp \
    test_tetengo2.gui.win32.main_menu.cpp \
    test_tetengo2.gui.win32.menu.cpp \
    test_tetengo2.gui.win32.menu_command.cpp \
    test_tetengo2.gui.win32.menu_separator.cpp \
    test_tetengo2.gui.win32.message_loop.cpp \
    test_tetengo2.gui.win32.popup_menu.cpp \
    test_tetengo2.gui.win32.quit_message_loop.cpp \
    test_tetengo2.gui.win32.widget.cpp \
    test_tetengo2.gui.win32.window.cpp

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

check_PROGRAMS = tetengo2.test
EXTRA_DIST = $(extra_headers) $(extra_sources)

TESTS = tetengo2.test

tetengo2_test_DEPENDENCIES = \
    messages.test
tetengo2_test_CPPFLAGS = \
    $(PRECOMPILE_CPPFLAGS) \
    $(BOOST_CPPFLAGS) \
    -I$(top_srcdir)/tetengo2/include
tetengo2_test_LDFLAGS = $(BOOST_LDFLAGS)
tetengo2_test_LDADD = \
    $(BOOST_FILESYSTEM_LIB) \
    $(BOOST_PROGRAM_OPTIONS_LIB) \
    $(BOOST_SYSTEM_LIB) \
    $(BOOST_UNIT_TEST_FRAMEWORK_LIB)
tetengo2_test_SOURCES = $(headers) $(sources)

messages.test:
	cp -r $(top_srcdir)/tetengo2/res.test/messages.test .

clean-local:
	-rm -rf messages.test

$(top_srcdir)/precompiled/precompiled.h.gch: $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_srcdir)/precompiled; $(MAKE) all; popd


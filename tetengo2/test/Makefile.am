# Automake Settings
# Copyright (C) 2007-2010 kaoru
# $Id$

headers = \
    stub_tetengo2.encode.h \
    stub_tetengo2.gui.abstract_window.h \
    stub_tetengo2.gui.alert.h \
    stub_tetengo2.gui.button.h \
    stub_tetengo2.gui.canvas.h \
    stub_tetengo2.gui.dialog.h \
    stub_tetengo2.gui.font.h \
    stub_tetengo2.gui.gui_initializer_finalizer.h \
    stub_tetengo2.gui.gui_type_list.h \
    stub_tetengo2.gui.main_menu.h \
    stub_tetengo2.gui.menu_item.h \
    stub_tetengo2.gui.message_loop.h \
    stub_tetengo2.gui.popup_menu.h \
    stub_tetengo2.gui.quit_message_loop.h \
    stub_tetengo2.gui.widget.h \
    stub_tetengo2.gui.window.h

extra_headers =

sources = \
    master.cpp \
    test_tetengo2.generator.cpp \
    test_tetengo2.gui.menu_command.cpp \
    test_tetengo2.gui.menu_observer.cpp \
    test_tetengo2.gui.menu_separator.cpp \
    test_tetengo2.gui.mouse_observer.cpp \
    test_tetengo2.gui.paint_observer.cpp \
    test_tetengo2.gui.window_observer.cpp \
    test_tetengo2.message_catalog.cpp \
    test_tetengo2.message_catalog_parser.cpp \
    test_tetengo2.messages.cpp

extra_sources = \
    test_tetengo2.gui.win32.abstract_window.cpp \
    test_tetengo2.gui.win32.alert.cpp \
    test_tetengo2.gui.win32.button.cpp \
    test_tetengo2.gui.win32.canvas.cpp \
    test_tetengo2.gui.win32.dialog.cpp \
    test_tetengo2.gui.win32.dialog_message_loop.cpp \
    test_tetengo2.gui.win32.font.cpp \
    test_tetengo2.gui.win32.gui_initializer_finalizer.cpp \
    test_tetengo2.gui.win32.gui_type_list.cpp \
    test_tetengo2.gui.win32.main_menu.cpp \
    test_tetengo2.gui.win32.menu_item.cpp \
    test_tetengo2.gui.win32.message_loop.cpp \
    test_tetengo2.gui.win32.popup_menu.cpp \
    test_tetengo2.gui.win32.quit_message_loop.cpp \
    test_tetengo2.gui.win32.widget.cpp \
    test_tetengo2.gui.win32.window.cpp \
    test_tetengo2.win32.encode.cpp

check_PROGRAMS = tetengo2.test
EXTRA_DIST = $(extra_headers) $(extra_sources)

TESTS = tetengo2.test

tetengo2_test_CPPFLAGS = \
    $(BOOST_CPPFLAGS) \
    -I$(top_srcdir)/tetengo2/include
tetengo2_test_LDFLAGS = $(BOOST_LDFLAGS)
tetengo2_test_LDADD = \
    $(BOOST_FILESYSTEM_LIB) \
    $(BOOST_PROGRAM_OPTIONS_LIB) \
    $(BOOST_SIGNALS_LIB) \
    $(BOOST_SYSTEM_LIB) \
    $(BOOST_UNIT_TEST_FRAMEWORK_LIB)
tetengo2_test_SOURCES = $(headers) $(sources)

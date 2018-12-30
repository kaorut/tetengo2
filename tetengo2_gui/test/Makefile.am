# Automake Settings
# Copyright (C) 2007-2019 kaoru
# $Id$

headers = \
    test_tetengo2.gui.detail_type_list.h \
    test_tetengo2.gui.type_list.h

extra_headers =

sources = \
    master.cpp \
    test_tetengo2.gui.alert.cpp \
    test_tetengo2.gui.common_dialog.color.cpp \
    test_tetengo2.gui.common_dialog.file_open.cpp \
    test_tetengo2.gui.common_dialog.file_save.cpp \
    test_tetengo2.gui.common_dialog.font.cpp \
    test_tetengo2.gui.common_dialog.message_box.cpp \
    test_tetengo2.gui.cursor.cursor_base.cpp \
    test_tetengo2.gui.cursor.system.cpp \
    test_tetengo2.gui.dimension.cpp \
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
    test_tetengo2.gui.icon.cpp \
    test_tetengo2.gui.menu.abstract_popup.cpp \
    test_tetengo2.gui.menu.command.cpp \
    test_tetengo2.gui.menu.menu_bar.cpp \
    test_tetengo2.gui.menu.menu_base.cpp \
    test_tetengo2.gui.menu.popup.cpp \
    test_tetengo2.gui.menu.recursive_iterator.cpp \
    test_tetengo2.gui.menu.separator.cpp \
    test_tetengo2.gui.menu.shortcut_key.cpp \
    test_tetengo2.gui.menu.shortcut_key_table.cpp \
    test_tetengo2.gui.message.child_observer_set.cpp \
    test_tetengo2.gui.message.dialog_message_loop.cpp \
    test_tetengo2.gui.message.file_drop_observer_set.cpp \
    test_tetengo2.gui.message.focus_observer_set.cpp \
    test_tetengo2.gui.message.keyboard_observer_set.cpp \
    test_tetengo2.gui.message.list_selection_observer_set.cpp \
    test_tetengo2.gui.message.menu_observer_set.cpp \
    test_tetengo2.gui.message.message_loop.cpp \
    test_tetengo2.gui.message.message_loop_break.cpp \
    test_tetengo2.gui.message.mouse_observer_set.cpp \
    test_tetengo2.gui.message.paint_observer_set.cpp \
    test_tetengo2.gui.message.scroll_bar_observer_set.cpp \
    test_tetengo2.gui.message.size_observer_set.cpp \
    test_tetengo2.gui.message.text_box_observer_set.cpp \
    test_tetengo2.gui.message.window_observer_set.cpp \
    test_tetengo2.gui.mouse_capture.cpp \
    test_tetengo2.gui.position.cpp \
    test_tetengo2.gui.scroll_bar.cpp \
    test_tetengo2.gui.shell.cpp \
    test_tetengo2.gui.timer.cpp \
    test_tetengo2.gui.unit.em.cpp \
    test_tetengo2.gui.unit.pixel.cpp \
    test_tetengo2.gui.unit.point.cpp \
    test_tetengo2.gui.unit.unit.cpp \
    test_tetengo2.gui.virtual_key.cpp \
    test_tetengo2.gui.widget.abstract_window.cpp \
    test_tetengo2.gui.widget.button.cpp \
    test_tetengo2.gui.widget.control.cpp \
    test_tetengo2.gui.widget.custom_control.cpp \
    test_tetengo2.gui.widget.dialog.cpp \
    test_tetengo2.gui.widget.dropdown_box.cpp \
    test_tetengo2.gui.widget.image.cpp \
    test_tetengo2.gui.widget.label.cpp \
    test_tetengo2.gui.widget.link_label.cpp \
    test_tetengo2.gui.widget.list_box.cpp \
    test_tetengo2.gui.widget.map_box.cpp \
    test_tetengo2.gui.widget.picture_box.cpp \
    test_tetengo2.gui.widget.progress_bar.cpp \
    test_tetengo2.gui.widget.progress_dialog.cpp \
    test_tetengo2.gui.widget.side_bar.cpp \
    test_tetengo2.gui.widget.tab_frame.cpp \
    test_tetengo2.gui.widget.text_box.cpp \
    test_tetengo2.gui.widget.widget.cpp \
    test_tetengo2.gui.widget.window.cpp

extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

check_PROGRAMS = tetengo2_gui.test
EXTRA_DIST = $(extra_headers) $(extra_sources)

TESTS = tetengo2_gui.test

tetengo2_gui_test_DEPENDENCIES = \
    $(top_builddir)/tetengo2/src/libtetengo2.a \
    $(top_builddir)/tetengo2/src/libtetengo2_gui.a \
    $(top_builddir)/tetengo2/src/libtetengo2_detail.a
tetengo2_gui_test_CPPFLAGS = \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_gui/include \
    -I$(top_srcdir)/tetengo2_detail/include
tetengo2_gui_test_LDFLAGS = \
    -L$(top_builddir)/tetengo2/src \
    -L$(top_builddir)/tetengo2_gui/src \
    -L$(top_builddir)/tetengo2_detail/src
tetengo2_gui_test_LDADD = \
    -ltetengo2_gui \
    -ltetengo2 \
    -ltetengo2_detail \
    $(UNITTEST_LIBS)
tetengo2_gui_test_SOURCES = $(headers) $(sources)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)

lint-iwyu: $(addsuffix .iwyuout, $(headers) $(sources))

lint-iwyu-extra: $(addsuffix .iwyuout, $(extra_headers) $(extra_sources))

%.iwyuout: %
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(tetengo2_gui_test_CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || true
	mv $(addsuffix .tmp, $@) $@

format:
	$(top_srcdir)/tools/call_clang-format.sh $(UNIX2DOS) $(CLANGFORMAT) $(srcdir) $(headers) $(sources) $(extra_headers) $(extra_sources)

clean-local:
	-rm -f *.iwyuout.tmp
	-rm -f *.iwyuout

$(top_builddir)/precompiled/precompiled.h.$(PRECOMPILE_EXT): $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_builddir)/precompiled; \
	$(MAKE) all; \
	popd

$(top_builddir)/tetengo2/src/libtetengo2.a:
	pushd $(top_builddir)/tetengo2/src; \
	$(MAKE) all; \
	popd

$(top_builddir)/tetengo2/src/libtetengo2_gui.a:
	pushd $(top_builddir)/tetengo2_gui/src; \
	$(MAKE) all; \
	popd

$(top_builddir)/tetengo2/src/libtetengo2_detail.a:
	pushd $(top_builddir)/tetengo2_detail/src; \
	$(MAKE) all; \
	popd

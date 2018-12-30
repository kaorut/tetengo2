# Automake Settings
# Copyright (C) 2007-2019 kaoru
# $Id$

headers =

extra_headers =

sources = \
    tetengo2.gui.alert.cpp \
    tetengo2.gui.common_dialog.color.cpp \
    tetengo2.gui.common_dialog.file_open.cpp \
    tetengo2.gui.common_dialog.file_save.cpp \
    tetengo2.gui.common_dialog.font.cpp \
    tetengo2.gui.common_dialog.message_box.cpp \
    tetengo2.gui.cursor.cursor_base.cpp \
    tetengo2.gui.cursor.system.cpp \
    tetengo2.gui.dimension.cpp \
    tetengo2.gui.drawing.background.cpp \
    tetengo2.gui.drawing.canvas.cpp \
    tetengo2.gui.drawing.color.cpp \
    tetengo2.gui.drawing.font.cpp \
    tetengo2.gui.drawing.picture.cpp \
    tetengo2.gui.drawing.picture_reader.cpp \
    tetengo2.gui.drawing.solid_background.cpp \
    tetengo2.gui.drawing.system_color_set.cpp \
    tetengo2.gui.drawing.transparent_background.cpp \
    tetengo2.gui.drawing.widget_canvas.cpp \
    tetengo2.gui.fixture.cpp \
    tetengo2.gui.icon.cpp \
    tetengo2.gui.menu.abstract_popup.cpp \
    tetengo2.gui.menu.command.cpp \
    tetengo2.gui.menu.menu_bar.cpp \
    tetengo2.gui.menu.menu_base.cpp \
    tetengo2.gui.menu.popup.cpp \
    tetengo2.gui.menu.recursive_iterator.cpp \
    tetengo2.gui.menu.separator.cpp \
    tetengo2.gui.menu.shortcut_key.cpp \
    tetengo2.gui.menu.shortcut_key_table.cpp \
    tetengo2.gui.message.child_observer_set.cpp \
    tetengo2.gui.message.dialog_message_loop.cpp \
    tetengo2.gui.message.file_drop_observer_set.cpp \
    tetengo2.gui.message.focus_observer_set.cpp \
    tetengo2.gui.message.keyboard_observer_set.cpp \
    tetengo2.gui.message.list_selection_observer_set.cpp \
    tetengo2.gui.message.menu_observer_set.cpp \
    tetengo2.gui.message.message_loop.cpp \
    tetengo2.gui.message.message_loop_break.cpp \
    tetengo2.gui.message.mouse_observer_set.cpp \
    tetengo2.gui.message.paint_observer_set.cpp \
    tetengo2.gui.message.scroll_bar_observer_set.cpp \
    tetengo2.gui.message.size_observer_set.cpp \
    tetengo2.gui.message.text_box_observer_set.cpp \
    tetengo2.gui.message.window_observer_set.cpp \
    tetengo2.gui.mouse_capture.cpp \
    tetengo2.gui.position.cpp \
    tetengo2.gui.scroll_bar.cpp \
    tetengo2.gui.shell.cpp \
    tetengo2.gui.timer.cpp \
    tetengo2.gui.unit.em.cpp \
    tetengo2.gui.unit.pixel.cpp \
    tetengo2.gui.unit.point.cpp \
    tetengo2.gui.widget.window.cpp \
    tetengo2.gui.widget.abstract_window.cpp \
    tetengo2.gui.widget.button.cpp \
    tetengo2.gui.widget.control.cpp \
    tetengo2.gui.widget.custom_control.cpp \
    tetengo2.gui.widget.dialog.cpp \
    tetengo2.gui.widget.dropdown_box.cpp \
    tetengo2.gui.widget.image.cpp \
    tetengo2.gui.widget.label.cpp \
    tetengo2.gui.widget.link_label.cpp \
    tetengo2.gui.widget.list_box.cpp \
    tetengo2.gui.widget.map_box.cpp \
    tetengo2.gui.widget.picture_box.cpp \
    tetengo2.gui.widget.progress_bar.cpp \
    tetengo2.gui.widget.progress_dialog.cpp \
    tetengo2.gui.widget.side_bar.cpp \
    tetengo2.gui.widget.tab_frame.cpp \
    tetengo2.gui.widget.text_box.cpp \
    tetengo2.gui.widget.widget.cpp \
    tetengo2.gui.virtual_key.cpp


extra_sources =

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

lib_LIBRARIES = libtetengo2_gui.a
EXTRA_DIST = $(extra_headers) $(extra_sources)

libtetengo2_gui_a_CPPFLAGS = \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include \
    -I$(top_srcdir)/tetengo2_gui/include
libtetengo2_gui_a_SOURCES = $(headers) $(sources)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)

lint-iwyu: $(addsuffix .iwyuout, $(headers) $(sources))

lint-iwyu-extra: $(addsuffix .iwyuout, $(extra_headers) $(extra_sources))

%.iwyuout: %
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(libtetengo2_gui_a_CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || true
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

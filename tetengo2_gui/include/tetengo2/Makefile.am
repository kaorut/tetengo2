# Automake Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

pkg_headers = \
    gui/alert.h \
    gui/common_dialog/color.h \
    gui/common_dialog/file_open.h \
    gui/common_dialog/file_save.h \
    gui/common_dialog/font.h \
    gui/common_dialog/message_box.h \
    gui/cursor/cursor_base.h \
    gui/cursor/system.h \
    gui/cursor/system_cursor_style.h \
    gui/dimension.h \
    gui/drawing/background.h \
    gui/drawing/canvas.h \
    gui/drawing/canvas_traits.h \
    gui/drawing/color.h \
    gui/drawing/font.h \
    gui/drawing/picture.h \
    gui/drawing/picture_reader.h \
    gui/drawing/solid_background.h \
    gui/drawing/system_color_set.h \
    gui/drawing/transparent_background.h \
    gui/drawing/widget_canvas.h \
    gui/fixture.h \
    gui/icon.h \
    gui/measure.h \
    gui/menu/abstract_popup.h \
    gui/menu/command.h \
    gui/menu/menu_bar.h \
    gui/menu/menu_base.h \
    gui/menu/popup.h \
    gui/menu/recursive_iterator.h \
    gui/menu/separator.h \
    gui/menu/shortcut_key.h \
    gui/menu/shortcut_key_table.h \
    gui/message/child_observer_set.h \
    gui/message/dialog_message_loop.h \
    gui/message/file_drop_observer_set.h \
    gui/message/focus_observer_set.h \
    gui/message/keyboard_observer_set.h \
    gui/message/list_selection_observer_set.h \
    gui/message/menu_observer_set.h \
    gui/message/message_loop.h \
    gui/message/message_loop_break.h \
    gui/message/mouse_observer_set.h \
    gui/message/paint_observer_set.h \
    gui/message/scroll_bar_observer_set.h \
    gui/message/size_observer_set.h \
    gui/message/text_box_observer_set.h \
    gui/message/window_observer_set.h \
    gui/mouse_capture.h \
    gui/position.h \
    gui/scroll_bar.h \
    gui/shell.h \
    gui/timer.h \
    gui/unit/em.h \
    gui/unit/pixel.h \
    gui/unit/point.h \
    gui/unit/unit.h \
    gui/virtual_key.h \
    gui/widget/abstract_window.h \
    gui/widget/button.h \
    gui/widget/control.h \
    gui/widget/custom_control.h \
    gui/widget/dialog.h \
    gui/widget/dropdown_box.h \
    gui/widget/image.h \
    gui/widget/label.h \
    gui/widget/link_label.h \
    gui/widget/list_box.h \
    gui/widget/map_box.h \
    gui/widget/picture_box.h \
    gui/widget/progress_bar.h \
    gui/widget/progress_dialog.h \
    gui/widget/side_bar.h \
    gui/widget/tab_frame.h \
    gui/widget/text_box.h \
    gui/widget/widget.h \
    gui/widget/widget_details_traits.h \
    gui/widget/widget_traits.h \
    gui/widget/window.h

extra_headers = \
    gui/0namespace.dox \
    gui/common_dialog/0namespace.dox \
    gui/cursor/0namespace.dox \
    gui/drawing/0namespace.dox \
    gui/menu/0namespace.dox \
    gui/message/0namespace.dox \
    gui/unit/0namespace.dox \
    gui/widget/0namespace.dox

nobase_pkginclude_HEADERS = $(pkg_headers)
EXTRA_DIST = $(extra_headers)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)
iwyu_CPPFLAGS = \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include \
    -I$(top_srcdir)/tetengo2_gui/include

lint-iwyu:
	for f in $(pkg_headers); \
	do \
	    echo "iwyu: "$(srcdir)/$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(iwyu_CPPFLAGS) $(CXXFLAGS) $(srcdir)/$$f || test $$? -eq 2; \
	done

lint-iwyu-extra:
	for f in $(extra_headers); \
	do \
	    echo "iwyu: "$(srcdir)/$$f; \
	    $(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(iwyu_CPPFLAGS) $(CXXFLAGS) $(srcdir)/$$f || test $$? -eq 2; \
	done

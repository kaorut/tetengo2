/*! \file
    \brief The facade of tetengo2::gui.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_H)
#define TETENGO2_GUI_H


#include <tetengo2/gui/alert.h>
#include <tetengo2/gui/common_dialog/color.h>
#include <tetengo2/gui/common_dialog/file_open.h>
#include <tetengo2/gui/common_dialog/file_save.h>
#include <tetengo2/gui/common_dialog/font.h>
#include <tetengo2/gui/common_dialog/message_box.h>
#include <tetengo2/gui/cursor/cursor_base.h>
#include <tetengo2/gui/cursor/system.h>
#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/canvas.h>
#include <tetengo2/gui/drawing/canvas_traits.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/drawing/picture.h>
#include <tetengo2/gui/drawing/picture_reader.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/system_color_set.h>
#include <tetengo2/gui/drawing/transparent_background.h>
#include <tetengo2/gui/drawing/widget_canvas.h>
#include <tetengo2/gui/fixture.h>
#include <tetengo2/gui/icon.h>
#include <tetengo2/gui/measure.h>
#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/command.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/gui/menu/popup.h>
#include <tetengo2/gui/menu/recursive_iterator.h>
#include <tetengo2/gui/menu/separator.h>
#include <tetengo2/gui/menu/shortcut_key.h>
#include <tetengo2/gui/menu/shortcut_key_table.h>
#include <tetengo2/gui/message/child_observer_set.h>
#include <tetengo2/gui/message/dialog_message_loop.h>
#include <tetengo2/gui/message/file_drop_observer_set.h>
#include <tetengo2/gui/message/focus_observer_set.h>
#include <tetengo2/gui/message/keyboard_observer_set.h>
#include <tetengo2/gui/message/list_selection_observer_set.h>
#include <tetengo2/gui/message/menu_observer_set.h>
#include <tetengo2/gui/message/message_loop.h>
#include <tetengo2/gui/message/message_loop_break.h>
#include <tetengo2/gui/message/mouse_observer_set.h>
#include <tetengo2/gui/message/paint_observer_set.h>
#include <tetengo2/gui/message/scroll_bar_observer_set.h>
#include <tetengo2/gui/message/size_observer_set.h>
#include <tetengo2/gui/message/text_box_observer_set.h>
#include <tetengo2/gui/message/window_observer_set.h>
#include <tetengo2/gui/mouse_capture.h>
#include <tetengo2/gui/scroll_bar.h>
#include <tetengo2/gui/shell.h>
#include <tetengo2/gui/timer.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/gui/unit/point.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/gui/virtual_key.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/gui/widget/button.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/custom_control.h>
#include <tetengo2/gui/widget/dialog.h>
#include <tetengo2/gui/widget/dropdown_box.h>
#include <tetengo2/gui/widget/image.h>
#include <tetengo2/gui/widget/label.h>
#include <tetengo2/gui/widget/link_label.h>
#include <tetengo2/gui/widget/list_box.h>
#include <tetengo2/gui/widget/map_box.h>
#include <tetengo2/gui/widget/picture_box.h>
#include <tetengo2/gui/widget/progress_bar.h>
#include <tetengo2/gui/widget/progress_dialog.h>
#include <tetengo2/gui/widget/side_bar.h>
#include <tetengo2/gui/widget/tab_frame.h>
#include <tetengo2/gui/widget/text_box.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/gui/widget/widget_details_traits.h>
#include <tetengo2/gui/widget/widget_traits.h>
#include <tetengo2/gui/widget/window.h>


#endif

/*! \file
    \brief The definition of tetengo2::detail::stub::gui_impl_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <chrono>
#include <functional>
#include <memory>

#include <tetengo2/detail/base/alert.h>
#include <tetengo2/detail/base/common_dialog.h>
#include <tetengo2/detail/base/cursor.h>
#include <tetengo2/detail/base/drawing.h>
#include <tetengo2/detail/base/gui_fixture.h>
#include <tetengo2/detail/base/icon.h>
#include <tetengo2/detail/base/menu.h>
#include <tetengo2/detail/base/message_handler.h>
#include <tetengo2/detail/base/message_loop.h>
#include <tetengo2/detail/base/mouse_capture.h>
#include <tetengo2/detail/base/scroll.h>
#include <tetengo2/detail/base/shell.h>
#include <tetengo2/detail/base/system_color.h>
#include <tetengo2/detail/base/timer.h>
#include <tetengo2/detail/base/unit.h>
#include <tetengo2/detail/base/virtual_key.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/detail/stub/alert.h>
#include <tetengo2/detail/stub/common_dialog.h>
#include <tetengo2/detail/stub/cursor.h>
#include <tetengo2/detail/stub/drawing.h>
#include <tetengo2/detail/stub/gui_fixture.h>
#include <tetengo2/detail/stub/gui_impl_set.h>
#include <tetengo2/detail/stub/icon.h>
#include <tetengo2/detail/stub/menu.h>
#include <tetengo2/detail/stub/message_handler.h>
#include <tetengo2/detail/stub/message_loop.h>
#include <tetengo2/detail/stub/mouse_capture.h>
#include <tetengo2/detail/stub/scroll.h>
#include <tetengo2/detail/stub/shell.h>
#include <tetengo2/detail/stub/system_color.h>
#include <tetengo2/detail/stub/timer.h>
#include <tetengo2/detail/stub/unit.h>
#include <tetengo2/detail/stub/virtual_key.h>
#include <tetengo2/detail/stub/widget.h>

namespace tetengo2::gui::widget {
    class widget;
}


namespace tetengo2::detail::stub {
    const gui_impl_set& gui_impl_set::instance()
    {
        static const gui_impl_set singleton;
        return singleton;
    }

    gui_impl_set::~gui_impl_set() = default;

    gui_impl_set::gui_impl_set() = default;

    const base::alert& gui_impl_set::alert_impl() const
    {
        return alert::instance();
    }

    const base::common_dialog& gui_impl_set::common_dialog_impl() const
    {
        return common_dialog::instance();
    }

    const base::cursor& gui_impl_set::cursor_impl() const
    {
        return cursor::instance();
    }

    const base::drawing& gui_impl_set::drawing_impl() const
    {
        return drawing::instance();
    }

    const base::drawing& gui_impl_set::fast_drawing_impl() const
    {
        return drawing::instance();
    }

    std::unique_ptr<base::gui_fixture> gui_impl_set::create_gui_fixture_impl() const
    {
        return std::make_unique<gui_fixture>();
    }

    const base::icon& gui_impl_set::icon_impl() const
    {
        return icon::instance();
    }

    const base::menu& gui_impl_set::menu_impl() const
    {
        return menu::instance();
    }

    const base::message_handler& gui_impl_set::message_handler_impl() const
    {
        return message_handler::instance();
    }

    const base::message_loop& gui_impl_set::message_loop_impl() const
    {
        return message_loop::instance();
    }

    std::unique_ptr<base::mouse_capture>
    gui_impl_set::create_mouse_capture_impl(const gui::widget::widget& widget) const
    {
        return std::make_unique<mouse_capture>(widget);
    }

    const base::scroll& gui_impl_set::scroll_impl() const
    {
        return scroll::instance();
    }

    const base::shell& gui_impl_set::shell_impl() const
    {
        return shell::instance();
    }

    const base::system_color& gui_impl_set::system_color_impl() const
    {
        return system_color::instance();
    }

    std::unique_ptr<base::timer> gui_impl_set::crate_timer_impl(
        const gui::widget::widget&       widget,
        std::function<void(bool&)>       procedure,
        const std::chrono::milliseconds& interval,
        const bool                       once_only) const
    {
        return std::make_unique<timer>(widget, std::move(procedure), interval, once_only);
    }

    const base::unit& gui_impl_set::unit_impl() const
    {
        return unit::instance();
    }

    const base::virtual_key& gui_impl_set::virtual_key_impl() const
    {
        return virtual_key::instance();
    }

    const base::widget& gui_impl_set::widget_impl() const
    {
        return widget::instance();
    }
}

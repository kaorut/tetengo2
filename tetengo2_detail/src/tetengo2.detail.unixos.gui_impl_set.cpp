/*! \file
    \brief The definition of tetengo2::detail::unixos::gui_impl_set.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <cassert>
#include <chrono>
#include <functional>
#include <memory>
#include <stdexcept>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/unixos/gui_impl_set.h>
#include <tetengo2/stdalt.h>

namespace tetengo2 {
    namespace detail::base {
        class alert;
        class common_dialog;
        class cursor;
        class drawing;
        class gui_fixture;
        class icon;
        class menu;
        class message_handler;
        class message_loop;
        class mouse_capture;
        class scroll;
        class shell;
        class system_color;
        class timer;
        class unit;
        class virtual_key;
        class widget;
    }

    namespace gui::widget {
        class widget;
    }
}


namespace tetengo2::detail::unixos {
    const gui_impl_set& gui_impl_set::instance()
    {
        static const gui_impl_set singleton;
        return singleton;
    }

    gui_impl_set::~gui_impl_set() = default;

    gui_impl_set::gui_impl_set() = default;

    const base::alert& gui_impl_set::alert_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::common_dialog& gui_impl_set::common_dialog_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::cursor& gui_impl_set::cursor_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::drawing& gui_impl_set::drawing_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::drawing& gui_impl_set::fast_drawing_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    std::unique_ptr<base::gui_fixture> gui_impl_set::create_gui_fixture_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::icon& gui_impl_set::icon_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::menu& gui_impl_set::menu_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::message_handler& gui_impl_set::message_handler_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::message_loop& gui_impl_set::message_loop_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    std::unique_ptr<base::mouse_capture>
    gui_impl_set::create_mouse_capture_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::scroll& gui_impl_set::scroll_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::shell& gui_impl_set::shell_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::system_color& gui_impl_set::system_color_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    std::unique_ptr<base::timer> gui_impl_set::crate_timer_impl(
        TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget,
        TETENGO2_STDALT_MAYBE_UNUSED std::function<void(bool&)> procedure,
        TETENGO2_STDALT_MAYBE_UNUSED const std::chrono::milliseconds& interval,
        TETENGO2_STDALT_MAYBE_UNUSED const bool                       once_only) const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::unit& gui_impl_set::unit_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::virtual_key& gui_impl_set::virtual_key_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::widget& gui_impl_set::widget_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }
}

/*! \file
    \brief The definition of tetengo2::detail::unixos::gui_impl_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <stdexcept>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/unixos/gui_impl_set.h>

namespace tetengo2::detail::base {
    class alert;
    class cursor;
    class drawing;
    class gui_fixture;
    class icon;
    class menu;
    class shell;
    class system_color;
    class unit;
    class virtual_key;
    class widget;
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

/*! \file
    \brief The definition of tetengo2::detail::windows::gui_impl_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <stdexcept>

#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/alert.h>
#include <tetengo2/detail/base/cursor.h>
#include <tetengo2/detail/base/gui_fixture.h>
#include <tetengo2/detail/base/icon.h>
#include <tetengo2/detail/base/shell.h>
#include <tetengo2/detail/base/system_color.h>
#include <tetengo2/detail/base/unit.h>
#include <tetengo2/detail/base/virtual_key.h>
#include <tetengo2/detail/windows/alert.h>
#include <tetengo2/detail/windows/cursor.h>
#include <tetengo2/detail/windows/gui_fixture.h>
#include <tetengo2/detail/windows/gui_impl_set.h>
#include <tetengo2/detail/windows/icon.h>
#include <tetengo2/detail/windows/shell.h>
#include <tetengo2/detail/windows/system_color.h>
#include <tetengo2/detail/windows/unit.h>
#include <tetengo2/detail/windows/virtual_key.h>


namespace tetengo2::detail::windows {
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

    const base::cursor& gui_impl_set::cursor_impl() const
    {
        return cursor::instance();
    }

    std::unique_ptr<base::gui_fixture> gui_impl_set::create_gui_fixture_impl() const
    {
        return std::make_unique<gui_fixture>();
    }

    const base::icon& gui_impl_set::icon_impl() const
    {
        return icon::instance();
    }

    const base::shell& gui_impl_set::shell_impl() const
    {
        return shell::instance();
    }

    const base::system_color& gui_impl_set::system_color_impl() const
    {
        return system_color::instance();
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
        BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        //return widget::instance();
    }
}

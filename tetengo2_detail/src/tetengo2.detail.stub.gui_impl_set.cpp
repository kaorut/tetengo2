/*! \file
    \brief The definition of tetengo2::detail::stub::gui_impl_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <stdexcept>

#include <tetengo2/detail/base/alert.h>
#include <tetengo2/detail/base/cursor.h>
#include <tetengo2/detail/base/gui_fixture.h>
#include <tetengo2/detail/base/icon.h>
#include <tetengo2/detail/base/shell.h>
#include <tetengo2/detail/base/unit.h>
#include <tetengo2/detail/stub/alert.h>
#include <tetengo2/detail/stub/cursor.h>
#include <tetengo2/detail/stub/gui_fixture.h>
#include <tetengo2/detail/stub/gui_impl_set.h>
#include <tetengo2/detail/stub/icon.h>
#include <tetengo2/detail/stub/shell.h>
#include <tetengo2/detail/stub/unit.h>


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

    const base::unit& gui_impl_set::unit_impl() const
    {
        return unit::instance();
    }
}

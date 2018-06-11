/*! \file
    \brief The definition of tetengo2::detail::windows::impl_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <tetengo2/detail/base/alert.h>
#include <tetengo2/detail/base/cursor.h>
#include <tetengo2/detail/base/encoding.h>
#include <tetengo2/detail/base/gui_fixture.h>
#include <tetengo2/detail/base/unit.h>
#include <tetengo2/detail/windows/alert.h>
#include <tetengo2/detail/windows/cursor.h>
#include <tetengo2/detail/windows/encoding.h>
#include <tetengo2/detail/windows/gui_fixture.h>
#include <tetengo2/detail/windows/icon.h>
#include <tetengo2/detail/windows/impl_set.h>
#include <tetengo2/detail/windows/shell.h>
#include <tetengo2/detail/windows/unit.h>


namespace tetengo2::detail::windows {
    const impl_set& impl_set::instance()
    {
        static const impl_set singleton;
        return singleton;
    }

    impl_set::~impl_set() = default;

    impl_set::impl_set() = default;

    const base::alert& impl_set::alert_impl() const
    {
        return alert::instance();
    }

    const base::cursor& impl_set::cursor_impl() const
    {
        return cursor::instance();
    }

    const base::encoding& impl_set::encoding_impl() const
    {
        return encoding::instance();
    }

    std::unique_ptr<base::gui_fixture> impl_set::create_gui_fixture_impl() const
    {
        return std::make_unique<gui_fixture>();
    }

    const base::icon& impl_set::icon_impl() const
    {
        return icon::instance();
    }

    const base::shell& impl_set::shell_impl() const
    {
        return shell::instance();
    }

    const base::unit& impl_set::unit_impl() const
    {
        return unit::instance();
    }
}

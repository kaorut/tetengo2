/*! \file
    \brief The definition of tetengo2::detail::windows::impl_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <tetengo2/detail/base/alert.h>
#include <tetengo2/detail/base/cursor.h>
#include <tetengo2/detail/base/gui_fixture.h>
#include <tetengo2/detail/base/unit.h>
#include <tetengo2/detail/windows/alert.h>
#include <tetengo2/detail/windows/cursor.h>
#include <tetengo2/detail/windows/gui_fixture.h>
#include <tetengo2/detail/windows/impl_set.h>
#include <tetengo2/detail/windows/unit.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace detail { namespace windows {
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

    std::unique_ptr<base::gui_fixture> impl_set::create_gui_fixture_impl() const
    {
        return tetengo2::stdalt::make_unique<gui_fixture>();
    }

    const base::unit& impl_set::unit_impl() const
    {
        return unit::instance();
    }


}}}

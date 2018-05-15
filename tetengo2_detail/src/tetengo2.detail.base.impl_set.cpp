/*! \file
    \brief The definition of tetengo2::detail::base::impl_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <tetengo2/detail/base/gui_fixture.h>
#include <tetengo2/detail/base/impl_set.h>


namespace tetengo2::detail::base {
    class alert;
    class cursor;
    class messages;
    class unit;
}


namespace tetengo2::detail::base {
    impl_set::~impl_set() = default;

    const alert& impl_set::alert_() const
    {
        return alert_impl();
    }

    const cursor& impl_set::cursor_() const
    {
        return cursor_impl();
    }

    std::unique_ptr<gui_fixture> impl_set::create_gui_fixture() const
    {
        return create_gui_fixture_impl();
    }

    const unit& impl_set::unit_() const
    {
        return unit_impl();
    }

    impl_set::impl_set() = default;
}

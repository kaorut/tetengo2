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
    class icon;
    class shell;
    class unit;
    class virtual_key;
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

    const icon& impl_set::icon_() const
    {
        return icon_impl();
    }

    const shell& impl_set::shell_() const
    {
        return shell_impl();
    }

    const unit& impl_set::unit_() const
    {
        return unit_impl();
    }

    const virtual_key& impl_set::virtual_key_() const
    {
        return virtual_key_impl();
    }

    impl_set::impl_set() = default;
}

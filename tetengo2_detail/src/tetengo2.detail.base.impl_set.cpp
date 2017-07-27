/*! \file
    \brief The definition of tetengo2::detail::base::impl_set.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>

#include <tetengo2/detail/base/gui_fixture.h>
#include <tetengo2/detail/base/impl_set.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace detail { namespace base
{
    impl_set::~impl_set()
    = default;

    const alert& impl_set::alert_()
    const
    {
        return alert_impl();
    }

    const cursor& impl_set::cursor_()
    const
    {
        return cursor_impl();
    }

    std::unique_ptr<gui_fixture> impl_set::create_gui_fixture()
    const
    {
        return create_gui_fixture_impl();
    }        

    impl_set::impl_set()
    = default;


}}}

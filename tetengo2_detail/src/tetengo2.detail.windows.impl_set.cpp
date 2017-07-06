/*! \file
    \brief The definition of tetengo2::detail::windows::impl_set.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <tetengo2/detail/windows/alert.h>
#include <tetengo2/detail/windows/cursor.h>
#include <tetengo2/detail/windows/impl_set.h>


namespace tetengo2 { namespace detail { namespace windows
{
    const impl_set& impl_set::instance()
    {
        static const impl_set singleton;
        return singleton;
    }

    impl_set::~impl_set()
    = default;

    impl_set::impl_set()
    = default;

    const base::alert& impl_set::alert_impl()
    const
    {
        return alert::instance();
    }

    const base::cursor& impl_set::cursor_impl()
    const
    {
        return cursor::instance();
    }


}}}

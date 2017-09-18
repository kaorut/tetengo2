/*! \file
    \brief The definition of tetengo2::detail::unixos::impl_set.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <stdexcept>

#include <tetengo2/detail/unixos/impl_set.h>


namespace tetengo2 { namespace detail { namespace unixos
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
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::cursor& impl_set::cursor_impl()
    const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    std::unique_ptr<base::gui_fixture> impl_set::create_gui_fixture_impl()
    const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::unit& impl_set::unit_impl()
    const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }


}}}

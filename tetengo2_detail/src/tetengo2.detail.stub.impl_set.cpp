/*! \file
    \brief The definition of tetengo2::detail::stub::impl_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <stdexcept>

#include <tetengo2/detail/base/impl_set.h>
#include <tetengo2/detail/stub/impl_set.h>

namespace tetengo2::detail::base {
    class config;
    class encoding;
}


namespace tetengo2::detail::stub {
    const impl_set& impl_set::instance()
    {
        static const impl_set singleton;
        return singleton;
    }

    impl_set::~impl_set() = default;

    impl_set::impl_set() = default;

    const base::config& impl_set::config_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }

    const base::encoding& impl_set::encoding_impl() const
    {
        assert(false);
        throw std::logic_error("No implementation.");
    }
}

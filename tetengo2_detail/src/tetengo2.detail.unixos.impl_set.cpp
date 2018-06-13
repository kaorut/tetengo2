/*! \file
    \brief The definition of tetengo2::detail::unixos::impl_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <tetengo2/detail/base/config.h>
#include <tetengo2/detail/base/encoding.h>
#include <tetengo2/detail/unixos/config.h>
#include <tetengo2/detail/unixos/encoding.h>
#include <tetengo2/detail/unixos/impl_set.h>


namespace tetengo2::detail::unixos {
    const impl_set& impl_set::instance()
    {
        static const impl_set singleton;
        return singleton;
    }

    impl_set::~impl_set() = default;

    impl_set::impl_set() = default;

    const base::config& impl_set::config_impl() const
    {
        return config::instance();
    }

    const base::encoding& impl_set::encoding_impl() const
    {
        return encoding::instance();
    }
}

/*! \file
    \brief The definition of tetengo2::detail::windows::impl_set.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <tetengo2/detail/base/config.h>
#include <tetengo2/detail/base/encoding.h>
#include <tetengo2/detail/base/messages.h>
#include <tetengo2/detail/windows/config.h>
#include <tetengo2/detail/windows/encoding.h>
#include <tetengo2/detail/windows/impl_set.h>
#include <tetengo2/detail/windows/messages.h>


namespace tetengo2::detail::windows {
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

    const base::messages& impl_set::messages_impl() const
    {
        return messages::instance();
    }
}

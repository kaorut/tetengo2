/*! \file
    \brief The definition of tetengo2::detail::base::impl_set.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <stdexcept>

#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/impl_set.h>


namespace tetengo2::detail::base {
    class config;
    class encoding;
    class messages;
}


namespace tetengo2::detail {
    namespace base {
        impl_set::~impl_set() = default;

        const config& impl_set::config_() const
        {
            return config_impl();
        }

        const encoding& impl_set::encoding_() const
        {
            return encoding_impl();
        }

        const messages& impl_set::messages_() const
        {
            return messages_impl();
        }

        impl_set::impl_set() = default;
    }


    namespace {
        const base::impl_set* g_p_impl_set = nullptr;
    }

    const base::impl_set& detail_impl_set()
    {
        if (!g_p_impl_set)
            BOOST_THROW_EXCEPTION(std::logic_error{ "No detail implementation set is set yet." });

        return *g_p_impl_set;
    }

    void set_detail_impl_set(const base::impl_set& impl_set_)
    {
        g_p_impl_set = &impl_set_;
    }
}
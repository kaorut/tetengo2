/*! \file
    \brief The definition of tetengo2::detail::base::config.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <utility>

#include <boost/optional.hpp>

#include <tetengo2/detail/base/config.h>


namespace tetengo2 { namespace detail { namespace base {
    config::~config() = default;

    config::config() = default;

    boost::optional<config::value_type> config::get(const string_type& group_name, const string_type& key) const
    {
        return get_impl(group_name, key);
    }

    void config::set(const string_type& group_name, const string_type& key, value_type value) const
    {
        set_impl(group_name, key, std::move(value));
    }

    void config::clear(const string_type& group_name) const
    {
        clear_impl(group_name);
    }


}}}

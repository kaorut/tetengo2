/*! \file
    \brief The definition of tetengo2::config::persistent_config.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/config/persistent_config.h>
#include <tetengo2/detail/base/config.h>
#include <tetengo2/detail/base/impl_set.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::config {
    class persistent_config::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = persistent_config::string_type;

        using uint_type = persistent_config::uint_type;

        using base_type = persistent_config::base_type;

        using value_type = persistent_config::value_type;


        // constructors and destructor

        explicit impl(string_type group_name) : m_group_name{ std::move(group_name) } {}


        // functions

        tetengo2::stdalt::optional<value_type> get_impl(const string_type& key) const
        {
            return detail::detail_impl_set().config_().get(m_group_name, key);
        }

        void set_impl(const string_type& key, value_type value)
        {
            return detail::detail_impl_set().config_().set(m_group_name, key, std::move(value));
        }

        void clear_impl()
        {
            return detail::detail_impl_set().config_().clear(m_group_name);
        }


    private:
        // variables

        const string_type m_group_name;
    };


    persistent_config::persistent_config(string_type group_name)
    : m_p_impl{ std::make_unique<impl>(std::move(group_name)) }
    {}

    persistent_config::~persistent_config() = default;

    tetengo2::stdalt::optional<persistent_config::value_type> persistent_config::get_impl(const string_type& key) const
    {
        return m_p_impl->get_impl(key);
    }

    void persistent_config::set_impl(const string_type& key, value_type value)
    {
        return m_p_impl->set_impl(key, std::move(value));
    }

    void persistent_config::clear_impl()
    {
        return m_p_impl->clear_impl();
    }
}

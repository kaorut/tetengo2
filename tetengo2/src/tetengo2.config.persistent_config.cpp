/*! \file
    \brief The definition of tetengo2::config::persistent_config.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>

#include <tetengo2/config/config_base.h>
#include <tetengo2/detail/base/config.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>

#include <tetengo2/config/persistent_config.h>


namespace tetengo2 { namespace config
{
    class persistent_config::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = persistent_config::string_type;

        using uint_type = persistent_config::uint_type;

        using base_type = persistent_config::base_type;

        using value_type = persistent_config::value_type;

        using config_details_type = persistent_config::config_details_type;


        // constructors and destructor

        impl(string_type group_name, const config_details_type& config_details)
        :
        m_group_name(std::move(group_name)),
        m_config_details(config_details)
        {}


        // functions

        boost::optional<value_type> get_impl(const string_type& key)
        const
        {
            return m_config_details.get(m_group_name, key);
        }

        void set_impl(const string_type& key, value_type value)
        {
            return m_config_details.set(m_group_name, key, std::move(value));
        }

        void clear_impl()
        {
            return m_config_details.clear(m_group_name);
        }


    private:
        // variables

        const string_type m_group_name;

        const config_details_type& m_config_details;


    };


    persistent_config::persistent_config(string_type group_name, const config_details_type& config_details)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(group_name), config_details))
    {}

    persistent_config::~persistent_config()
    = default;

    boost::optional<persistent_config::value_type> persistent_config::get_impl(const string_type& key)
    const
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


}}

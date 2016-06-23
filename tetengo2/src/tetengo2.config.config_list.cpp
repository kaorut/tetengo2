/*! \file
    \brief The definition of tetengo2::config::config_list.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>

#include <tetengo2/config/config_list.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace config
{
    class config_list::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = type_list::string_type;

        using uint_type = type_list::size_type;

        using base_type = config_base;

        using value_type = typename base_type::value_type;


        // constructors and destructor

        explicit impl(std::vector<std::unique_ptr<base_type>> p_configs)
        :
        m_p_configs(std::move(p_configs))
        {}


        // functions

        boost::optional<value_type> get_impl(const string_type& key)
        const
        {
            for (const std::unique_ptr<base_type>& p_config: m_p_configs)
            {
                const auto value = p_config->get(key);
                if (value)
                    return value;
            }

            return boost::none;
        }

        void set_impl(const string_type& key, value_type value)
        {
            std::for_each(
                m_p_configs.begin(),
                m_p_configs.end(),
                [&key, &value](std::unique_ptr<base_type>& p_config) { p_config->set(key, std::move(value)); }
            );
        }

        void clear_impl()
        {
            std::for_each(
                m_p_configs.begin(),
                m_p_configs.end(),
                [](std::unique_ptr<base_type>& p_config) { p_config->clear(); }
            );
        }


    private:
        // variables

        std::vector<std::unique_ptr<base_type>> m_p_configs;


    };


    config_list::config_list(std::vector<std::unique_ptr<base_type>> p_configs)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(p_configs)))
    {}

    config_list::~config_list()
    = default;


    boost::optional<config_list::value_type> config_list::get_impl(const string_type& key)
    const
    {
        return m_p_impl->get_impl(key);
    }

    void config_list::set_impl(const string_type& key, value_type value)
    {
        m_p_impl->set_impl(key, std::move(value));
    }

    void config_list::clear_impl()
    {
        m_p_impl->clear_impl();
    }


}}

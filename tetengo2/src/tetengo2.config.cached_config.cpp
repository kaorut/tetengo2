/*! \file
    \brief The definition of tetengo2::config::cached_config.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/config/cached_config.h>
#include <tetengo2/config/config_base.h>
#include <tetengo2/config/temporary_config.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::config {
    class cached_config::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = cached_config::string_type;

        using uint_type = cached_config::uint_type;

        using base_type = cached_config::base_type;

        using value_type = cached_config::value_type;


        // constructors and destructor

        explicit impl(std::unique_ptr<base_type> p_config) : m_p_config{ std::move(p_config) }, m_cache{} {}


        // functions

        tetengo2::stdalt::optional<value_type> get_impl(const string_type& key) const
        {
            auto cached_value = m_cache.get(key);
            if (cached_value)
                return cached_value;

            auto value = m_p_config->get(key);
            if (value)
                m_cache.set(key, *value);

            return value;
        }

        void set_impl(const string_type& key, value_type value)
        {
            m_cache.set(key, value);
            m_p_config->set(key, std::move(value));
        }

        void clear_impl()
        {
            m_cache.clear();
            m_p_config->clear();
        }


    private:
        // types

        using cache_type = temporary_config;


        // variables

        const std::unique_ptr<base_type> m_p_config;

        mutable cache_type m_cache;
    };


    cached_config::cached_config(std::unique_ptr<base_type> p_config)
    : m_p_impl{ std::make_unique<impl>(std::move(p_config)) }
    {}

    cached_config::~cached_config() = default;

    tetengo2::stdalt::optional<cached_config::value_type> cached_config::get_impl(const string_type& key) const
    {
        return m_p_impl->get_impl(key);
    }

    void cached_config::set_impl(const string_type& key, value_type value)
    {
        m_p_impl->set_impl(key, std::move(value));
    }

    void cached_config::clear_impl()
    {
        m_p_impl->clear_impl();
    }
}

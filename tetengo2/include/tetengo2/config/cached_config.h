/*! \file
    \brief The definition of tetengo2::config::cached_config.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONFIG_CACHEDCONFIG_H)
#define TETENGO2_CONFIG_CACHEDCONFIG_H

#include <memory>
#include <utility>

#include <boost/optional.hpp>

#include <tetengo2/config/config_base.h>
#include <tetengo2/config/temporary_config.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace config
{
    /*!
        \brief The class template for a cached configuration.

        \tparam String A string type.
        \tparam UInt   An unsigned integer type.
    */
    template <typename String, typename UInt>
    class cached_config : public config_base
    {
    public:
        // types

        //! The string type.
        using string_type = type_list::string_type;

        //! The unsigned integer type.
        using uint_type = type_list::size_type;

        //! The base type.
        using base_type = config_base;

        //! The value type.
        using value_type = typename base_type::value_type;


        // constructors and destructor

        /*!
            \brief Creates a cached configuration.

            \param p_config A unique pointer to a configuration.
        */
        explicit cached_config(std::unique_ptr<base_type> p_config)
        :
        m_p_config(std::move(p_config)),
        m_cache()
        {}

        /*!
            \brief Destroys the cached configuration.
        */
        virtual ~cached_config()
        = default;


    private:
        // types

        using cache_type = temporary_config<string_type, uint_type>;


        // variables

        const std::unique_ptr<base_type> m_p_config;

        mutable cache_type m_cache;


        // virtual functions

        virtual boost::optional<value_type> get_impl(const string_type& key)
        const override
        {
            auto cached_value = m_cache.get(key);
            if (cached_value)
                return cached_value;

            auto value = m_p_config->get(key);
            if (value)
                m_cache.set(key, *value);

            return value;
        }

        virtual void set_impl(const string_type& key, value_type value)
        override
        {
            m_cache.set(key, value);
            m_p_config->set(key, std::move(value));
        }

        virtual void clear_impl()
        override
        {
            m_cache.clear();
            m_p_config->clear();
        }


    };


}}


#endif

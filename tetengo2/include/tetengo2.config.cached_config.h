/*! \file
    \brief The definition of tetengo2::config::cached_config.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONFIG_CACHEDCONFIG_H)
#define TETENGO2_CONFIG_CACHEDCONFIG_H

//#include <memory>
//#include <utility>

//#include <boost/optional.hpp>

#include "tetengo2.config.config_base.h"
#include "tetengo2.config.temporary_config.h"
#include "tetengo2.stdalt.h"


namespace tetengo2 { namespace config
{
    /*!
        \brief The class template for a cached configuration.

        \tparam String A string type.
        \tparam UInt   An unsigned integer type.
    */
    template <typename String, typename UInt>
    class cached_config : public config_base<String, UInt>
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The unsigned integer type.
        typedef UInt uint_type;

        //! The base type.
        typedef config_base<string_type, uint_type> base_type;

        //! The value type.
        typedef typename base_type::value_type value_type;


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
        TETENGO2_STDALT_NOEXCEPT
        {}


    private:
        // types

        typedef temporary_config<string_type, uint_type> cache_type;


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


    };


}}


#endif
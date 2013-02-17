/*! \file
    \brief The definition of tetengo2::config::config_list.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONFIG_CONFIGLIST_H)
#define TETENGO2_CONFIG_CONFIGLIST_H

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include "tetengo2.config.config_base.h"
#include "tetengo2.cpp11.h"


namespace tetengo2 { namespace config
{
    /*!
        \brief The class template for a configuration list.

        \tparam String A string type.
        \tparam UInt   An unsigned integer type.
    */
    template <typename String, typename UInt>
    class config_list : public config_base<String, UInt>
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
            \brief Creates a configuration list.

            \param p_configs A vector of unique pointers to configurations.
        */
        config_list(std::vector<std::unique_ptr<base_type>> p_configs)
        :
        m_p_configs(std::move(p_configs))
        {}

        /*!
            \brief Destroys the configuration list.
        */
        virtual ~config_list()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // variables

        std::vector<std::unique_ptr<base_type>> m_p_configs;


        // virtual functions

        virtual boost::optional<value_type> get_impl(const string_type& key)
        const
        {
            BOOST_FOREACH (const std::unique_ptr<base_type>& p_config, m_p_configs)
            {
                const boost::optional<value_type> value = p_config->get(key);
                if (value)
                    return value;
            }

            return boost::none;
        }

        virtual void set_impl(const string_type& key, value_type value)
        {
            std::for_each(
                m_p_configs.begin(),
                m_p_configs.end(),
                TETENGO2_CPP11_BIND(&base_type::set, tetengo2::cpp11::placeholders_1(), key, value)
            );
        }


    };


}}


#endif

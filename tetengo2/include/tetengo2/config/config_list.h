/*! \file
    \brief The definition of tetengo2::config::config_list.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONFIG_CONFIGLIST_H)
#define TETENGO2_CONFIG_CONFIGLIST_H

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include <boost/optional.hpp>

#include <tetengo2/config/config_base.h>
#include <tetengo2/stdalt.h>


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
        using string_type = String;

        //! The unsigned integer type.
        using uint_type = UInt;

        //! The base type.
        using base_type = config_base<string_type, uint_type>;

        //! The value type.
        using value_type = typename base_type::value_type;


        // constructors and destructor

        /*!
            \brief Creates a configuration list.

            \param p_configs A vector of unique pointers to configurations.
        */
        explicit config_list(std::vector<std::unique_ptr<base_type>> p_configs)
        :
        m_p_configs(std::move(p_configs))
        {}

        /*!
            \brief Destroys the configuration list.
        */
        virtual ~config_list()
        = default;


    private:
        // variables

        std::vector<std::unique_ptr<base_type>> m_p_configs;


        // virtual functions

        virtual boost::optional<value_type> get_impl(const string_type& key)
        const override
        {
            for (const std::unique_ptr<base_type>& p_config: m_p_configs)
            {
                const auto value = p_config->get(key);
                if (value)
                    return value;
            }

            return boost::none;
        }

        virtual void set_impl(const string_type& key, value_type value)
        override
        {
            std::for_each(
                m_p_configs.begin(),
                m_p_configs.end(),
                [&key, &value](std::unique_ptr<base_type>& p_config) { p_config->set(key, std::move(value)); }
            );
        }

        virtual void clear_impl()
        override
        {
            std::for_each(
                m_p_configs.begin(),
                m_p_configs.end(),
                [](std::unique_ptr<base_type>& p_config) { p_config->clear(); }
            );
        }


    };


}}


#endif

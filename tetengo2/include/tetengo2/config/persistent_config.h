/*! \file
    \brief The definition of tetengo2::config::persistent_config.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONFIG_PERSISTENTCONFIG_H)
#define TETENGO2_CONFIG_PERSISTENTCONFIG_H

#include <utility>

#include <boost/optional.hpp>

#include <tetengo2/config/config_base.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace config
{
    /*!
        \brief The class template for a persistent configuration.

        \tparam String        A string type.
        \tparam UInt          An unsigned integer type.
        \tparam Encoder       An encoder type.
        \tparam ConfigDetails A detail implementation type of a configuration.
    */
    template <typename String, typename UInt, typename Encoder, typename ConfigDetails>
    class persistent_config : public config_base
    {
    public:
        // types

        //! The string type.
        using string_type = type_list::string_type;

        //! The unsigned integer type.
        using uint_type = type_list::size_type;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The configuration details type.
        using configuration_details_type = ConfigDetails;

        //! The base type.
        using base_type = config_base;

        //! The value type.
        using value_type = typename base_type::value_type;


        // constructors and destructor

        /*!
            \brief Creates a persistent configuration.

            \param group_name A group name.
        */
        explicit persistent_config(string_type group_name)
        :
        m_group_name(std::move(group_name))
        {}

        /*!
            \brief Destroys the persistent configuration.
        */
        virtual ~persistent_config()
        = default;


    private:
        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton{};
            return singleton;
        }


        // variables

        const string_type m_group_name;


        // virtual functions

        virtual boost::optional<value_type> get_impl(const string_type& key)
        const override
        {
            return configuration_details_type::template get<string_type, uint_type>(m_group_name, key, encoder());
        }

        virtual void set_impl(const string_type& key, value_type value)
        override
        {
            configuration_details_type::set(m_group_name, key, std::move(value), encoder());
        }

        virtual void clear_impl()
        override
        {
            configuration_details_type::clear(m_group_name, encoder());
        }


    };


}}


#endif

/*! \file
    \brief The definition of tetengo2::detail::unixos::config.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_UNIXOS_CONFIG_H)
#define TETENGO2_DETAIL_UNIXOS_CONFIG_H

#include <string>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <tetengo2/utility.h>


namespace tetengo2 { namespace detail { namespace unixos
{
    /*!
        \brief The class for a detail implementation of a configuration.
    */
    class config : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = std::string;


        // static functions

        /*!
            \brief Returns the configuration value.

            \tparam String  A string type.
            \tparam UInt    An unsigned integer type.
            \tparam Encoder An encoder type.

            \param group_name A group name.
            \param key        A key.
            \param encoder    An encoder.

            \return The value.
        */
        template <typename String, typename UInt, typename Encoder>
        static boost::optional<boost::variant<String, UInt>> get(
            const String&  group_name,
            const String&  key,
            const Encoder& encoder
        )
        {
            suppress_unused_variable_warning(group_name, key, encoder);

            return boost::none;
        }

        /*!
            \brief Sets a configuration value.

            \tparam String  A string type.
            \tparam UInt    An unsigned integer type.
            \tparam Encoder An encoder type.

            \param group_name A group_name.
            \param key        A key.
            \param value      A value.
            \param encoder    An encoder.
        */
        template <typename String, typename UInt, typename Encoder>
        static void set(
            const String&                group_name,
            const String&                key,
            boost::variant<String, UInt> value,
            const Encoder&               encoder
        )
        {
            suppress_unused_variable_warning(group_name, key, value, encoder);
        }

        /*!
            \brief Clears the configuration.

            \tparam String  A string type.
            \tparam Encoder An encoder type.

            \param group_name A group_name.
            \param encoder    An encoder.
        */
        template <typename String, typename Encoder>
        static void clear(const String& group_name, const Encoder& encoder)
        {
            suppress_unused_variable_warning(group_name, encoder);
        }


    };


}}}


#endif

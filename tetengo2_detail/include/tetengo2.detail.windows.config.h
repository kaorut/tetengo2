/*! \file
    \brief The definition of tetengo2::detail::windows::config.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_CONFIG_H)
#define TETENGO2_DETAIL_WINDOWS_CONFIG_H

#include <boost/noncopyable.hpp>

//#pragma warning (push)
//#pragma warning (disable: 4005)
//#include <intsafe.h>
//#include <stdint.h>
//#pragma warning(pop)
//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of a config.
    */
    class config : private boost::noncopyable
    {
    public:
        // static functions

        /*!
            \brief Returns the configuration value.

            \tparam String A string type.
            \tparam UInt   An unsigned integer type.

            \param group_name A group name.
            \param key        A key.

            \return The value.
        */
        template <typename String, typename UInt>
        static boost::optional<boost::variant<String, UInt>> get(const String& group_name, const String& key)
        {
            return boost::none;
        }

        /*!
            \brief Sets a configuration value.

            \tparam String A string type.
            \tparam UInt   An unsigned integer type.

            \param group_name A group_name.
            \param key        A key.
            \param value      A value.
        */
        template <typename String, typename UInt>
        static void set(const String& group_name, const String& key, boost::variant<String, UInt> value)
        {}


    };


}}}


#endif

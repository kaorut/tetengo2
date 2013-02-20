/*! \file
    \brief The definition of tetengo2::detail::windows::config.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_CONFIG_H)
#define TETENGO2_DETAIL_WINDOWS_CONFIG_H

#include <boost/algorithm/string.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/scope_exit.hpp>
#include <boost/utility.hpp>
#include <boost/variant.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.text.h"


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
            const std::pair<String, String> registry_key_and_value_name =
                build_registry_key_and_value_name(group_name, key);

            ::HKEY handle = NULL;
            const ::LONG create_key_error_code =
                ::RegCreateKeyExW(
                    HKEY_CURRENT_USER,
                    registry_key_and_value_name.first.c_str(),
                    0,
                    NULL,
                    REG_OPTION_NON_VOLATILE,
                    KEY_READ,
                    NULL,
                    &handle,
                    NULL
                );
            if (create_key_error_code != ERROR_SUCCESS)
                return boost::none;
            BOOST_SCOPE_EXIT((handle))
            {
                ::RegCloseKey(handle);
            } BOOST_SCOPE_EXIT_END;

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


    private:
        // static functions

        template <typename String>
        static std::pair<String, String> build_registry_key_and_value_name(const String& group_name, const String& key)
        {
            std::vector<String> key_names;
            boost::split(key_names, key, is_splitter<typename String::value_type>);
            if (key_names.size() <= 1)
                return std::make_pair(group_name, key);
            
            return
                std::make_pair(
                    String(TETENGO2_TEXT("Software\\tetengo\\")) +
                    group_name +
                        String(TETENGO2_TEXT("\\")) +
                        boost::join(
                            std::make_pair(key_names.begin(), boost::prior(key_names.end())),
                            String(TETENGO2_TEXT("\\"))
                        ),
                    key_names[key_names.size() - 1]
                );
        }

        template <typename Char>
        static bool is_splitter(const Char character)
        {
            return character == Char(TETENGO2_TEXT('/'));
        }


    };


}}}


#endif

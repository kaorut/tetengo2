/*! \file
    \brief The definition of tetengo2::detail::windows::config.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_CONFIG_H)
#define TETENGO2_DETAIL_WINDOWS_CONFIG_H

#include <cassert>
#include <string>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
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

#include <tetengo2/text.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of a config.
    */
    class config : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = std::wstring;


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
            const auto registry_key_and_value_name = build_registry_key_and_value_name(group_name, key);

            const registry<String, Encoder> handle{ registry_key_and_value_name.first, encoder, KEY_READ };
            if (!handle.get())
                return boost::none;

            const auto type = query_value_type(handle.get(), registry_key_and_value_name.second, encoder);

            switch (type.first)
            {
            case value_type::string:
                return
                    boost::make_optional(
                        boost::variant<String, UInt>(
                            get_string(handle.get(), registry_key_and_value_name.second, type.second, encoder)
                        )
                    );
            case value_type::dword:
                return
                    boost::make_optional(
                        boost::variant<String, UInt>(
                            get_dword(handle.get(), registry_key_and_value_name.second, encoder)
                        )
                    );
            default:
                assert(type.first == value_type::unknown);
                return boost::none;
            }
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
            const auto registry_key_and_value_name = build_registry_key_and_value_name(group_name, key);

            const registry<String, Encoder> handle{ registry_key_and_value_name.first, encoder, KEY_WRITE };
            if (!handle.get())
                return;

            switch (value.which())
            {
            case 0:
                set_string(handle.get(), registry_key_and_value_name.second, boost::get<String>(value), encoder);
                break;
            case 1:
                set_dword(
                    handle.get(),
                    registry_key_and_value_name.second,
                    static_cast< ::DWORD>(boost::get<UInt>(value)),
                    encoder
                );
                break;
            default:
                assert(false);
                break;
            }
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
            const registry<String, Encoder> handle{ path_prefix<String>(), encoder, KEY_WRITE };
            if (!handle.get())
                return;

            ::RegDeleteTreeW(handle.get(), encoder.encode(group_name).c_str());
        }


    private:
        // types

        template <typename String, typename Encoder>
        class registry : private boost::noncopyable
        {
        public:
            registry(const String& key, const Encoder& encoder, const ::REGSAM mode)
            :
            m_handle(create(key, encoder, mode))
            {}

            ~registry()
            noexcept
            {
                ::RegCloseKey(m_handle);
            }

            const ::HKEY get()
            const
            {
                return m_handle;
            }

        private:
            static ::HKEY create(const String&  key, const Encoder& encoder, const ::REGSAM mode)
            {
                ::HKEY handle = nullptr;
                const auto create_key_result =
                    ::RegCreateKeyExW(
                        HKEY_CURRENT_USER,
                        encoder.encode(key).c_str(),
                        0,
                        nullptr,
                        REG_OPTION_NON_VOLATILE,
                        mode,
                        nullptr,
                        &handle,
                        nullptr
                    );
                if (create_key_result != ERROR_SUCCESS)
                    return nullptr;

                return handle;
            }

            const ::HKEY m_handle;

        };

        enum class value_type
        {
            unknown,
            string,
            dword,
        };


        // static functions

        template <typename String>
        static const String& path_prefix()
        {
            static const String singleton{ TETENGO2_TEXT("Software\\tetengo\\") };
            return singleton;
        }

        template <typename String>
        static std::pair<String, String> build_registry_key_and_value_name(const String& group_name, const String& key)
        {
            std::vector<String> key_names{};
            boost::split(
                key_names,
                key,
                [](const typename String::value_type c) {
                    return c == typename String::value_type{ TETENGO2_TEXT('/') };
                }
            );
            if (key_names.size() <= 1)
                return std::make_pair(path_prefix<String>() + group_name, key);
            
            return
                std::make_pair(
                     path_prefix<String>() +
                        group_name +
                        String{ TETENGO2_TEXT("\\") } +
                        boost::join(
                            std::make_pair(key_names.begin(), boost::prior(key_names.end())),
                            String{ TETENGO2_TEXT("\\") }
                        ),
                    key_names[key_names.size() - 1]
                );
        }

        template <typename String, typename Encoder>
        static std::pair<value_type, typename String::size_type> query_value_type(
            const ::HKEY   handle,
            const String&  key,
            const Encoder& encoder
        )
        {
            ::DWORD type = 0;
            ::DWORD value_size = 0;
            const auto query_value_result =
                ::RegQueryValueExW(handle, encoder.encode(key).c_str(), 0, &type, nullptr, &value_size);
            if (query_value_result != ERROR_SUCCESS)
                return std::make_pair(value_type::unknown, 0);

            switch (type)
            {
            case REG_SZ:
                return std::make_pair(value_type::string, value_size / sizeof(string_type::value_type));
            case REG_DWORD:
                return std::make_pair(value_type::dword, 0);
            default:
                return std::make_pair(value_type::unknown, 0);
            }
        }

        template <typename String, typename Encoder>
        static String get_string(
            const ::HKEY                     handle,
            const String&                    key,
            const typename String::size_type result_length,
            const Encoder&                   encoder
        )
        {
            std::vector<typename string_type::value_type> value(result_length, 0);
            auto value_size =
                static_cast< ::DWORD>(result_length * sizeof(typename string_type::value_type));
            const auto query_value_result =
                ::RegQueryValueExW(
                    handle,
                    encoder.encode(key).c_str(),
                    0,
                    nullptr,
                    reinterpret_cast< ::LPBYTE>(value.data()),
                    &value_size
                );
            boost::ignore_unused(query_value_result);
            assert(query_value_result == ERROR_SUCCESS);

            return encoder.decode(&value[0]);
        }

        template <typename String, typename Encoder>
        static ::DWORD get_dword(const ::HKEY handle, const String& key, const Encoder& encoder)
        {
            ::DWORD value = 0;
            ::DWORD value_size = sizeof(::DWORD);
            const auto query_value_result =
                ::RegQueryValueExW(
                    handle,
                    encoder.encode(key).c_str(),
                    0,
                    nullptr,
                    reinterpret_cast< ::LPBYTE>(&value),
                    &value_size
                );
            boost::ignore_unused(query_value_result);
            assert(query_value_result == ERROR_SUCCESS);

            return value;
        }

        template <typename String, typename Encoder>
        static void set_string(const ::HKEY handle, const String& key, const String& value, const Encoder& encoder)
        {
            const auto encoded_value = encoder.encode(value);
            ::RegSetValueEx(
                handle,
                encoder.encode(key).c_str(),
                0,
                REG_SZ,
                reinterpret_cast<const ::BYTE*>(encoded_value.c_str()),
                static_cast< ::DWORD>(
                    (encoded_value.length() + 1) * sizeof(typename string_type::value_type)
                )
            );
        }

        template <typename String, typename Encoder>
        static void set_dword(const ::HKEY handle, const String& key, const ::DWORD value, const Encoder& encoder)
        {
            ::RegSetValueEx(
                handle,
                encoder.encode(key).c_str(),
                0,
                REG_DWORD,
                reinterpret_cast<const ::BYTE*>(&value),
                sizeof(::DWORD)
            );
        }


    };


}}}


#endif

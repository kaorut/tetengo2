/*! \file
    \brief The definition of detail::windows::config.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <cassert>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/config.h>
#include <tetengo2/detail/windows/encoding.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace detail { namespace windows
{
    class config::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = config::string_type;

        using uint_type = config::uint_type;

        using value_type = config::value_type;


        // constructors and destructor

        impl()
        {}


        // functions

        // virtual functions

        virtual boost::optional<value_type> get_impl(const string_type& group_name, const string_type& key)
        const
        {
            const auto registry_key_and_value_name = build_registry_key_and_value_name(group_name, key);

            const registry_type handle{ registry_key_and_value_name.first, KEY_READ };
            if (!handle.get())
                return boost::none;

            const auto type = query_value_kind(handle.get(), registry_key_and_value_name.second);

            switch (type.first)
            {
            case value_kind_type::string:
                return
                    boost::make_optional(
                        value_type{
                            get_string(handle.get(), registry_key_and_value_name.second, type.second)
                        }
                    );
            case value_kind_type::dword:
                return
                    boost::make_optional(
                        value_type{ get_dword(handle.get(), registry_key_and_value_name.second) }
                    );
            default:
                assert(type.first == value_kind_type::unknown);
                return boost::none;
            }
        }

        virtual void set_impl(const string_type& group_name, const string_type& key, value_type value)
        const
        {
            const auto registry_key_and_value_name = build_registry_key_and_value_name(group_name, key);

            const registry_type handle{ registry_key_and_value_name.first, KEY_WRITE };
            if (!handle.get())
                return;

            switch (value.which())
            {
            case 0:
                set_string(handle.get(), registry_key_and_value_name.second, boost::get<string_type>(value));
                break;
            case 1:
                set_dword(
                    handle.get(),
                    registry_key_and_value_name.second,
                    static_cast< ::DWORD>(boost::get<uint_type>(value))
                );
                break;
            default:
                assert(false);
                break;
            }
        }

        virtual void clear_impl(const string_type& group_name)
        const
        {
            const registry_type handle{ path_prefix(), KEY_WRITE };
            if (!handle.get())
                return;

            ::RegDeleteTreeW(handle.get(), encoder().encode(group_name).c_str());
        }


    private:
        // types

        using native_string_type = std::wstring;

        using encoding_details_type = encoding;

        using encoder_type =
            text::encoder<
                text::encoding::locale<string_type, encoding_details_type>,
                text::encoding::locale<native_string_type, encoding_details_type>
            >;

        class registry_type : private boost::noncopyable
        {
        public:
            registry_type(const string_type& key, const ::REGSAM mode)
            :
            m_handle(create(key, mode))
            {}

            ~registry_type()
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
            static ::HKEY create(const string_type&  key, const ::REGSAM mode)
            {
                ::HKEY handle = nullptr;
                const auto create_key_result =
                    ::RegCreateKeyExW(
                        HKEY_CURRENT_USER,
                        encoder().encode(key).c_str(),
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

        enum class value_kind_type
        {
            unknown,
            string,
            dword,
        };


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton{};
            return singleton;
        }

        static const string_type& path_prefix()
        {
            static const string_type singleton{ TETENGO2_TEXT("Software\\tetengo\\") };
            return singleton;
        }

        static std::pair<string_type, string_type> build_registry_key_and_value_name(
            const string_type& group_name,
            const string_type& key
        )
        {
            std::vector<string_type> key_names{};
            boost::split(
                key_names,
                key,
                [](const string_type::value_type c) {
                    return c == string_type::value_type{ TETENGO2_TEXT('/') };
                }
            );
            if (key_names.size() <= 1)
                return std::make_pair(path_prefix() + group_name, key);
            
            return
                std::make_pair(
                     path_prefix() +
                        group_name +
                        string_type{ TETENGO2_TEXT("\\") } +
                        boost::join(
                            std::make_pair(key_names.begin(), std::prev(key_names.end())),
                            string_type{ TETENGO2_TEXT("\\") }
                        ),
                    key_names[key_names.size() - 1]
                );
        }

        static std::pair<value_kind_type, string_type::size_type> query_value_kind(
            const ::HKEY       handle,
            const string_type& key
        )
        {
            ::DWORD type = 0;
            ::DWORD value_size = 0;
            const auto query_value_result =
                ::RegQueryValueExW(handle, encoder().encode(key).c_str(), 0, &type, nullptr, &value_size);
            if (query_value_result != ERROR_SUCCESS)
                return std::make_pair(value_kind_type::unknown, 0);

            switch (type)
            {
            case REG_SZ:
                return std::make_pair(value_kind_type::string, value_size / sizeof(native_string_type::value_type));
            case REG_DWORD:
                return std::make_pair(value_kind_type::dword, 0);
            default:
                return std::make_pair(value_kind_type::unknown, 0);
            }
        }

        static string_type get_string(
            const ::HKEY                 handle,
            const string_type&           key,
            const string_type::size_type result_length
        )
        {
            std::vector<native_string_type::value_type> value(result_length, 0);
            auto value_size =
                static_cast< ::DWORD>(result_length * sizeof(native_string_type::value_type));
            const auto query_value_result =
                ::RegQueryValueExW(
                    handle,
                    encoder().encode(key).c_str(),
                    0,
                    nullptr,
                    reinterpret_cast< ::LPBYTE>(value.data()),
                    &value_size
                );
            boost::ignore_unused(query_value_result);
            assert(query_value_result == ERROR_SUCCESS);

            return encoder().decode(&value[0]);
        }

        static ::DWORD get_dword(const ::HKEY handle, const string_type& key)
        {
            ::DWORD value = 0;
            ::DWORD value_size = sizeof(::DWORD);
            const auto query_value_result =
                ::RegQueryValueExW(
                    handle,
                    encoder().encode(key).c_str(),
                    0,
                    nullptr,
                    reinterpret_cast< ::LPBYTE>(&value),
                    &value_size
                );
            boost::ignore_unused(query_value_result);
            assert(query_value_result == ERROR_SUCCESS);

            return value;
        }

        static void set_string(const ::HKEY handle, const string_type& key, const string_type& value)
        {
            const auto encoded_value = encoder().encode(value);
            ::RegSetValueEx(
                handle,
                encoder().encode(key).c_str(),
                0,
                REG_SZ,
                reinterpret_cast<const ::BYTE*>(encoded_value.c_str()),
                static_cast< ::DWORD>(
                    (encoded_value.length() + 1) * sizeof(native_string_type::value_type)
                )
            );
        }

        static void set_dword(const ::HKEY handle, const string_type& key, const ::DWORD value)
        {
            ::RegSetValueEx(
                handle,
                encoder().encode(key).c_str(),
                0,
                REG_DWORD,
                reinterpret_cast<const ::BYTE*>(&value),
                sizeof(::DWORD)
            );
        }


    };


    const config& config::instance()
    {
        static const config singleton{};
        return singleton;
    }

    config::~config()
    = default;

    config::config()
    :
    m_p_impl(stdalt::make_unique<impl>())
    {}


    // virtual functions

    boost::optional<config::value_type> config::get_impl(const string_type& group_name, const string_type& key)
    const
    {
        return m_p_impl->get_impl(group_name, key);
    }

    void config::set_impl(const string_type& group_name, const string_type& key, value_type value)
    const
    {
        m_p_impl->set_impl(group_name, key, std::move(value));
    }

    void config::clear_impl(const string_type& group_name)
    const
    {
        m_p_impl->clear_impl(group_name);
    }


}}}

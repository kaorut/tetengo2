/*! \file
    \brief The definition of tetengo2::detail::windows::encoding.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <utility> // IWYU pragma: keep
#include <vector> // IWYU pragma: keep

#include <boost/core/noncopyable.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/encoding.h>
#include <tetengo2/detail/windows/windows_version.h> // IWYU pragma: keep
#include <tetengo2/stdalt.h>


namespace tetengo2::detail::windows {
    class encoding::impl : private boost::noncopyable
    {
    public:
        // types

        using pivot_type_type = encoding::pivot_type_type;

        using pivot_type = encoding::pivot_type;

        using utf8_string_type = encoding::utf8_string_type;

        using cp932_string_type = encoding::cp932_string_type;


        // static functions

        static const encoding& instance()
        {
            static const encoding singleton;
            return singleton;
        }


        // constructors

        impl() = default;


        // functions

        pivot_type_type pivot_type_impl() const
        {
            return pivot_type_type::std_wstring;
        }

        utf8_string_type pivot_to_utf8_impl(pivot_type pivot) const
        {
            const std::wstring& pivot_as_wstring = tetengo2::stdalt::get<std::wstring>(pivot);

            const ::DWORD flags = on_windows_vista_or_later() ? WC_ERR_INVALID_CHARS : 0;

            const auto string_length = ::WideCharToMultiByte(
                CP_UTF8,
                flags,
                pivot_as_wstring.c_str(),
                static_cast<int>(pivot_as_wstring.length()),
                nullptr,
                0,
                nullptr,
                nullptr);
            std::vector<char> string(string_length + 1, '\0');

            const auto converted_length = ::WideCharToMultiByte(
                CP_UTF8,
                flags,
                pivot_as_wstring.c_str(),
                static_cast<int>(pivot_as_wstring.length()),
                string.data(),
                string_length,
                nullptr,
                nullptr);
            converted_length;
            assert(converted_length == string_length);

            return { string.begin(), string.begin() + string_length };
        }

        pivot_type utf8_to_pivot_impl(utf8_string_type string) const
        {
            const auto pivot_length = ::MultiByteToWideChar(
                CP_UTF8, MB_ERR_INVALID_CHARS, string.c_str(), static_cast<int>(string.length()), nullptr, 0);
            std::vector<wchar_t> pivot(pivot_length + 1, L'\0');

            const auto converted_length = ::MultiByteToWideChar(
                CP_UTF8,
                MB_ERR_INVALID_CHARS,
                string.c_str(),
                static_cast<int>(string.length()),
                pivot.data(),
                pivot_length);
            converted_length;
            assert(converted_length == pivot_length);

            return std::wstring{ pivot.begin(), pivot.begin() + pivot_length };
        }

        cp932_string_type pivot_to_cp932_impl(pivot_type pivot) const
        {
            const std::wstring& pivot_as_wstring = tetengo2::stdalt::get<std::wstring>(pivot);

            const auto string_length = ::WideCharToMultiByte(
                932,
                0,
                pivot_as_wstring.c_str(),
                static_cast<int>(pivot_as_wstring.length()),
                nullptr,
                0,
                nullptr,
                nullptr);
            std::vector<char> string(string_length + 1, '\0');
            const ::DWORD     le = ::GetLastError();
            le;

            const auto converted_length = ::WideCharToMultiByte(
                932,
                0,
                pivot_as_wstring.c_str(),
                static_cast<int>(pivot_as_wstring.length()),
                string.data(),
                string_length,
                nullptr,
                nullptr);
            converted_length;
            assert(converted_length == string_length);

            return { string.begin(), string.begin() + string_length };
        }

        pivot_type cp932_to_pivot_impl(cp932_string_type string) const
        {
            const auto pivot_length = ::MultiByteToWideChar(
                932, MB_ERR_INVALID_CHARS, string.c_str(), static_cast<int>(string.length()), nullptr, 0);
            std::vector<wchar_t> pivot(pivot_length + 1, L'\0');

            const auto converted_length = ::MultiByteToWideChar(
                932,
                MB_ERR_INVALID_CHARS,
                string.c_str(),
                static_cast<int>(string.length()),
                pivot.data(),
                pivot_length);
            converted_length;
            assert(converted_length == pivot_length);

            return std::wstring{ pivot.begin(), pivot.begin() + pivot_length };
        }
    };


    const encoding& encoding::instance()
    {
        return impl::instance();
    }

    encoding::~encoding() = default;

    encoding::encoding() : m_p_impl{ std::make_unique<impl>() } {}

    encoding::pivot_type_type encoding::pivot_type_impl() const
    {
        return m_p_impl->pivot_type_impl();
    }

    encoding::utf8_string_type encoding::pivot_to_utf8_impl(pivot_type pivot) const
    {
        return m_p_impl->pivot_to_utf8_impl(std::move(pivot));
    }

    encoding::pivot_type encoding::utf8_to_pivot_impl(utf8_string_type string) const
    {
        return m_p_impl->utf8_to_pivot_impl(std::move(string));
    }

    encoding::cp932_string_type encoding::pivot_to_cp932_impl(pivot_type pivot) const
    {
        return m_p_impl->pivot_to_cp932_impl(std::move(pivot));
    }

    encoding::pivot_type encoding::cp932_to_pivot_impl(cp932_string_type string) const
    {
        return m_p_impl->cp932_to_pivot_impl(std::move(string));
    }
}

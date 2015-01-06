/*! \file
    \brief The definition of tetengo2::detail::windows::encoding.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_ENCODING_H)
#define TETENGO2_DETAIL_WINDOWS_ENCODING_H

#include <cassert>
#include <string>
#include <vector>

#include <boost/core/noncopyable.hpp>

//#pragma warning (push)
//#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
//#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/windows_version.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of an encoding.
    */
    class encoding : private boost::noncopyable
    {
    public:
        // types

        //! The pivot type.
        //!
        //! Stores UTF-8.
        using pivot_type = std::wstring;

        //! The UTF-8 string type.
        using utf8_string_type = std::string;

        //! The CP932 string type.
        using cp932_string_type = std::string;


        // static functions

        /*!
            \brief Converts a pivot to a UTF-8 string.

            \param pivot A pivot.

            \return A UTF-8 string.
        */
        static utf8_string_type pivot_to_utf8(const pivot_type& pivot)
        {
            const ::DWORD flags = on_windows_vista_or_later() ? WC_ERR_INVALID_CHARS : 0;

            const auto string_length =
                ::WideCharToMultiByte(
                    CP_UTF8, flags, pivot.c_str(), static_cast<int>(pivot.length()), nullptr, 0, nullptr, nullptr
                );
            std::vector<char> string(string_length + 1, '\0');

            const auto converted_length =
                ::WideCharToMultiByte(
                    CP_UTF8,
                    flags,
                    pivot.c_str(),
                    static_cast<int>(pivot.length()),
                    string.data(),
                    string_length,
                    nullptr,
                    nullptr
                );
            converted_length;
            assert(converted_length == string_length);

            return { string.begin(), string.begin() + string_length };
        }

        /*!
            \brief Converts a UTF-8 string to a pivot.

            \param string A UTF-8 string.

            \return A pivot.
        */
        static pivot_type utf8_to_pivot(const utf8_string_type& string)
        {
            const auto pivot_length =
                ::MultiByteToWideChar(
                    CP_UTF8, MB_ERR_INVALID_CHARS, string.c_str(), static_cast<int>(string.length()), nullptr, 0
                );
            std::vector<wchar_t> pivot(pivot_length + 1, L'\0');

            const auto converted_length =
                ::MultiByteToWideChar(
                    CP_UTF8,
                    MB_ERR_INVALID_CHARS,
                    string.c_str(),
                    static_cast<int>(string.length()),
                    pivot.data(),
                    pivot_length
                );
            converted_length;
            assert(converted_length == pivot_length);

            return { pivot.begin(), pivot.begin() + pivot_length };
        }

        /*!
            \brief Converts a pivot to a CP932 string.

            \param pivot A pivot.

            \return A CP932 string.
        */
        static cp932_string_type pivot_to_cp932(const pivot_type& pivot)
        {
            const auto string_length =
                ::WideCharToMultiByte(
                    932, 0, pivot.c_str(), static_cast<int>(pivot.length()), nullptr, 0, nullptr, nullptr
                );
            std::vector<char> string(string_length + 1, '\0');
            const ::DWORD le = ::GetLastError(); le;

            const auto converted_length =
                ::WideCharToMultiByte(
                    932,
                    0,
                    pivot.c_str(),
                    static_cast<int>(pivot.length()),
                    string.data(),
                    string_length,
                    nullptr,
                    nullptr
                );
            converted_length;
            assert(converted_length == string_length);

            return { string.begin(), string.begin() + string_length };
        }

        /*!
            \brief Converts a CP932 string to a pivot.

            \param string A CP932 string.

            \return A pivot.
        */
        static pivot_type cp932_to_pivot(const cp932_string_type& string)
        {
            const auto pivot_length =
                ::MultiByteToWideChar(
                    932, MB_ERR_INVALID_CHARS, string.c_str(), static_cast<int>(string.length()), nullptr, 0
                );
            std::vector<wchar_t> pivot(pivot_length + 1, L'\0');

            const auto converted_length =
                ::MultiByteToWideChar(
                    932,
                    MB_ERR_INVALID_CHARS,
                    string.c_str(),
                    static_cast<int>(string.length()),
                    pivot.data(),
                    pivot_length
                );
            converted_length;
            assert(converted_length == pivot_length);

            return { pivot.begin(), pivot.begin() + pivot_length };
        }


    private:
        // forbidden operations

        encoding()
        = delete;


   };


}}}


#endif

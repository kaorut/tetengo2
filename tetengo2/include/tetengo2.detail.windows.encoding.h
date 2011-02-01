/*! \file
    \brief The definition of tetengo2::detail::windows::encoding.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_ENCODING_H)
#define TETENGO2_DETAIL_WINDOWS_ENCODING_H

#include <cassert>
#include <cstddef>
#include <string>

#include <boost/scoped_array.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.detail.windows.windows_version.h"


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of an encoding.
    */
    class encoding
    {
    public:
        // types

        //! The pivot type.
        typedef std::wstring pivot_type;

        //! The UTF-8 string type.
        typedef std::string utf8_string_type;


        // static functions

        /*!
            \brief Converts a pivot to a UTF-8 string.

            \param pivot A pivot.

            \return A UTF-8 string.
        */
        static utf8_string_type pivot_to_utf8(const pivot_type& pivot)
        {
            const ::DWORD flags =
                tetengo2::detail::windows::on_windows_vista_or_later() ?
                WC_ERR_INVALID_CHARS : 0;

            const int string_length =
                ::WideCharToMultiByte(
                    CP_UTF8,
                    flags,
                    pivot.c_str(),
                    static_cast<int>(pivot.length()),
                    NULL,
                    0,
                    NULL,
                    NULL
                );
            const boost::scoped_array<char> p_string(
                new char[string_length + 1]
            );

            const int converted_length =
                ::WideCharToMultiByte(
                    CP_UTF8,
                    flags,
                    pivot.c_str(),
                    static_cast<int>(pivot.length()),
                    p_string.get(),
                    string_length,
                    NULL,
                    NULL
                );
            assert(converted_length == string_length);
            p_string[string_length] = '\0';

            return utf8_string_type(
                p_string.get(), p_string.get() + string_length
            );
        }

        /*!
            \brief Converts a UTF-8 string to a pivot.

            \param string A UTF-8 string.

            \return A pivot.
        */
        static pivot_type utf8_to_pivot(const utf8_string_type& string)
        {
            const int pivot_length =
                ::MultiByteToWideChar(
                    CP_UTF8,
                    MB_ERR_INVALID_CHARS,
                    string.c_str(),
                    static_cast<int>(string.length()),
                    NULL,
                    0
                );
            const boost::scoped_array<wchar_t> p_pivot(
                new wchar_t[pivot_length + 1]
            );

            const int converted_length =
                ::MultiByteToWideChar(
                    CP_UTF8,
                    MB_ERR_INVALID_CHARS,
                    string.c_str(),
                    static_cast<int>(string.length()),
                    p_pivot.get(),
                    pivot_length
                );
            assert(converted_length == pivot_length);
            p_pivot[pivot_length] = L'\0';

            return pivot_type(p_pivot.get(), p_pivot.get() + pivot_length);
        }


    private:
        // forbidden operations

        encoding();


   };


}}}


#endif

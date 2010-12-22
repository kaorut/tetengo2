/*! \file
    \brief The definition of tetengo2::encoding::win32::utf8.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODING_WIN32_UTF8_H)
#define TETENGO2_ENCODING_WIN32_UTF8_H

#include <cassert>
#include <cstddef>
//#include <string>

#include <boost/operators.hpp>
#include <boost/scoped_array.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "tetengo2.encoding.encoding.h"
#include "tetengo2.win32.detail.windows_version.h"


namespace tetengo2 { namespace encoding { namespace win32
{
    /*!
        \brief The class for a UTF-8 encoding.
    */
    class utf8 : public encoding, private boost::equality_comparable<utf8>
    {
    public:
        // types

        //! The string type.
        typedef std::string string_type;

        //! The string character type.
        typedef string_type::value_type string_char_type;


        // functions

        /*!
            \brief Checks whether one UTF-8 encoding is equal to another.

            \param one     One UTF-8 encoding.
            \param another Another UTF-8 encoding.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const utf8& one, const utf8& another)
        {
            return true;
        }

        /*!
            \brief Translates a string from the pivot encoding.

            \param pivot A pivot string.

            \return A translated string.
        */
        string_type from_pivot(const pivot_type& pivot)
        const
        {
            const ::DWORD flags =
                tetengo2::win32::detail::on_windows_vista_or_later() ?
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

            return string_type(
                p_string.get(), p_string.get() + string_length
            );
        }

        /*!
            \brief Translates a string to the pivot encoding.

            \param string A string.

            \return A translated pivot string.
        */
        pivot_type to_pivot(const string_type& string)
        const
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


    };


}}}


#endif

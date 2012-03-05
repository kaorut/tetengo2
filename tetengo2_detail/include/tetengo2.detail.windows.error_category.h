/*! \file
    \brief The definition of tetengo2::detail::windows::error_category.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_ERRORCATEGORY_H)
#define TETENGO2_DETAIL_WINDOWS_ERRORCATEGORY_H

#include <system_error>
#include <vector>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.cpp11.h"
#include "tetengo2.detail.windows.encoding.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"
#include "tetengo2.text.encoding.utf8.h"


namespace tetengo2 { namespace detail { namespace windows
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        typedef
            text::encoder<
                text::encoding::utf8<encoding>,
                text::encoding::locale<std::wstring, encoding>
            >
            encoder_type;

        inline const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }


    }
#endif

    /*!
        \brief The class for a detail implementation of an error category.
    */
    class error_category : public std::error_category
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a detail implementation of an error category.
        */
        error_category()
        :
        std::error_category()
        {}

        /*!
            \brief Destroys the detail implementation of the error category.
        */
        ~error_category()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the name.

            \return The name.
        */
        virtual const char* name()
        const
        {
            return "win32";
        }

        /*!
            \brief Returns the message.

            \param error_value An error value.

            \return The message.
        */
        virtual std::string message(const value_type error_value)
        const
        {
            const std::size_t message_capacity = 64 * 1024;
            std::vector<wchar_t> message(message_capacity, 0);
            ::DWORD message_length =
                ::FormatMessageW(
                    FORMAT_MESSAGE_FROM_SYSTEM,
                    NULL,
                    error_value,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    &message[0],
                    message_capacity,
                    NULL
                );
            if (message_length == 0)
                return "Unknown Error";

            while (
                message_length > 0 && (
                    message[message_length - 1] == L'\r' ||
                    message[message_length - 1] == L'\n'
                )
            )
            {
                --message_length;
            }

            return detail::encoder().decode(
                std::wstring(
                    message.begin(), message.begin() + message_length
                )
            );
        }


    };


    /*!
        \brief Returns the error category for Win32.

        \return The error category.
    */
    inline const std::error_category& win32_category()
    {
        static const error_category singleton;
        return singleton;
    }


}}}


#endif

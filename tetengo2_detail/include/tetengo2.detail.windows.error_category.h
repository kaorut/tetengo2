/*! \file
    \brief The definition of tetengo2::detail::windows::error_category.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_ERRORCATEGORY_H)
#define TETENGO2_DETAIL_WINDOWS_ERRORCATEGORY_H

#include <system_error>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.cpp11.h"


namespace tetengo2 { namespace detail { namespace windows
{
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
            return "test";
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

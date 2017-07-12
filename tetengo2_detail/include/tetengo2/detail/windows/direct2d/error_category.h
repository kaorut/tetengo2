/*! \file
    \brief The definition of tetengo2::detail::windows::direct2d::error_category.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_DIRECT2D_ERRORCATEGORY_H)
#define TETENGO2_DETAIL_WINDOWS_DIRECT2D_ERRORCATEGORY_H

#include <string>
#include <system_error>

#include <tetengo2/detail/windows/error_category.h>


namespace tetengo2 { namespace detail { namespace windows { namespace direct2d
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
        error_category();

        /*!
            \brief Destroys the detail implementation of the error category.
        */
        virtual ~error_category();


        // functions

        /*!
            \brief Returns the name.

            \return The name.
        */
        virtual const char* name()
        const noexcept override;

        /*!
            \brief Returns the message.

            \param error_value An error value.

            \return The message.
        */
        virtual std::string message(int error_value)
        const override;


    };


    /*!
        \brief Returns the error category for Direct2D.

        \return The error category.
    */
    const std::error_category& direct2d_category();


}}}}


#endif

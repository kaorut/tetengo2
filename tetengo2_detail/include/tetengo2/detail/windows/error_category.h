/*! \file
    \brief The definition of tetengo2::detail::windows::error_category.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_ERRORCATEGORY_H)
#define TETENGO2_DETAIL_WINDOWS_ERRORCATEGORY_H

#include <string>
#include <system_error>


namespace tetengo2::detail::windows {
    /*!
        \brief The class for a detail implementation of an error category.
    */
    class error_category : public std::error_category
    {
    public:
        // constructors and destructor

        /*!
            \brief Destroys the detail implementation of the error category.
        */
        virtual ~error_category();


        // functions

        /*!
            \brief Returns the name.

            \return The name.
        */
        virtual const char* name() const noexcept override;

        /*!
            \brief Returns the message.

            \param error_value An error value.

            \return The message.
        */
        virtual std::string message(int error_value) const override;
    };

    /*!
        \brief Returns the error category for Win32.

        \return The error category.
    */
    ;
    const std::error_category& win32_category();

    /*!
        \brief The class for a detail implementation of an error category of WIC.
    */
    class wic_error_category : public std::error_category
    {
    public:
        // constructors and destructor

        /*!
            \brief Destroys the detail implementation of the error category of WIC.
        */
        virtual ~wic_error_category();


        // functions

        /*!
            \brief Returns the name.

            \return The name.
        */
        virtual const char* name() const noexcept override;

        /*!
            \brief Returns the message.

            \param error_value An error value.

            \return The message.
        */
        virtual std::string message(int error_value) const override;
    };

    /*!
        \brief Returns the error category for WIC.

        \return The error category.
    */
    const std::error_category& wic_category();
}


#endif

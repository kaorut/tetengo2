/*! \file
    \brief The definition of tetengo2::gui::drawing::background.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_BACKGROUND_H)
#define TETENGO2_GUI_DRAWING_BACKGROUND_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/drawing.h>


namespace tetengo2::gui::drawing {
    /*!
        \brief The class for a background.
    */
    class background : private boost::noncopyable
    {
    public:
        // types

        //! The drawing details type.
        using drawing_details_type = detail::base::drawing;

        //! The details type.
        using details_type = drawing_details_type::background_details_type;

        //! The detail implementation pointer type.
        using details_ptr_type = drawing_details_type::background_details_ptr_type;


        // constructors and destructor

        /*!
            \brief Destroys the background.
        */
        virtual ~background() = default;


        // functions

        /*!
            \brief Clones the background.

            \return A unique pointer to a clone.
        */
        std::unique_ptr<background> clone() const
        {
            return clone_impl();
        }

        /*!\
            \brief Returns the detail implentation of a drawing.

            \return The detail implementation of a drawing.
        */
        const drawing_details_type& drawing_details() const
        {
            return drawing_details_impl();
        }

        /*!
            \brief Returns the detail implementation;

            \return The detail implementation.
        */
        const details_type& details() const
        {
            return details_impl();
        }

        /*!
            \brief Returns the detail implementation;

            \return The detail implementation.
        */
        details_type& details()
        {
            return details_impl();
        }


    protected:
        // constructors and destructor

        /*!
            \brief Creates a background.
        */
        background() {}


    private:
        // virtual functions

        virtual std::unique_ptr<background> clone_impl() const = 0;

        virtual const drawing_details_type& drawing_details_impl() const = 0;

        virtual const details_type& details_impl() const = 0;

        virtual details_type& details_impl() = 0;
    };
}


#endif

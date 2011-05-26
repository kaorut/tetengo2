/*! \file
    \brief The definition of tetengo2::gui::drawing::background.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_BACKGROUND_H)
#define TETENGO2_GUI_DRAWING_BACKGROUND_H

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

#include "tetengo2.cpp0x.h"


namespace tetengo2 { namespace gui { namespace drawing
{
    /*!
        \brief The class template for a background.

        \tparam DrawingDetails A detail implementation type of a drawing.
    */
    template <typename DrawingDetails>
    class background : private boost::noncopyable
    {
    public:
        // types

        //! The detail implementation type of a drawing.
        typedef DrawingDetails drawing_details_type;

        //! The detail implementation type.
        typedef
            typename drawing_details_type::background_details_type
            details_type;

        //! The detail implementation pointer type.
        typedef
            typename drawing_details_type::background_details_ptr_type
            details_ptr_type;


        // constructors and destructor

        /*!
            \brief Destroys the background.
        */
        virtual ~background()
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the detail implementation;

            \return The detail implementation.
        */
        boost::optional<const details_type&> details()
        const
        {
            return details_impl();
        }

        /*!
            \brief Returns the detail implementation;

            \return The detail implementation.
        */
        boost::optional<details_type&> details()
        {
            return details_impl();
        }


    protected:
        // constructors

        /*!
            \brief Creates a background.
        */
        background()
        {}


    private:
        // virtual functions

        virtual boost::optional<details_type&> details_impl()
        = 0;

        virtual boost::optional<const details_type&> details_impl()
        const = 0;


    };


}}}


#endif

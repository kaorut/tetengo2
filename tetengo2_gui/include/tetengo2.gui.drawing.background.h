/*! \file
    \brief The definition of tetengo2::gui::drawing::background.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_BACKGROUND_H)
#define TETENGO2_GUI_DRAWING_BACKGROUND_H

//#include <memory>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

#include "tetengo2.stdalt.h"


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
        typedef typename drawing_details_type::background_details_type details_type;

        //! The detail implementation pointer type.
        typedef typename drawing_details_type::background_details_ptr_type details_ptr_type;


        // constructors and destructor

        /*!
            \brief Destroys the background.
        */
        virtual ~background()
        TETENGO2_STDALT_NOEXCEPT
        {}


        // functions

        /*!
            \brief Clones the background.

            \return A unique pointer to a clone.
        */
        std::unique_ptr<background> clone()
        const
        {
            return clone_impl();
        }

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
        // constructors and destructor

        /*!
            \brief Creates a background.
        */
        background()
        {}


    private:
        // virtual functions

        virtual std::unique_ptr<background> clone_impl()
        const = 0;

        virtual boost::optional<details_type&> details_impl()
        = 0;

        virtual boost::optional<const details_type&> details_impl()
        const = 0;


    };


}}}


#endif

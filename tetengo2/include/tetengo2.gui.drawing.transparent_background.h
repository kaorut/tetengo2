/*! \file
    \brief The definition of tetengo2::gui::drawing::transparent_background.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_TRANSPARENTBACKGROUND_H)
#define TETENGO2_GUI_DRAWING_TRANSPARENTBACKGROUND_H

//#include <boost/optional.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.drawing.background.h"


namespace tetengo2 { namespace gui { namespace drawing
{
    /*!
        \brief The class template for a transparent background.

        \tparam DrawingDetails A detail implementation type of a drawing.
    */
    template <typename DrawingDetails>
    class transparent_background : public background<DrawingDetails>
    {
    public:
        // types

        //! The base type.
        typedef background<DrawingDetails> base_type;


        // constructors and destructor

        /*!
            \brief Creates a transparent background.
        */
        transparent_background()
        :
        base_type(),
        m_p_details(
            base_type::drawing_details_type::create_transparent_background()
        )
        {}

        /*!
            \brief Destroys the background.
        */
        virtual ~transparent_background()
        TETENGO2_CPP0X_NOEXCEPT
        {}


    private:
        // types

        typedef typename base_type::details_type details_type;

        typedef typename base_type::details_ptr_type details_ptr_type;


        // variables

        const details_ptr_type m_p_details;


        // virtual functions

        virtual boost::optional<const details_type&>
        details_impl()
        const
        {
            return boost::make_optional<const details_type&>(
                static_cast<bool>(m_p_details), *m_p_details
            );
        }

        virtual boost::optional<details_type&>
        details_impl()
        {
            return boost::make_optional<details_type&>(
                static_cast<bool>(m_p_details), *m_p_details
            );
        }


    };


}}}


#endif

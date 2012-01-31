/*! \file
    \brief The definition of tetengo2::gui::drawing::system_color_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_SYSTEMCOLORSET_H)
#define TETENGO2_GUI_DRAWING_SYSTEMCOLORSET_H

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui { namespace drawing
{
    /*!
        \brief The class template for a system color set.

        \tparam Color          A color type.
        \tparam DrawingDetails A detail implementation type of a drawing.
    */
    template <typename Color, typename DrawingDetails>
    class system_color_set : private boost::noncopyable
    {
    public:
        // types

        //! The color type.
        typedef Color color_type;

        //! The detail implementation type of a drawing.
        typedef DrawingDetails drawing_details_type;


        // static functions

        /*!
            \brief Returns the color of dialog backgrounds.

            \return The color.
        */
        static const color_type& dialog_background()
        {
            static const color_type singleton(192, 192, 192);
            return singleton;
        }


    private:
        // forbidden operations

        system_color_set();


    };


}}}


#endif

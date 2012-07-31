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

        \tparam Color              A color type.
        \tparam SystemColorDetails A detail implementation type of a system color.
    */
    template <typename Color, typename SystemColorDetails>
    class system_color_set : private boost::noncopyable
    {
    public:
        // types

        //! The color type.
        typedef Color color_type;

        //! The detail implementation type of a system color.
        typedef SystemColorDetails system_color_details_type;


        // static functions

        /*!
            \brief Returns the color of dialog backgrounds.

            \return The color.
        */
        static const color_type& dialog_background()
        {
            static const color_type singleton(
                system_color_details_type::template get_system_color<color_type>(
                    system_color_details_type::system_color_index_type::dialog_background
                )
            );
            return singleton;
        }


    private:
        // forbidden operations

        system_color_set();


    };


}}}


#endif

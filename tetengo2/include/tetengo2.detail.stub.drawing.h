/*! \file
    \brief The definition of tetengo2::detail::stub::drawing.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_DRAWING_H)
#define TETENGO2_DETAIL_STUB_DRAWING_H

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.text.h"


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a drawing.
    */
    class drawing
    {
    public:
        // types

        //! The background details type.
        struct background_details_type {};


        // static functions

        /*!
            \brief Creates a solid background.

            \tparam Color A color type.

            \param color A color.

            \return A tetengo2::cpp0x::unique_ptr::type to a solid background.
        */
        template <typename Color>
        tetengo2::cpp0x::unique_ptr<background_details_type>::type
        create_solid_background(const Color& color)
        {
            return tetengo2::cpp0x::unique_ptr<background_details_type>::type(
                new background_details_type()
            );
        }

        /*!
            \brief Makes a dialog font.

            \tparam Font A font type.

            \return A dialog font.
        */
        template <typename Font>
        static Font make_dialog_font()
        {
            return Font(
                TETENGO2_TEXT("TetengoFont"), 12, false, false, false, false
            );
        }


    private:
        // forbidden operations

        drawing();


    };


}}}


#endif

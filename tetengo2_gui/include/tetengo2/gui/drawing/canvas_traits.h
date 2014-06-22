/*! \file
    \brief The definition of tetengo2::gui::drawing::canvas_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_CANVASTRAITS_H)
#define TETENGO2_GUI_DRAWING_CANVASTRAITS_H

#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/drawing/picture.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/icon.h>


namespace tetengo2 { namespace gui { namespace drawing
{
    /*!
        \brief The traits class template for a canvas.

        \tparam Size            A size type.
        \tparam IntSize         An integer size type.
        \tparam String          A string type.
        \tparam Path            A path type.
        \tparam Position        A position type.
        \tparam Dimension       A dimension type.
        \tparam Encoder         An encoder type.
        \tparam DrawingDetails  A drawing details type.
        \tparam IconDetails     An icon details type.
    */
    template <
        typename Size,
        typename IntSize,
        typename String,
        typename Path,
        typename Position,
        typename Dimension,
        typename Encoder,
        typename DrawingDetails,
        typename IconDetails
    >
    class canvas_traits
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The integer size type.
        using int_size_type = IntSize;

        //! The string type.
        using string_type = String;

        //! The path type.
        using path_type = Path;

        //! The position type.
        using position_type = Position;

        //! The dimension type.
        using dimension_type = Dimension;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The drawing details type.
        using drawing_details_type = DrawingDetails;

        //! The background type.
        using background_type = background<drawing_details_type>;

        //! The solid background type.
        using solid_background_type = solid_background<drawing_details_type>;

        //! The color type.
        using color_type = color<unsigned char>;

        //! The font type.
        using font_type = font<string_type, int_size_type, drawing_details_type>;

        //! The picture type.
        using picture_type = picture<dimension_type, drawing_details_type>;

        //! The icon details type.
        using icon_details_type = IconDetails;

        //! The icon type.
        using icon_type = gui::icon<path_type, dimension_type, icon_details_type>;


    };


}}}


#endif

/*! \file
    \brief The definition of tetengo2::gui::drawing::canvas_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_CANVASTRAITS_H)
#define TETENGO2_GUI_DRAWING_CANVASTRAITS_H


namespace tetengo2 { namespace gui { namespace drawing
{
    /*!
        \brief The traits class template for a canvas.

        \tparam Size            A size type.
        \tparam String          A string type.
        \tparam Position        A position type.
        \tparam Dimension       A dimension type.
        \tparam Encoder         An encoder type.
        \tparam Color           A color type.
        \tparam Background      A background type.
        \tparam SolidBackground A solid background type.
        \tparam Font            A font type.
        \tparam Picture         A picture type.
        \tparam Icon            An icon type.
    */
    template <
        typename Size,
        typename String,
        typename Position,
        typename Dimension,
        typename Encoder,
        typename Color,
        typename Background,
        typename SolidBackground,
        typename Font,
        typename Picture,
        typename Icon
    >
    class canvas_traits
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The string type.
        using string_type = String;

        //! The position type.
        using position_type = Position;

        //! The dimension type.
        using dimension_type = Dimension;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The color type.
        using color_type = Color;

        //! The background type.
        using background_type = Background;

        //! The solid background type.
        using solid_background_type = SolidBackground;

        //! The font type.
        using font_type = Font;

        //! The picture type.
        using picture_type = Picture;

        //! The icon type.
        using icon_type = Icon;


    };


}}}


#endif

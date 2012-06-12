/*! \file
    \brief The definition of tetengo2::gui::drawing::canvas_traits.

    Copyright (C) 2007-2012 kaoru

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
        typename Picture
    >
    class canvas_traits
    {
    public:
        // types

        //! The size type.
        typedef Size size_type;

        //! The string type.
        typedef String string_type;

        //! The position type.
        typedef Position position_type;

        //! The dimension type.
        typedef Dimension dimension_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The color type.
        typedef Color color_type;

        //! The background type.
        typedef Background background_type;

        //! The solid background type.
        typedef SolidBackground solid_background_type;

        //! The font type.
        typedef Font font_type;

        //! The picture type.
        typedef Picture picture_type;


    };


}}}


#endif

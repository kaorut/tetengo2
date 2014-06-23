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
        \tparam IntSize         An integer size type.
        \tparam String          A string type.
        \tparam Path            A path type.
        \tparam Position        A position type.
        \tparam Dimension       A dimension type.
        \tparam Encoder         An encoder type.
    */
    template <
        typename Size,
        typename IntSize,
        typename String,
        typename Path,
        typename Position,
        typename Dimension,
        typename Encoder
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


    };


}}}


#endif

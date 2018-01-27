/*! \file
    \brief The definition of tetengo2::gui::widget::widget_traits.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_WIDGETTRAITS_H)
#define TETENGO2_GUI_WIDGET_WIDGETTRAITS_H


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The traits class template for a GUI widget.

        \tparam Size       A size type.
        \tparam Difference A difference type.
        \tparam String     A string type.
        \tparam Position   A position type.
        \tparam Dimension  A dimension type.
        \tparam Encoder    An encoder type.
   */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename Position,
        typename Dimension,
        typename Encoder
    >
    struct widget_traits
    {
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The position type.
        using position_type = Position;

        //! The dimension type.
        using dimension_type = Dimension;

        //! The encoder type.
        using encoder_type = Encoder;


    };


}}}


#endif

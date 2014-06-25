/*! \file
    \brief The definition of tetengo2::gui::widget::traits::widget_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_WIDGETTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_WIDGETTRAITS_H

#include <tetengo2/gui/measure.h>


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a GUI widget.

        \tparam Size             A size type.
        \tparam UnitSize         A unit size type.
        \tparam Difference       A difference type.
        \tparam String           A string type.
        \tparam Path             A path type.
        \tparam Position         A position type.
        \tparam Dimension        A dimension type.
        \tparam Encoder          An encoder type.
        \tparam ExceptionEncoder An exception encoder type.
   */
    template <
        typename Size,
        typename UnitSize,
        typename Difference,
        typename String,
        typename Path,
        typename Position,
        typename Dimension,
        typename Encoder,
        typename ExceptionEncoder
    >
    struct widget_traits
    {
        // types

        //! The size type.
        using size_type = Size;

        //! The unit size type.
        using unit_size_type = UnitSize;

        //! The difference type.
        using difference_type = Difference;

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

        //! The exception encoder type.
        using exception_encoder_type = ExceptionEncoder;


    };


}}}}


#endif

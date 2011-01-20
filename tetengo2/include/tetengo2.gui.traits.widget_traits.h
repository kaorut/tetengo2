/*! \file
    \brief The definition of tetengo2::gui::traits::widget_traits.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_TRAITS_WIDGETTRAITS_H)
#define TETENGO2_GUI_TRAITS_WIDGETTRAITS_H

#include "tetengo2.gui.measure.h"


namespace tetengo2 { namespace gui { namespace traits
{
    /*!
        \brief The traits class template for a GUI widget.
 
        \tparam Handle           A handle type to the native interface.
        \tparam Canvas           A canvas type.
        \tparam Alert            An alerting unary functor type.
        \tparam Position         A position type.
        \tparam Dimension        A dimension type.
        \tparam String           A string type.
        \tparam Encoder          An encoder type.
        \tparam Background       A background type.
        \tparam Font             A font type.
        \tparam PaintObserverSet A paint observer set type.
        \tparam MouseObserverSet A mouse observer set type.
   */
    template <
        typename Handle,
        typename Canvas,
        typename Alert,
        typename Position,
        typename Dimension,
        typename String,
        typename Encoder,
        typename Background,
        typename Font,
        typename PaintObserverSet,
        typename MouseObserverSet
    >
    struct widget_traits
    {
        // types

        //! The handle type.
        typedef Handle handle_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The alerting unary functor type.
        typedef Alert alert_type;

        //! The position type.
        typedef Position position_type;

        //! The dimension type.
        typedef Dimension dimension_type;

        //! The difference type.
        typedef
            typename tetengo2::gui::position<position_type>::left_type
            difference_type;

        //! The size type.
        typedef
            typename tetengo2::gui::dimension<dimension_type>::width_type
            size_type;

        //! The string type.
        typedef String string_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The background type.
        typedef Background background_type;

        //! The font type.
        typedef Font font_type;

        //! The paint observer set type.
        typedef PaintObserverSet paint_observer_set_type;

        //! The mouse observer set type.
        typedef MouseObserverSet mouse_observer_set_type;


    };


}}}


#endif

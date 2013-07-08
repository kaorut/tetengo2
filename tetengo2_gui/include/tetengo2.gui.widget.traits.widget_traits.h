/*! \file
    \brief The definition of tetengo2::gui::widget::traits::widget_traits.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_WIDGETTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_WIDGETTRAITS_H

#include "tetengo2.gui.measure.h"


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a GUI widget.

        \tparam WidgetCanvas        A widget canvas type.
        \tparam Alert               An alert type.
        \tparam Position            A position type.
        \tparam Dimension           A dimension type.
        \tparam String              A string type.
        \tparam Encoder             An encoder type.
        \tparam Background          A background type.
        \tparam Font                A font type.
        \tparam SystemCursor        A system cursor type.
        \tparam ScrollBar           A scroll bar type.
        \tparam SizeObserverSet     A size observer set type.
        \tparam FocusObserverSet    A focus observer set type.
        \tparam PaintObserverSet    A paint observer set type.
        \tparam KeyboardObserverSet A keyboard observer set type.
        \tparam MouseObserverSet    A mouse observer set type.
   */
    template <
        typename WidgetCanvas,
        typename Alert,
        typename Position,
        typename Dimension,
        typename String,
        typename Encoder,
        typename Background,
        typename Font,
        typename SystemCursor,
        typename ScrollBar,
        typename SizeObserverSet,
        typename FocusObserverSet,
        typename PaintObserverSet,
        typename KeyboardObserverSet,
        typename MouseObserverSet
    >
    struct widget_traits
    {
        // types

        //! The widget canvas type.
        typedef WidgetCanvas widget_canvas_type;

        //! The canvas type.
        typedef typename widget_canvas_type::base_type canvas_type;

        //! The alert type.
        typedef Alert alert_type;

        //! The position type.
        typedef Position position_type;

        //! The dimension type.
        typedef Dimension dimension_type;

        //! The difference type.
        typedef typename gui::position<position_type>::left_type difference_type;

        //! The size type.
        typedef typename gui::dimension<dimension_type>::width_type size_type;

        //! The string type.
        typedef String string_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The background type.
        typedef Background background_type;

        //! The font type.
        typedef Font font_type;

        //! The system cursor type.
        typedef SystemCursor system_cursor_type;

        //! The scroll bar type.
        typedef ScrollBar scroll_bar_type;

        //! The size observer set type.
        typedef SizeObserverSet size_observer_set_type;

        //! The focus observer set type.
        typedef FocusObserverSet focus_observer_set_type;

        //! The paint observer set type.
        typedef PaintObserverSet paint_observer_set_type;

        //! The keyboard observer set type.
        typedef KeyboardObserverSet keyboard_observer_set_type;

        //! The mouse observer set type.
        typedef MouseObserverSet mouse_observer_set_type;


    };


}}}}


#endif

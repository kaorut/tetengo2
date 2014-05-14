/*! \file
    \brief The definition of tetengo2::gui::widget::traits::widget_traits.

    Copyright (C) 2007-2014 kaoru

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
        using widget_canvas_type = WidgetCanvas;

        //! The canvas type.
        using canvas_type = typename widget_canvas_type::base_type;

        //! The alert type.
        using alert_type = Alert;

        //! The position type.
        using position_type = Position;

        //! The dimension type.
        using dimension_type = Dimension;

        //! The difference type.
        using difference_type = typename gui::position<position_type>::left_type;

        //! The size type.
        using size_type = typename gui::dimension<dimension_type>::width_type;

        //! The string type.
        using string_type = String;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The background type.
        using background_type = Background;

        //! The font type.
        using font_type = Font;

        //! The system cursor type.
        using system_cursor_type = SystemCursor;

        //! The scroll bar type.
        using scroll_bar_type = ScrollBar;

        //! The size observer set type.
        using size_observer_set_type = SizeObserverSet;

        //! The focus observer set type.
        using focus_observer_set_type = FocusObserverSet;

        //! The paint observer set type.
        using paint_observer_set_type = PaintObserverSet;

        //! The keyboard observer set type.
        using keyboard_observer_set_type = KeyboardObserverSet;

        //! The mouse observer set type.
        using mouse_observer_set_type = MouseObserverSet;


    };


}}}}


#endif

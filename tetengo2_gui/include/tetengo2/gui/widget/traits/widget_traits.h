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
        \tparam String           A string type.
        \tparam Path             A path type.
        \tparam Position         A position type.
        \tparam Dimension        A dimension type.
        \tparam Encoder          An encoder type.
        \tparam ExceptionEncoder An exception encoder type.

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
        typename Size,
        typename UnitSize,
        typename String,
        typename Path,
        typename Position,
        typename Dimension,
        typename Encoder,
        typename ExceptionEncoder,

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

        //! The size type.
        using size_type = Size;

        //! The unit size type.
        using unit_size_type = UnitSize;

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

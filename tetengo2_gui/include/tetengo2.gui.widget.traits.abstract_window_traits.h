/*! \file
    \brief The definition of tetengo2::gui::widget::traits::abstract_window_traits.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_ABSTRACTWINDOWTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_ABSTRACTWINDOWTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for an abstract window.

        \tparam WidgetTraits      A traits type for a GUI widget.
        \tparam MenuBar           A menu bar type.
        \tparam WindowObserverSet A window observer set type.
   */
    template <
        typename WidgetTraits,
        typename MenuBar,
        typename WindowObserverSet
    >
    struct abstract_window_traits
    {
        //types

        //! The base type.
        typedef WidgetTraits base_type;

        //! The menu bar type.
        typedef MenuBar menu_bar_type;

        //! The window observer set type.
        typedef WindowObserverSet window_observer_set_type;


    };


}}}}


#endif

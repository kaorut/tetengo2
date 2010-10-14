/*! \file
    \brief The definition of tetengo2::gui::abstract_window_traits.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_ABSTRACTWINDOWTRAITS_H)
#define TETENGO2_GUI_ABSTRACTWINDOWTRAITS_H


namespace tetengo2 { namespace gui
{
    /*!
        \brief The traits class template for an abstract window.
 
        \tparam WidgetTraits      A traits type for a GUI widget.
        \tparam MainMenu          A main menu type.
        \tparam WindowObserverSet A window observer set type.
   */
    template <
        typename WidgetTraits,
        typename MainMenu,
        typename WindowObserverSet
    >
    struct abstract_window_traits
    {
        //types

        //! The base type.
        typedef WidgetTraits base_type;

        //! The main menu type.
        typedef MainMenu main_menu_type;

        //! The window observer set type.
        typedef WindowObserverSet window_observer_set_type;


    };


}}


#endif

/*! \file
    \brief The definition of tetengo2::gui::menu::traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_TRAITS_H)
#define TETENGO2_GUI_MENU_TRAITS_H


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The traits class template for a menu.

        \tparam String          A string type.
        \tparam ShortcutKey     A shortcut key type.
        \tparam Encoder         An encoder type.
        \tparam MenuObserverSet A menu observer set type.
   */
    template <typename String, typename ShortcutKey, typename Encoder, typename MenuObserverSet>
    struct traits
    {
        //types

        //! The string type.
        typedef String string_type;

        //! The shortcut key type.
        typedef ShortcutKey shortcut_key_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The menu observer set type.
        typedef MenuObserverSet menu_observer_set_type;


    };




}}}


#endif

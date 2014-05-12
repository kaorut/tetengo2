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
        using string_type = String;

        //! The shortcut key type.
        using shortcut_key_type = ShortcutKey;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The menu observer set type.
        using menu_observer_set_type = MenuObserverSet;


    };




}}}


#endif

/*! \file
    \brief The definition of tetengo2::gui::menu::command.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_COMMAND_H)
#define TETENGO2_GUI_MENU_COMMAND_H

#include <algorithm>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/menu.h>
#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::menu {
    /*!
        \brief The class for a menu command.
   */
    class command : public menu_base
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The base type.
        using base_type = menu_base;

        //! The shortcut key type.
        using shortcut_key_type = typename base_type::shortcut_key_type;


        // constructors and destructor

        /*!
            \brief Creates a menu command without a shortcut key.

            \param text A text.
        */
        explicit command(string_type text)
        : base_type{ std::move(text), detail::gui_detail_impl_set().menu_().create_menu() }
        {}

        /*!
            \brief Creates a menu command with a shortcut key.

            \param text         A text.
            \param shortcut_key A shortcut key.
        */
        command(string_type text, shortcut_key_type shortcut_key)
        : base_type{ std::move(text), std::move(shortcut_key), detail::gui_detail_impl_set().menu_().create_menu() }
        {}

        /*!
            \brief Destroys the menu command.
        */
        virtual ~command() = default;


    private:
        // types

        using style_type = typename base_type::style_type;


        // virtual functions

        virtual const style_type& style_impl() const override
        {
            return detail::gui_detail_impl_set().menu_().menu_command_style();
        }
    };
}


#endif

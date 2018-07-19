/*! \file
    \brief The definition of tetengo2::gui::menu::command.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_COMMAND_H)
#define TETENGO2_GUI_MENU_COMMAND_H

#include <algorithm>

#include <tetengo2/detail/stub/menu.h>
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

        //! The menu details type.
        using menu_details_type = detail::stub::menu;

        //! The base type.
        using base_type = menu_base;

        //! The shortcut key type.
        using shortcut_key_type = typename base_type::shortcut_key_type;


        // constructors and destructor

        /*!
            \brief Creates a menu command without a shortcut key.

            \param text A text.
        */
        explicit command(string_type text) : base_type{ std::move(text), menu_details_type::create_menu() } {}

        /*!
            \brief Creates a menu command with a shortcut key.

            \param text         A text.
            \param shortcut_key A shortcut key.
        */
        command(string_type text, shortcut_key_type shortcut_key)
        : base_type{ std::move(text), std::move(shortcut_key), menu_details_type::create_menu() }
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
            return menu_details_type::template menu_command_style<base_type>();
        }
    };
}


#endif

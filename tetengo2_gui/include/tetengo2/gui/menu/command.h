/*! \file
    \brief The definition of tetengo2::gui::menu::command.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_COMMAND_H)
#define TETENGO2_GUI_MENU_COMMAND_H

#include <memory>

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

        //! The style type.
        using style_type = typename base_type::style_type;


        // constructors and destructor

        /*!
            \brief Creates a menu command without a shortcut key.

            \param text A text.
        */
        explicit command(string_type text);

        /*!
            \brief Creates a menu command with a shortcut key.

            \param text         A text.
            \param shortcut_key A shortcut key.
        */
        command(string_type text, shortcut_key_type shortcut_key);

        /*!
            \brief Destroys the menu command.
        */
        virtual ~command();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual const style_type& style_impl() const override;
    };
}


#endif

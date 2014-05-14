/*! \file
    \brief The definition of tetengo2::gui::menu::command.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_COMMAND_H)
#define TETENGO2_GUI_MENU_COMMAND_H

#include <utility>

#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The class template for a menu command.

        \tparam Traits      A traits type.
        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename Traits, typename MenuDetails>
    class command : public menu_base<Traits, MenuDetails>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The detail implementation type of a menu.
        using menu_details_type = MenuDetails;

        //! The base type.
        using base_type = menu_base<traits_type, menu_details_type>;

        //! The string type.
        using string_type = typename base_type::string_type;

        //! The shortcut key type.
        using shortcut_key_type = typename base_type::shortcut_key_type;


        // constructors and destructor

        /*!
            \brief Creates a menu command without a shortcut key.

            \param text A text.
        */
        explicit command(string_type text)
        :
        base_type(std::move(text), menu_details_type::create_menu())
        {}

        /*!
            \brief Creates a menu command with a shortcut key.

            \param text         A text.
            \param shortcut_key A shortcut key.
        */
        command(string_type text, shortcut_key_type shortcut_key)
        :
        base_type(std::move(text), std::move(shortcut_key), menu_details_type::create_menu())
        {}

        /*!
            \brief Destroys the menu command.
        */
        virtual ~command()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        // types

        using style_type = typename base_type::style_type;


        // virtual functions

        virtual const style_type& style_impl()
        const override
        {
            return menu_details_type::template menu_command_style<base_type>();
        }


    };


}}}


#endif

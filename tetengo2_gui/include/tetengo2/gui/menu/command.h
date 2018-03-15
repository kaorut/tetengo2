/*! \file
    \brief The definition of tetengo2::gui::menu::command.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_COMMAND_H)
#define TETENGO2_GUI_MENU_COMMAND_H

#include <tetengo2/gui/menu/menu_base.h>


namespace tetengo2 { namespace gui { namespace menu {
    /*!
        \brief The class template for a menu command.

        \tparam String            A string type.
        \tparam Encoder           An encoder type.
        \tparam MenuDetails       A detail implementation type of a menu.
        \tparam VirtualKeyDetails A detail implementation type of a virtual key.
   */
    template <typename String, typename Encoder, typename MenuDetails, typename VirtualKeyDetails>
    class command : public menu_base<String, Encoder, MenuDetails, VirtualKeyDetails>
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The virtual key details type.
        using virtual_key_details_type = VirtualKeyDetails;

        //! The base type.
        using base_type = menu_base<string_type, encoder_type, menu_details_type, virtual_key_details_type>;

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


}}}


#endif

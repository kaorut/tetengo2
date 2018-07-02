/*! \file
    \brief The definition of tetengo2::gui::menu::separator.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_SEPARATOR_H)
#define TETENGO2_GUI_MENU_SEPARATOR_H

#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::menu {
    /*!
        \brief The class template for a menu separator.

        The text is empty.

        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename MenuDetails>
    class separator : public menu_base<MenuDetails>
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The base type.
        using base_type = menu_base<menu_details_type>;


        // constructors and destructor

        /*!
            \brief Creates a menu separator.
        */
        separator() : base_type{ string_type{}, menu_details_type::create_menu() } {}

        /*!
            \brief Destroys the menu separator.
        */
        virtual ~separator() = default;


    private:
        // types

        using style_type = typename base_type::style_type;


        // virtual functions

        virtual const style_type& style_impl() const override
        {
            return menu_details_type::template menu_separator_style<base_type>();
        }
    };
}


#endif

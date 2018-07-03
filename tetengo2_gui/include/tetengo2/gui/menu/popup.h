/*! \file
    \brief The definition of tetengo2::gui::menu::popup.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_POPUP_H)
#define TETENGO2_GUI_MENU_POPUP_H

#include <algorithm>

#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::menu {
    /*!
        \brief The class template for a popup menu.

        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename MenuDetails>
    class popup : public abstract_popup<MenuDetails>
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The base type.
        using base_type = abstract_popup<menu_details_type>;


        // constructors and destructor

        /*!
            \brief Creates a popup menu.

            \param text A text.
        */
        explicit popup(string_type text) : base_type{ std::move(text), menu_details_type::create_popup_menu() } {}

        /*!
            \brief Destroys the popup menu.
        */
        virtual ~popup() = default;


    private:
        // types

        using style_type = typename base_type::style_type;


        // virtual functions

        virtual const style_type& style_impl() const override
        {
            return menu_details_type::template popup_menu_style<typename base_type::base_type>();
        }
    };
}


#endif

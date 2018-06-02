/*! \file
    \brief The definition of tetengo2::gui::menu::popup.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_POPUP_H)
#define TETENGO2_GUI_MENU_POPUP_H

#include <tetengo2/gui/menu/abstract_popup.h>


namespace tetengo2::gui::menu {
    /*!
        \brief The class template for a popup menu.

        \tparam String      A string type.
        \tparam Encoder     An encoder type.
        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename String, typename Encoder, typename MenuDetails>
    class popup : public abstract_popup<String, Encoder, MenuDetails>
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The base type.
        using base_type = abstract_popup<string_type, encoder_type, menu_details_type>;


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

/*! \file
    \brief The definition of tetengo2::gui::menu::popup.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_POPUP_H)
#define TETENGO2_GUI_MENU_POPUP_H

#include <memory>

#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::menu {
    /*!
        \brief The class for a popup menu.
   */
    class popup : public abstract_popup
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The base type.
        using base_type = abstract_popup;

        //! The style type.
        using style_type = typename base_type::style_type;


        // constructors and destructor

        /*!
            \brief Creates a popup menu.

            \param text A text.
        */
        explicit popup(string_type text);

        /*!
            \brief Destroys the popup menu.
        */
        virtual ~popup();


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

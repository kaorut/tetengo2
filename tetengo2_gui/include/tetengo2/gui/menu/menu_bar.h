/*! \file
    \brief The definition of tetengo2::gui::menu::menu_bar.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_MENUBAR_H)
#define TETENGO2_GUI_MENU_MENUBAR_H

#include <cassert>
#include <memory>

#include <tetengo2/detail/stub/menu.h>
#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/shortcut_key_table.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::menu {
    /*!
        \brief The class for a menu bar.
   */
    class menu_bar : public abstract_popup
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The menu details type.
        using menu_details_type = detail::stub::menu;

        //! The base type.
        using base_type = abstract_popup;

        //! The shortcut key table type.
        using shortcut_key_table_type = shortcut_key_table;


        // constructors and destructor

        /*!
            \brief Creates a menu bar.
        */
        menu_bar()
        : base_type{ string_type{}, menu_details_type::instance().create_menu_bar() }, m_p_shortcut_key_table{
              std::make_unique<shortcut_key_table_type>()
          }
        {}

        /*!
            \brief Destroys the menu bar.
        */
        virtual ~menu_bar() = default;


        // functions

        /*!
            \brief Returns the shortcut key table.

            \return The shortcut key table.
        */
        const shortcut_key_table_type& get_shortcut_key_table() const
        {
            assert(m_p_shortcut_key_table);
            return *m_p_shortcut_key_table;
        }

        /*!
            \brief Updates the shortcut key table.
        */
        void update_shortcut_key_table()
        {
            m_p_shortcut_key_table = std::make_unique<shortcut_key_table_type>(*this);
        }


    private:
        // types

        using style_type = typename base_type::base_type::style_type;


        // variables

        std::unique_ptr<shortcut_key_table_type> m_p_shortcut_key_table;


        // virtual functions

        virtual const style_type& style_impl() const override
        {
            return menu_details_type::instance().menu_bar_style();
        }
    };
}


#endif

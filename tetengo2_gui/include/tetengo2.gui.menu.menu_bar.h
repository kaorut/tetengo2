/*! \file
    \brief The definition of tetengo2::gui::menu::menu_bar.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_MENUBAR_H)
#define TETENGO2_GUI_MENU_MENUBAR_H

#include "tetengo2.cpp11.h"
#include "tetengo2.gui.menu.abstract_popup.h"


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The class template for a menu bar.

        \tparam Traits           A traits type.
        \tparam ShortcutKeyTable A shortcut key table type.
        \tparam MenuDetails      A detail implementation type of a menu.
   */
    template <
        typename Traits,
        typename ShortcutKeyTable,
        typename MenuDetails
    >
    class menu_bar : public abstract_popup<Traits, MenuDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The shortcut key table type.
        typedef ShortcutKeyTable shortcut_key_table_type;

        //! The detail implementation type of a menu.
        typedef MenuDetails menu_details_type;

        //! The base type.
        typedef abstract_popup<traits_type, menu_details_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a menu bar.
        */
        menu_bar()
        :
        base_type(string_type(), menu_details_type::create_menu_bar()),
        m_shortcut_key_table()
        {}

        /*!
            \brief Destroys the menu bar.
        */
        virtual ~menu_bar()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef typename base_type::string_type string_type;

        typedef typename base_type::style_type style_type;


        // variables

        shortcut_key_table_type m_shortcut_key_table;


        // virtual functions

        virtual const style_type& style_impl()
        const
        {
            return menu_details_type::menu_bar_style();
        }


    };


}}}


#endif

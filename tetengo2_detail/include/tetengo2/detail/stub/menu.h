/*! \file
    \brief The definition of tetengo2::detail::stub::menu.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_MENU_H)
#define TETENGO2_DETAIL_STUB_MENU_H

#include <memory>

#include <tetengo2/detail/base/menu.h>

namespace tetengo2 { namespace gui { namespace menu {
    class abstract_popup;
    class menu_base;
}}}


namespace tetengo2::detail::stub {
    /*!
        \brief The class for a detail implementation of a menu.
    */
    class menu : public base::menu
    {
    public:
        // types

        //! The menu details type.
        using menu_details_type = base::menu::menu_details_type;

        //! The menu details pointer type.
        using menu_details_ptr_type = base::menu::menu_details_ptr_type;

        //! The shortcut key table details type.
        using shortcut_key_table_details_type = base::menu::shortcut_key_table_details_type;

        //! The shortcut key table details pointer type.
        using shortcut_key_table_details_ptr_type = base::menu::shortcut_key_table_details_ptr_type;

        //! The style tag type.
        using style_tag = base::menu::style_tag;

        //! The state type.
        using state_type = menu::state_type;

        //! The iterator type.
        using iterator = menu::iterator;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const menu& instance();


        // constructors and destructor

        /*!
            \brief Destroy the detail implementation.
        */
        virtual ~menu();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        menu();


        // virtual functions

        virtual menu_details_ptr_type create_menu_bar_impl() const override;

        virtual menu_details_ptr_type create_popup_menu_impl() const override;

        virtual menu_details_ptr_type create_menu_impl() const override;

        virtual void set_enabled_impl(gui::menu::menu_base& menu, bool enabled) const override;

        virtual void set_state_impl(gui::menu::menu_base& menu, state_type state) const override;

        virtual shortcut_key_table_details_ptr_type create_shortcut_key_table_impl() const override;

        virtual shortcut_key_table_details_ptr_type
        create_shortcut_key_table_impl(const gui::menu::menu_base& root_menu) const override;

        virtual void insert_menu_impl(
            gui::menu::abstract_popup& popup_menu,
            const iterator&            offset,
            gui::menu::menu_base&      menu) const override;

        virtual void erase_menus_impl(
            gui::menu::abstract_popup& popup_menu,
            const iterator&            first,
            const iterator&            last) const override;
    };
}


#endif

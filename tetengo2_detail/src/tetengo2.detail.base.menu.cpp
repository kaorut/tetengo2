/*! \file
    \brief The definition of tetengo2::detail::base::menu.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/menu.h>
#include <tetengo2/gui/menu/menu_base.h>

namespace tetengo2 { namespace gui { namespace menu {
    class popup;
}}}


namespace tetengo2::detail::base {
    class menu::impl : private boost::noncopyable
    {
    public:
        // types

        using menu_details_type = menu::menu_details_type;

        using menu_details_ptr_type = menu::menu_details_ptr_type;

        using shortcut_key_table_details_type = menu::shortcut_key_table_details_type;

        using shortcut_key_table_details_ptr_type = menu::shortcut_key_table_details_ptr_type;

        using style_tag = menu::style_tag;


        // static functions

        static const style_tag& menu_bar_style();

        static const style_tag& popup_menu_style();

        static const style_tag& menu_command_style();

        static const style_tag& menu_separator_style();


        // functions

        menu_details_ptr_type create_menu_bar(const menu& self) const
        {
            return self.create_menu_bar_impl();
        }

        menu_details_ptr_type create_popup_menu(const menu& self) const
        {
            return self.create_popup_menu_impl();
        }

        menu_details_ptr_type create_menu(const menu& self) const
        {
            return self.create_menu_impl();
        }

        void set_enabled(gui::menu::menu_base& menu_, const bool enabled, const menu& self) const
        {
            self.set_enabled_impl(menu_, enabled);
        }

        void
        set_state(gui::menu::menu_base& menu_, const gui::menu::menu_base::state_type state, const menu& self) const
        {
            self.set_state_impl(menu_, state);
        }

        shortcut_key_table_details_ptr_type create_shortcut_key_table(const menu& self) const
        {
            return self.create_shortcut_key_table_impl();
        }

        shortcut_key_table_details_ptr_type create_shortcut_key_table(
            const gui::menu::menu_base::const_iterator& first,
            const gui::menu::menu_base::const_iterator& last,
            const menu&                                 self) const
        {
            return self.create_shortcut_key_table_impl(first, last);
        }

        void insert_menu(
            gui::menu::popup&                           popup_menu,
            const gui::menu::menu_base::const_iterator& offset,
            gui::menu::menu_base&                       menu_,
            const menu&                                 self) const
        {
            self.insert_menu_impl(popup_menu, offset, menu_);
        }

        void erase_menus(
            gui::menu::popup&                           popup_menu,
            const gui::menu::menu_base::const_iterator& first,
            const gui::menu::menu_base::const_iterator& last,
            const menu&                                 self) const
        {
            self.erase_menus_impl(popup_menu, first, last);
        }
    };


    menu::~menu() = default;

    menu::menu_details_ptr_type menu::create_menu_bar() const
    {
        return m_p_impl->create_menu_bar(*this);
    }

    menu::menu_details_ptr_type menu::create_popup_menu() const
    {
        return m_p_impl->create_popup_menu(*this);
    }

    menu::menu_details_ptr_type menu::create_menu() const
    {
        return m_p_impl->create_menu(*this);
    }

    void menu::set_enabled(gui::menu::menu_base& menu, const bool enabled) const
    {
        m_p_impl->set_enabled(menu, enabled, *this);
    }

    void menu::set_state(gui::menu::menu_base& menu, const gui::menu::menu_base::state_type state) const
    {
        m_p_impl->set_state(menu, state, *this);
    }

    menu::shortcut_key_table_details_ptr_type menu::create_shortcut_key_table() const
    {
        return m_p_impl->create_shortcut_key_table(*this);
    }

    menu::shortcut_key_table_details_ptr_type menu::create_shortcut_key_table(
        const gui::menu::menu_base::const_iterator& first,
        const gui::menu::menu_base::const_iterator& last) const
    {
        return m_p_impl->create_shortcut_key_table(first, last, *this);
    }

    void menu::insert_menu(
        gui::menu::popup&                           popup_menu,
        const gui::menu::menu_base::const_iterator& offset,
        gui::menu::menu_base&                       menu) const
    {
        m_p_impl->insert_menu(popup_menu, offset, menu, *this);
    }

    void menu::erase_menus(
        gui::menu::popup&                           popup_menu,
        const gui::menu::menu_base::const_iterator& first,
        const gui::menu::menu_base::const_iterator& last) const
    {
        m_p_impl->erase_menus(popup_menu, first, last, *this);
    }

    menu::menu() : m_p_impl{ std::make_unique<impl>() } {}
}

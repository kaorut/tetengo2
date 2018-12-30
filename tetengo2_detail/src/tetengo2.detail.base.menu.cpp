/*! \file
    \brief The definition of tetengo2::detail::base::menu.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/menu.h>

namespace tetengo2 { namespace gui { namespace menu {
    class abstract_popup;
    class menu_base;
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

        using state_type = menu::state_type;

        using iterator = menu::iterator;


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

        void set_state(gui::menu::menu_base& menu_, const state_type state, const menu& self) const
        {
            self.set_state_impl(menu_, state);
        }

        shortcut_key_table_details_ptr_type create_shortcut_key_table(const menu& self) const
        {
            return self.create_shortcut_key_table_impl();
        }

        shortcut_key_table_details_ptr_type
        create_shortcut_key_table(const gui::menu::menu_base& root_menu, const menu& self) const
        {
            return self.create_shortcut_key_table_impl(root_menu);
        }

        void insert_menu(
            gui::menu::abstract_popup& popup_menu,
            const iterator&            offset,
            gui::menu::menu_base&      menu_,
            const menu&                self) const
        {
            self.insert_menu_impl(popup_menu, offset, menu_);
        }

        void erase_menus(
            gui::menu::abstract_popup& popup_menu,
            const iterator&            first,
            const iterator&            last,
            const menu&                self) const
        {
            self.erase_menus_impl(popup_menu, first, last);
        }


        const style_tag& menu_bar_style(const menu& self) const
        {
            return self.menu_bar_style_impl();
        }

        const style_tag& popup_menu_style(const menu& self) const
        {
            return self.popup_menu_style_impl();
        }

        const style_tag& menu_command_style(const menu& self) const
        {
            return self.menu_command_style_impl();
        }

        const style_tag& menu_separator_style(const menu& self) const
        {
            return self.menu_separator_style_impl();
        }
    };


    menu::menu_details_type::~menu_details_type() = default;

    menu::shortcut_key_table_details_type::~shortcut_key_table_details_type() = default;

    menu::style_tag::~style_tag() = default;

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

    void menu::set_state(gui::menu::menu_base& menu, const state_type state) const
    {
        m_p_impl->set_state(menu, state, *this);
    }

    menu::shortcut_key_table_details_ptr_type menu::create_shortcut_key_table() const
    {
        return m_p_impl->create_shortcut_key_table(*this);
    }

    menu::shortcut_key_table_details_ptr_type
    menu::create_shortcut_key_table(const gui::menu::menu_base& root_menu) const
    {
        return m_p_impl->create_shortcut_key_table(root_menu, *this);
    }

    void
    menu::insert_menu(gui::menu::abstract_popup& popup_menu, const iterator& offset, gui::menu::menu_base& menu) const
    {
        m_p_impl->insert_menu(popup_menu, offset, menu, *this);
    }

    void menu::erase_menus(gui::menu::abstract_popup& popup_menu, const iterator& first, const iterator& last) const
    {
        m_p_impl->erase_menus(popup_menu, first, last, *this);
    }

    const menu::style_tag& menu::menu_bar_style() const
    {
        return m_p_impl->menu_bar_style(*this);
    }

    const menu::style_tag& menu::popup_menu_style() const
    {
        return m_p_impl->popup_menu_style(*this);
    }

    const menu::style_tag& menu::menu_command_style() const
    {
        return m_p_impl->menu_command_style(*this);
    }

    const menu::style_tag& menu::menu_separator_style() const
    {
        return m_p_impl->menu_separator_style(*this);
    }

    menu::menu() : m_p_impl{ std::make_unique<impl>() } {}
}

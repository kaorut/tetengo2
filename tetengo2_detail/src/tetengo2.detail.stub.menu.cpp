/*! \file
    \brief The definition of tetengo2::detail::stub::menu.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/stub/menu.h>
#include <tetengo2/stdalt.h>

namespace tetengo2 { namespace gui { namespace menu {
    class abstract_popup;
    class menu_base;
}}}


namespace tetengo2::detail::stub {
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

        menu_details_ptr_type create_menu_bar_impl() const
        {
            return std::make_unique<menu_details_type>();
        }

        menu_details_ptr_type create_popup_menu_impl() const
        {
            return std::make_unique<menu_details_type>();
        }

        menu_details_ptr_type create_menu_impl() const
        {
            return std::make_unique<menu_details_type>();
        }

        void set_enabled_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::menu::menu_base& menu,
            TETENGO2_STDALT_MAYBE_UNUSED const bool            enabled) const
        {}

        void set_state_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::menu::menu_base& menu,
            TETENGO2_STDALT_MAYBE_UNUSED const state_type state) const
        {}

        shortcut_key_table_details_ptr_type create_shortcut_key_table_impl() const
        {
            return std::make_unique<shortcut_key_table_details_type>();
        }

        shortcut_key_table_details_ptr_type
        create_shortcut_key_table_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::menu::menu_base& root_menu) const
        {
            return std::make_unique<shortcut_key_table_details_type>();
        }

        void insert_menu_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::menu::abstract_popup& popup_menu,
            TETENGO2_STDALT_MAYBE_UNUSED const iterator& offset,
            TETENGO2_STDALT_MAYBE_UNUSED gui::menu::menu_base& menu) const
        {}

        void erase_menus_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::menu::abstract_popup& popup_menu,
            TETENGO2_STDALT_MAYBE_UNUSED const iterator& first,
            TETENGO2_STDALT_MAYBE_UNUSED const iterator& last) const
        {}

        const style_tag& menu_bar_style_impl() const
        {
            static const style_tag singleton;
            return singleton;
        }

        const style_tag& popup_menu_style_impl() const
        {
            static const style_tag singleton;
            return singleton;
        }

        const style_tag& menu_command_style_impl() const
        {
            static const style_tag singleton;
            return singleton;
        }

        const style_tag& menu_separator_style_impl() const
        {
            static const style_tag singleton;
            return singleton;
        }
    };


    const menu& menu::instance()
    {
        static const menu singleton;
        return singleton;
    }

    menu::~menu() = default;

    menu::menu() : m_p_impl{ std::make_unique<impl>() } {}

    menu::menu_details_ptr_type menu::create_menu_bar_impl() const
    {
        return m_p_impl->create_menu_bar_impl();
    }

    menu::menu_details_ptr_type menu::create_popup_menu_impl() const
    {
        return m_p_impl->create_popup_menu_impl();
    }

    menu::menu_details_ptr_type menu::create_menu_impl() const
    {
        return m_p_impl->create_menu_impl();
    }

    void menu::set_enabled_impl(gui::menu::menu_base& menu, bool enabled) const
    {
        m_p_impl->set_enabled_impl(menu, enabled);
    }

    void menu::set_state_impl(gui::menu::menu_base& menu, state_type state) const
    {
        m_p_impl->set_state_impl(menu, state);
    }

    menu::shortcut_key_table_details_ptr_type menu::create_shortcut_key_table_impl() const
    {
        return m_p_impl->create_shortcut_key_table_impl();
    }

    menu::shortcut_key_table_details_ptr_type
    menu::create_shortcut_key_table_impl(const gui::menu::menu_base& root_menu) const
    {
        return m_p_impl->create_shortcut_key_table_impl(root_menu);
    }

    void menu::insert_menu_impl(
        gui::menu::abstract_popup& popup_menu,
        const iterator&            offset,
        gui::menu::menu_base&      menu) const
    {
        m_p_impl->insert_menu_impl(popup_menu, offset, menu);
    }

    void
    menu::erase_menus_impl(gui::menu::abstract_popup& popup_menu, const iterator& first, const iterator& last) const
    {
        m_p_impl->erase_menus_impl(popup_menu, first, last);
    }

    const menu::style_tag& menu::menu_bar_style_impl() const
    {
        return m_p_impl->menu_bar_style_impl();
    }

    const menu::style_tag& menu::popup_menu_style_impl() const
    {
        return m_p_impl->menu_bar_style_impl();
    }

    const menu::style_tag& menu::menu_command_style_impl() const
    {
        return m_p_impl->menu_bar_style_impl();
    }

    const menu::style_tag& menu::menu_separator_style_impl() const
    {
        return m_p_impl->menu_bar_style_impl();
    }
}

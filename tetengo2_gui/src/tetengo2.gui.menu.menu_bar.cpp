/*! \file
    \brief The definition of tetengo2::gui::menu::menu_bar.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <cassert>
#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/menu.h>
#include <tetengo2/gui/menu/menu_bar.h>


namespace tetengo2::gui::menu {
    /*!
        \brief The class for a menu bar.
   */
    class menu_bar::impl : private boost::noncopyable
    {
    public:
        // types

        using shortcut_key_table_type = menu_bar::shortcut_key_table_type;

        using style_type = menu_bar::style_type;


        // constructors and destructor

        impl() : m_p_shortcut_key_table{ std::make_unique<shortcut_key_table_type>() } {}


        // functions

        const shortcut_key_table_type& get_shortcut_key_table() const
        {
            assert(m_p_shortcut_key_table);
            return *m_p_shortcut_key_table;
        }

        void update_shortcut_key_table(menu_bar& self)
        {
            m_p_shortcut_key_table = std::make_unique<shortcut_key_table_type>(self);
        }

        const style_type& style_impl() const
        {
            return detail::gui_detail_impl_set().menu_().menu_bar_style();
        }


    private:
        // variables

        std::unique_ptr<shortcut_key_table_type> m_p_shortcut_key_table;
    };


    menu_bar::menu_bar()
    : base_type{ string_type{}, detail::gui_detail_impl_set().menu_().create_menu_bar() }, m_p_impl{
          std::make_unique<impl>()
      }
    {}

    menu_bar::~menu_bar() = default;

    const menu_bar::shortcut_key_table_type& menu_bar::get_shortcut_key_table() const
    {
        return m_p_impl->get_shortcut_key_table();
    }

    void menu_bar::update_shortcut_key_table()
    {
        m_p_impl->update_shortcut_key_table(*this);
    }

    const menu_bar::style_type& menu_bar::style_impl() const
    {
        return m_p_impl->style_impl();
    }
}

/*! \file
    \brief The definition of tetengo2::gui::menu::command.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/menu.h>
#include <tetengo2/gui/menu/command.h>


namespace tetengo2::gui::menu {
    /*!
        \brief The class for a menu command.
   */
    class command::impl : private boost::noncopyable
    {
    public:
        // types

        using style_type = command::style_type;


        // functions

        const style_type& style_impl() const
        {
            return detail::gui_detail_impl_set().menu_().menu_command_style();
        }
    };


    command::command(string_type text)
    : base_type{ std::move(text), detail::gui_detail_impl_set().menu_().create_menu() }, m_p_impl{
          std::make_unique<impl>()
      }
    {}

    command::command(string_type text, shortcut_key_type shortcut_key)
    : base_type{ std::move(text), std::move(shortcut_key), detail::gui_detail_impl_set().menu_().create_menu() },
      m_p_impl{ std::make_unique<impl>() }
    {}

    command::~command() = default;

    const command::style_type& command::style_impl() const
    {
        return m_p_impl->style_impl();
    }
}

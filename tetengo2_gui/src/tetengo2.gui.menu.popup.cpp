/*! \file
    \brief The definition of tetengo2::gui::menu::popup.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/menu.h>
#include <tetengo2/gui/menu/popup.h>


namespace tetengo2::gui::menu {
    class popup::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = popup::string_type;

        using base_type = popup::base_type;

        using style_type = popup::style_type;


        // functions

        const style_type& style_impl() const
        {
            return detail::gui_detail_impl_set().menu_().popup_menu_style();
        }
    };


    popup::popup(string_type text)
    : base_type{ std::move(text), detail::gui_detail_impl_set().menu_().create_popup_menu() }, m_p_impl{
          std::make_unique<impl>()
      }
    {}

    popup::~popup() = default;

    const popup::style_type& popup::style_impl() const
    {
        return m_p_impl->style_impl();
    }
}

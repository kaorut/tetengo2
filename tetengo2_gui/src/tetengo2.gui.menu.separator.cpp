/*! \file
    \brief The definition of tetengo2::gui::menu::separator.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/menu.h>
#include <tetengo2/gui/menu/separator.h>


namespace tetengo2::gui::menu {
    class separator::impl : private boost::noncopyable
    {
    public:
        // types

        using style_type = separator::style_type;


        // functions

        const style_type& style_impl() const
        {
            return detail::gui_detail_impl_set().menu_().menu_separator_style();
        }
    };


    separator::separator() : base_type{ string_type{}, detail::gui_detail_impl_set().menu_().create_menu() } {}

    separator::~separator() = default;

    const separator::style_type& separator::style_impl() const
    {
        return m_p_impl->style_impl();
    }
}

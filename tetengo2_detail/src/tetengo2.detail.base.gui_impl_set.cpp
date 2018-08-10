/*! \file
    \brief The definition of tetengo2::detail::base::gui_impl_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <stdexcept>

#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/gui_fixture.h>
#include <tetengo2/detail/base/gui_impl_set.h>


namespace tetengo2::detail::base {
    class alert;
    class cursor;
    class drawing;
    class icon;
    class menu;
    class shell;
    class system_color;
    class unit;
    class virtual_key;
    class widget;
}


namespace tetengo2::detail {
    namespace base {
        gui_impl_set::~gui_impl_set() = default;

        const alert& gui_impl_set::alert_() const
        {
            return alert_impl();
        }

        const cursor& gui_impl_set::cursor_() const
        {
            return cursor_impl();
        }

        const drawing& gui_impl_set::drawing_() const
        {
            return drawing_impl();
        }

        const drawing& gui_impl_set::fast_drawing() const
        {
            return fast_drawing_impl();
        }

        std::unique_ptr<gui_fixture> gui_impl_set::create_gui_fixture() const
        {
            return create_gui_fixture_impl();
        }

        const icon& gui_impl_set::icon_() const
        {
            return icon_impl();
        }

        const menu& gui_impl_set::menu_() const
        {
            return menu_impl();
        }

        const shell& gui_impl_set::shell_() const
        {
            return shell_impl();
        }

        const system_color& gui_impl_set::system_color_() const
        {
            return system_color_impl();
        }

        const unit& gui_impl_set::unit_() const
        {
            return unit_impl();
        }

        const virtual_key& gui_impl_set::virtual_key_() const
        {
            return virtual_key_impl();
        }

        const widget& gui_impl_set::widget_() const
        {
            return widget_impl();
        }

        gui_impl_set::gui_impl_set() = default;
    }


    namespace {
        const base::gui_impl_set* g_p_impl_set = nullptr;
    }

    const base::gui_impl_set& gui_detail_impl_set()
    {
        if (!g_p_impl_set)
            BOOST_THROW_EXCEPTION(std::logic_error{ "No detail implementation set is set yet." });

        return *g_p_impl_set;
    }

    void set_gui_detail_impl_set(const base::gui_impl_set& impl_set_)
    {
        g_p_impl_set = &impl_set_;
    }
}
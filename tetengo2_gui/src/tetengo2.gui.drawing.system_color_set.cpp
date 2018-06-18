/*! \file
    \brief The definition of tetengo2::gui::drawing::system_color_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/system_color.h>
#include <tetengo2/gui/drawing/system_color_set.h>


namespace tetengo2::gui::drawing {
    class system_color_set::impl : private boost::noncopyable
    {
    public:
        // types

        using color_type = system_color_set::color_type;


        // static functions

        static const system_color_set& instance()
        {
            static const system_color_set singleton{};
            return singleton;
        }


        // functions

        const color_type& title_bar_background() const
        {
            static const color_type singleton{ details().get_system_color(index_type::title_bar_background) };
            return singleton;
        }

        const color_type& title_bar_text() const
        {
            static const color_type singleton{ details().get_system_color(index_type::title_bar_text) };
            return singleton;
        }

        const color_type& dialog_background() const
        {
            static const color_type singleton{ details().get_system_color(index_type::dialog_background) };
            return singleton;
        }

        const color_type& control_background() const
        {
            static const color_type singleton{ details().get_system_color(index_type::control_background) };
            return singleton;
        }

        const color_type& control_text() const
        {
            static const color_type singleton{ details().get_system_color(index_type::control_text) };
            return singleton;
        }

        const color_type& selected_background() const
        {
            static const color_type singleton{ details().get_system_color(index_type::selected_background) };
            return singleton;
        }

        const color_type& selected_text() const
        {
            static const color_type singleton{ details().get_system_color(index_type::selected_text) };
            return singleton;
        }

        const color_type& hyperlink_text() const
        {
            static const color_type singleton{ details().get_system_color(index_type::hyperlink_text) };
            return singleton;
        }


    private:
        // types

        using index_type = detail::base::system_color::index_type;


        // static functions

        static const detail::base::system_color& details()
        {
            return detail::gui_detail_impl_set().system_color_();
        }
    };


    const system_color_set& system_color_set::instance()
    {
        return impl::instance();
    }

    const system_color_set::color_type& system_color_set::title_bar_background() const
    {
        return m_p_impl->title_bar_background();
    }

    const system_color_set::color_type& system_color_set::title_bar_text() const
    {
        return m_p_impl->title_bar_text();
    }

    const system_color_set::color_type& system_color_set::dialog_background() const
    {
        return m_p_impl->dialog_background();
    }

    const system_color_set::color_type& system_color_set::control_background() const
    {
        return m_p_impl->control_background();
    }

    const system_color_set::color_type& system_color_set::control_text() const
    {
        return m_p_impl->control_text();
    }

    const system_color_set::color_type& system_color_set::selected_background() const
    {
        return m_p_impl->selected_background();
    }

    const system_color_set::color_type& system_color_set::selected_text() const
    {
        return m_p_impl->selected_text();
    }

    const system_color_set::color_type& system_color_set::hyperlink_text() const
    {
        return m_p_impl->hyperlink_text();
    }

    system_color_set::system_color_set() : m_p_impl{ std::make_unique<impl>() } {}
}

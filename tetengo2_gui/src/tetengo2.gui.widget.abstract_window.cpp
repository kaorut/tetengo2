/*! \file
    \brief The definition of tetengo2::gui::widget::abstract_window.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>
#include <stdexcept>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_handler.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    class abstract_window::impl : private boost::noncopyable
    {
    public:
        // types

        using icon_type = abstract_window::icon_type;

        using menu_bar_type = abstract_window::menu_bar_type;

        using window_observer_set_type = abstract_window::window_observer_set_type;

        using file_drop_observer_set_type = abstract_window::file_drop_observer_set_type;

        using window_state_type = abstract_window::window_state_type;

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // constructors and destructor

        impl(const bool file_droppable)
        : m_file_droppable{ file_droppable }, m_p_icon{}, m_p_menu_bar{}, m_window_observer_set{},
          m_file_drop_observer_set{}
        {}

        ~impl() noexcept
        {
            // if (!this->destroyed())
            //    set_icon(std::unique_ptr<icon_type>{});
        }


        // functions

        void activate(abstract_window& self)
        {
            widget_details().activate(self);
        }

        window_state_type window_state(const abstract_window& self) const
        {
            return static_cast<window_state_type>(widget_details().window_state(self));
        }

        void set_window_state(const window_state_type state, abstract_window& self)
        {
            return widget_details().set_window_state(self, static_cast<widget_details_type::window_state_type>(state));
        }

        dimension_type normal_dimension(const abstract_window& self) const
        {
            return widget_details().normal_dimension(self);
        }

        bool has_icon() const
        {
            return static_cast<bool>(m_p_icon);
        }

        const icon_type& icon() const
        {
            if (!has_icon())
                BOOST_THROW_EXCEPTION((std::logic_error{ "This abstract window has no icon." }));

            return *m_p_icon;
        }

        icon_type& icon()
        {
            if (!has_icon())
                BOOST_THROW_EXCEPTION((std::logic_error{ "This abstract window has no icon." }));

            return *m_p_icon;
        }

        void set_icon(std::unique_ptr<icon_type> p_icon, abstract_window& self)
        {
            widget_details().set_icon(self, p_icon.get());
            m_p_icon = std::move(p_icon);
        }

        bool has_menu_bar() const
        {
            return static_cast<bool>(m_p_menu_bar);
        }

        const menu_bar_type& menu_bar() const
        {
            if (!has_menu_bar())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The abstract window does not have a menu bar." }));

            return *m_p_menu_bar;
        }

        menu_bar_type& menu_bar()
        {
            if (!has_menu_bar())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The abstract window does not have a menu bar." }));

            return *m_p_menu_bar;
        }

        void set_menu_bar(std::unique_ptr<menu_bar_type> p_menu_bar, abstract_window& self)
        {
            widget_details().set_menu_bar(self, static_cast<const menu_bar_type*>(nullptr));

            if (p_menu_bar)
            {
                p_menu_bar->update_shortcut_key_table();
                widget_details().set_menu_bar(self, p_menu_bar.get());
            }
            m_p_menu_bar = std::move(p_menu_bar);
        }

        bool file_droppable() const
        {
            return m_file_droppable;
        }

        const window_observer_set_type& window_observer_set() const
        {
            return m_window_observer_set;
        }

        window_observer_set_type& window_observer_set()
        {
            return m_window_observer_set;
        }

        const file_drop_observer_set_type& file_drop_observer_set() const
        {
            return m_file_drop_observer_set;
        }

        file_drop_observer_set_type& file_drop_observer_set()
        {
            return m_file_drop_observer_set;
        }

        void close(abstract_window& self)
        {
            widget_details().close(self);
        }


    private:
        // variables

        const bool m_file_droppable;

        std::unique_ptr<icon_type> m_p_icon;

        std::unique_ptr<menu_bar_type> m_p_menu_bar;

        window_observer_set_type m_window_observer_set;

        file_drop_observer_set_type m_file_drop_observer_set;
    };


    abstract_window::~abstract_window() noexcept
    {
        if (!this->destroyed())
            set_icon(std::unique_ptr<icon_type>{});
    }

    void abstract_window::activate()
    {
        m_p_impl->activate(*this);
    }

    abstract_window::window_state_type abstract_window::window_state() const
    {
        return m_p_impl->window_state(*this);
    }

    void abstract_window::set_window_state(const window_state_type state)
    {
        m_p_impl->set_window_state(state, *this);
    }

    abstract_window::dimension_type abstract_window::normal_dimension() const
    {
        return m_p_impl->normal_dimension(*this);
    }

    bool abstract_window::has_icon() const
    {
        return m_p_impl->has_icon();
    }

    const abstract_window::icon_type& abstract_window::icon() const
    {
        return m_p_impl->icon();
    }

    abstract_window::icon_type& abstract_window::icon()
    {
        return m_p_impl->icon();
    }

    void abstract_window::set_icon(std::unique_ptr<icon_type> p_icon)
    {
        m_p_impl->set_icon(std::move(p_icon), *this);
    }

    bool abstract_window::has_menu_bar() const
    {
        return m_p_impl->has_menu_bar();
    }

    const abstract_window::menu_bar_type& abstract_window::menu_bar() const
    {
        return m_p_impl->menu_bar();
    }

    abstract_window::menu_bar_type& abstract_window::menu_bar()
    {
        return m_p_impl->menu_bar();
    }

    void abstract_window::set_menu_bar(std::unique_ptr<abstract_window::menu_bar_type> p_menu_bar)
    {
        m_p_impl->set_menu_bar(std::move(p_menu_bar), *this);
    }

    bool abstract_window::file_droppable() const
    {
        return m_p_impl->file_droppable();
    }

    const abstract_window::window_observer_set_type& abstract_window::window_observer_set() const
    {
        return m_p_impl->window_observer_set();
    }

    abstract_window::window_observer_set_type& abstract_window::window_observer_set()
    {
        return m_p_impl->window_observer_set();
    }

    const abstract_window::file_drop_observer_set_type& abstract_window::file_drop_observer_set() const
    {
        return m_p_impl->file_drop_observer_set();
    }

    abstract_window::file_drop_observer_set_type& abstract_window::file_drop_observer_set()
    {
        return m_p_impl->file_drop_observer_set();
    }

    void abstract_window::close()
    {
        m_p_impl->close(*this);
    }

    abstract_window::abstract_window(
        const scroll_bar_style_type scroll_bar_style,
        const bool                  file_droppable,
        message_handler_map_type&&  message_handler_map)
    :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
      widget
    {
        scroll_bar_style, detail::gui_detail_impl_set().message_handler_().make_abstract_window_message_handler_map(
                              *this, std::move(message_handler_map))
    }
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
    , m_p_impl{ std::make_unique<impl>(file_droppable) } {}
}

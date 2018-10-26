/*! \file
    \brief The definition of tetengo2::gui::widget::custom_control.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/operators.hpp>
#include <boost/predef.h>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_handler.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/gui/message/child_observer_set.h>
#include <tetengo2/gui/mouse_capture.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/custom_control.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::widget {
    class custom_control::impl : private boost::noncopyable
    {
    public:
        // types

        using mouse_button_type = custom_control::mouse_button_type;


        // constructors and destructor

        impl() : m_p_mouse_capture{}, m_p_mouse_captured_item{ nullptr } {}


        // functions

        bool mouse_captured(const inner_item* const p_inner_item) const
        {
            return static_cast<bool>(m_p_mouse_capture) && (!p_inner_item || m_p_mouse_captured_item == p_inner_item);
        }

        bool mouse_captured(const mouse_button_type mouse_button, const inner_item* const p_inner_item) const
        {
            return static_cast<bool>(m_p_mouse_capture) && m_p_mouse_capture->button() == mouse_button &&
                   (!p_inner_item || m_p_mouse_captured_item == p_inner_item);
        }

        bool set_mouse_capture(
            const mouse_button_type mouse_button,
            const inner_item* const p_inner_item,
            custom_control&         self)
        {
            if (m_p_mouse_capture)
                return false;

            m_p_mouse_capture = std::make_unique<mouse_capture_type>(self, mouse_button);
            m_p_mouse_captured_item = p_inner_item;

            return true;
        }

        void release_mouse_capture()
        {
            m_p_mouse_captured_item = nullptr;
            m_p_mouse_capture.reset();
        }


    private:
        // types

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;

        using mouse_capture_type = gui::mouse_capture;


        // variables

        std::unique_ptr<mouse_capture_type> m_p_mouse_capture;

        const inner_item* m_p_mouse_captured_item;
    };


    custom_control::~custom_control() noexcept
    {
        try
        {
            if (this->has_parent())
                this->parent().child_observer_set().destroying()(*this);
        }
        catch (...)
        {
        }
    }

    bool custom_control::mouse_captured(const inner_item* const p_inner_item) const
    {
        return m_p_impl->mouse_captured(p_inner_item);
    }

    bool
    custom_control::mouse_captured(const mouse_button_type mouse_button, const inner_item* const p_inner_item) const
    {
        return m_p_impl->mouse_captured(mouse_button, p_inner_item);
    }

    bool custom_control::set_mouse_capture(const mouse_button_type mouse_button, const inner_item* const p_inner_item)
    {
        return m_p_impl->set_mouse_capture(mouse_button, p_inner_item, *this);
    }

    void custom_control::release_mouse_capture()
    {
        m_p_impl->release_mouse_capture();
    }

    custom_control::custom_control(widget& parent, const bool border, const scroll_bar_style_type scroll_bar_style)
    :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
      control{ scroll_bar_style,
               detail::gui_detail_impl_set().message_handler_().make_custom_control_message_handler_map(
                   *this,
                   message_handler_map_type{}),
               widget_details().create_custom_control(
                   parent,
                   border,
                   static_cast<widget_details_type::scroll_bar_style_type>(scroll_bar_style)) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
      m_p_impl{ std::make_unique<impl>() }
    {
        control::initialize(this);

        parent.child_observer_set().created()(*this);
    }


    class inner_item::impl : private boost::noncopyable
    {
    public:
        // types

        using mouse_button_type = inner_item::mouse_button_type;

        using position_type = inner_item::position_type;

        using dimension_type = inner_item::dimension_type;

        using canvas_type = inner_item::canvas_type;


        // constructors and destructors

        impl(custom_control& parent, position_type&& position, dimension_type&& dimension)
        : m_parent{ parent }, m_position{ std::move(position) }, m_dimension{ std::move(dimension) }, m_mouse_inside{
              false
          }
        {}


        // functions

        const position_type& position() const
        {
            return m_position;
        }

        void set_position(position_type position)
        {
            m_position = std::move(position);
        }

        const dimension_type& dimension() const
        {
            return m_dimension;
        }

        void set_dimension(dimension_type dimension)
        {
            m_dimension = std::move(dimension);
        }

        void resized(inner_item& self)
        {
            self.resized_impl();
        }

        void paint(canvas_type& canvas, const inner_item& self) const
        {
            self.paint_impl(canvas);
        }

        void mouse_pressed(const mouse_button_type mouse_button, const position_type& cursor_position, inner_item& self)
        {
            if (!inside(cursor_position))
                return;

            if (!this->parent().set_mouse_capture(mouse_button, &self))
                return;

            self.mouse_pressed_impl(cursor_position);
        }

        void
        mouse_released(const mouse_button_type mouse_button, const position_type& cursor_position, inner_item& self)
        {
            if (!this->parent().mouse_captured(mouse_button, &self))
                return;

            self.mouse_released_impl(cursor_position);

            this->parent().release_mouse_capture();
        }

        void mouse_moved(const position_type& cursor_position, inner_item& self)
        {
            if (this->parent().mouse_captured(&self) || inside(cursor_position))
            {
                self.mouse_moved_impl(cursor_position);
                if (!m_mouse_inside)
                {
                    self.mouse_entered_impl();
                    m_mouse_inside = true;
                }
            }
            else
            {
                if (m_mouse_inside)
                {
                    self.mouse_left_impl();
                    m_mouse_inside = false;
                }
            }
        }

        const custom_control& parent() const
        {
            return m_parent;
        }

        custom_control& parent()
        {
            return m_parent;
        }

        bool inside(const position_type& position) const
        {
            const auto& left = m_position.left();
            const auto  right = left + position_unit_type::from(m_dimension.width());
            const auto& top = m_position.top();
            const auto  bottom = top + position_unit_type::from(m_dimension.height());

            const auto& cursor_left = position.left();
            const auto& cursor_top = position.top();

            return (left <= cursor_left && cursor_left < right) && (top <= cursor_top && cursor_top < bottom);
        }

        void resized_impl() {}

        void paint_impl(TETENGO2_STDALT_MAYBE_UNUSED canvas_type& canvas) const {}

        void mouse_pressed_impl(TETENGO2_STDALT_MAYBE_UNUSED const position_type& cursor_position) {}

        void mouse_released_impl(TETENGO2_STDALT_MAYBE_UNUSED const position_type& cursor_position) {}

        void mouse_moved_impl(TETENGO2_STDALT_MAYBE_UNUSED const position_type& cursor_position) {}

        void mouse_entered_impl() {}

        void mouse_left_impl() {}


    private:
        // types

        using position_unit_type = position_type::unit_type;


        // variables

        custom_control& m_parent;

        position_type m_position;

        dimension_type m_dimension;

        bool m_mouse_inside;
    };


    inner_item::~inner_item() = default;

    const inner_item::position_type& inner_item::position() const
    {
        return m_p_impl->position();
    }

    void inner_item::set_position(position_type position)
    {
        m_p_impl->set_position(std::move(position));
    }

    const inner_item::dimension_type& inner_item::dimension() const
    {
        return m_p_impl->dimension();
    }

    void inner_item::set_dimension(dimension_type dimension)
    {
        m_p_impl->set_dimension(std::move(dimension));
    }

    void inner_item::resized()
    {
        m_p_impl->resized(*this);
    }

    void inner_item::paint(canvas_type& canvas) const
    {
        m_p_impl->paint(canvas, *this);
    }

    void inner_item::mouse_pressed(const mouse_button_type mouse_button, const position_type& cursor_position)
    {
        m_p_impl->mouse_pressed(mouse_button, cursor_position, *this);
    }

    void inner_item::mouse_released(const mouse_button_type mouse_button, const position_type& cursor_position)
    {
        m_p_impl->mouse_released(mouse_button, cursor_position, *this);
    }

    void inner_item::mouse_moved(const position_type& cursor_position)
    {
        m_p_impl->mouse_moved(cursor_position, *this);
    }

    inner_item::inner_item(custom_control& parent, position_type&& position, dimension_type&& dimension)
    : m_p_impl{ std::make_unique<impl>(parent, std::move(position), std::move(dimension)) }
    {}

    const custom_control& inner_item::parent() const
    {
        return m_p_impl->parent();
    }

    custom_control& inner_item::parent()
    {
        return m_p_impl->parent();
    }

    bool inner_item::inside(const position_type& position) const
    {
        return m_p_impl->inside(position);
    }

    void inner_item::resized_impl()
    {
        m_p_impl->resized_impl();
    }

    void inner_item::paint_impl(canvas_type& canvas) const
    {
        m_p_impl->paint_impl(canvas);
    }

    void inner_item::mouse_pressed_impl(const position_type& cursor_position)
    {
        m_p_impl->mouse_pressed_impl(cursor_position);
    }

    void inner_item::mouse_released_impl(const position_type& cursor_position)
    {
        m_p_impl->mouse_released_impl(cursor_position);
    }

    void inner_item::mouse_moved_impl(const position_type& cursor_position)
    {
        m_p_impl->mouse_moved_impl(cursor_position);
    }

    void inner_item::mouse_entered_impl()
    {
        m_p_impl->mouse_entered_impl();
    }

    void inner_item::mouse_left_impl()
    {
        m_p_impl->mouse_left_impl();
    }
}

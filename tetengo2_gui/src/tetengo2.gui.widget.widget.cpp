/*! \file
    \brief The definition of tetengo2::gui::widget::widget.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <functional>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_handler.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/drawing/canvas.h>
#include <tetengo2/gui/drawing/widget_canvas.h>
#include <tetengo2/gui/message/focus_observer_set.h>
#include <tetengo2/gui/message/mouse_observer_set.h>
#include <tetengo2/gui/message/paint_observer_set.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    class widget::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = widget::string_type;

        using position_type = widget::position_type;

        using dimension_type = widget::dimension_type;

        using widget_details_type = widget::widget_details_type;

        using details_type = widget::details_type;

        using canvas_type = widget::canvas_type;

        using widget_canvas_type = widget::widget_canvas_type;

        using background_type = widget::background_type;

        using font_type = widget::font_type;

        using cursor_type = widget::cursor_type;

        using scroll_bar_type = widget::scroll_bar_type;

        using scroll_bar_style_type = widget::scroll_bar_style_type;

        using message_handler_details_type = widget::message_handler_details_type;

        using message_handler_map_type = widget::message_handler_map_type;

        using child_type = widget::child_type;

        using child_observer_set_type = widget::child_observer_set_type;

        using size_observer_set_type = widget::size_observer_set_type;

        using focus_observer_set_type = widget::focus_observer_set_type;

        using paint_observer_set_type = widget::paint_observer_set_type;

        using keyboard_observer_set_type = widget::keyboard_observer_set_type;

        using mouse_observer_set_type = widget::mouse_observer_set_type;


        // static functions

        static void initialize(widget* const p_widget)
        {
            assert(p_widget);

            widget_details().associate_to_native_window_system(*p_widget);

            p_widget->set_font(font_type::dialog_font());

            p_widget->m_p_impl->m_p_vertical_scroll_bar = p_widget->m_p_impl->create_vertical_scroll_bar(*p_widget);
            p_widget->m_p_impl->m_p_horizontal_scroll_bar = p_widget->m_p_impl->create_horizontal_scroll_bar(*p_widget);
        }


        static const detail::base::widget& widget_details()
        {
            return detail::gui_detail_impl_set().widget_();
        }


        // constructors and destructor

        impl(const scroll_bar_style_type scroll_bar_style, message_handler_map_type&& message_handler_map, widget& self)
        : m_message_handler_map{ detail::gui_detail_impl_set().message_handler_().make_widget_message_handler_map(
              self,
              std::move(message_handler_map)) },
          m_focused{ false }, m_destroyed{ false }, m_p_background{}, m_p_cursor{},
          m_scroll_bar_style{ scroll_bar_style }, m_p_vertical_scroll_bar{}, m_p_horizontal_scroll_bar{},
          m_child_observer_set{}, m_size_observer_set{}, m_focus_observer_set{}, m_paint_observer_set{},
          m_keyboard_observer_set{}, m_mouse_observer_set{}
        {
            m_focus_observer_set.got_focus().connect([this]() { this->m_focused = true; });
            m_focus_observer_set.lost_focus().connect([this]() { this->m_focused = false; });
            m_paint_observer_set.paint_background().connect(paint_background(self));
        }


        // functions

        bool has_parent(const widget& self) const
        {
            return widget_details().has_parent(self);
        }

        const widget& parent(const widget& self) const
        {
            if (!has_parent(self))
                BOOST_THROW_EXCEPTION((std::logic_error{ "Has no parent." }));

            return widget_details().parent(self);
        }

        widget& parent(widget& self)
        {
            if (!has_parent(self))
                BOOST_THROW_EXCEPTION((std::logic_error{ "Has no parent." }));

            return widget_details().parent(self);
        }

        const widget& root_ancestor(const widget& self) const
        {
            if (!has_parent(self))
                BOOST_THROW_EXCEPTION((std::logic_error{ "Has no parent." }));

            return widget_details().root_ancestor(self);
        }

        widget& root_ancestor(widget& self)
        {
            if (!has_parent(self))
                BOOST_THROW_EXCEPTION((std::logic_error{ "Has no parent." }));

            return widget_details().root_ancestor(self);
        }

        bool enabled(const widget& self) const
        {
            return widget_details().enabled(self);
        }

        void set_enabled(const bool enabled, widget& self)
        {
            widget_details().set_enabled(self, enabled);
        }

        bool visible(const widget& self) const
        {
            return widget_details().visible(self);
        }

        void set_visible(const bool visible, widget& self)
        {
            widget_details().set_visible(self, visible);
        }

        bool focused() const
        {
            return m_focused;
        }

        void set_focus(widget& self)
        {
            widget_details().set_focus(self);
        }

        position_type position(const widget& self) const
        {
            return widget_details().position(self);
        }

        void set_position(const position_type& position, widget& self)
        {
            widget_details().move(self, position, dimension(self));
        }

        dimension_type dimension(const widget& self) const
        {
            return widget_details().dimension(self);
        }

        void set_dimension(const dimension_type& dimension, widget& self)
        {
            widget_details().move(self, position(self), dimension);
        }

        dimension_type client_dimension(const widget& self) const
        {
            return widget_details().client_dimension(self);
        }

        void set_client_dimension(const dimension_type& client_dimension, widget& self)
        {
            if (client_dimension.width() == dimension_unit_type{} || client_dimension.height() == dimension_unit_type{})
            {
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Client dimension has zero value." }));
            }

            widget_details().set_client_dimension(self, client_dimension);
        }

        void set_position_and_dimension(const position_type& position, const dimension_type& dimension, widget& self)
        {
            widget_details().move(self, position, dimension);
        }

        string_type text(const widget& self) const
        {
            return widget_details().text(self);
        }

        void set_text(string_type text, widget& self)
        {
            widget_details().set_text(self, std::move(text));
        }

        const background_type* p_background() const
        {
            return m_p_background.get();
        }

        void set_background(std::unique_ptr<background_type> p_background)
        {
            m_p_background = std::move(p_background);
        }

        font_type font(const widget& self) const
        {
            return widget_details().font(self);
        }

        void set_font(const font_type& font, widget& self)
        {
            widget_details().set_font(self, font);
        }

        const cursor_type* p_cursor() const
        {
            return m_p_cursor.get();
        }

        void set_cursor(std::unique_ptr<cursor_type> p_cursor)
        {
            m_p_cursor = std::move(p_cursor);
        }

        bool has_vertical_scroll_bar() const
        {
            return static_cast<bool>(m_p_vertical_scroll_bar);
        }

        const scroll_bar_type& vertical_scroll_bar() const
        {
            if (!has_vertical_scroll_bar())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The widget has no vertical scroll bar." }));

            return *m_p_vertical_scroll_bar;
        }

        scroll_bar_type& vertical_scroll_bar()
        {
            if (!has_vertical_scroll_bar())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The widget has no vertical scroll bar." }));

            return *m_p_vertical_scroll_bar;
        }

        bool has_horizontal_scroll_bar() const
        {
            return static_cast<bool>(m_p_horizontal_scroll_bar);
        }

        const scroll_bar_type& horizontal_scroll_bar() const
        {
            if (!has_horizontal_scroll_bar())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The widget has no horizontal scroll bar." }));

            return *m_p_horizontal_scroll_bar;
        }

        scroll_bar_type& horizontal_scroll_bar()
        {
            if (!has_horizontal_scroll_bar())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The widget has no horizontal scroll bar." }));

            return *m_p_horizontal_scroll_bar;
        }

        std::vector<std::reference_wrapper<const child_type>> children(const widget& self) const
        {
            const std::vector<std::reference_wrapper<child_type>> children_ =
                widget_details().children(const_cast<widget&>(self));
            return std::vector<std::reference_wrapper<const child_type>>{ children_.begin(), children_.end() };
        }

        std::vector<std::reference_wrapper<child_type>> children(widget& self)
        {
            return widget_details().children(self);
        }

        void repaint(const bool immediately, const widget& self) const
        {
            widget_details().repaint(self, immediately);
        }

        void repaint_partially(const position_type& position, const dimension_type& dimension, const widget& self) const
        {
            widget_details().repaint_partially(self, position, dimension);
        }

        std::unique_ptr<canvas_type> create_canvas(const widget& self) const
        {
            return std::make_unique<widget_canvas_type>(detail::gui_detail_impl_set().drawing_(), details(self));
        }

        void click() const
        {
            m_mouse_observer_set.clicked()();
        }

        void click()
        {
            m_mouse_observer_set.clicked()();
        }

        const child_observer_set_type& child_observer_set() const
        {
            return m_child_observer_set;
        }

        child_observer_set_type& child_observer_set()
        {
            return m_child_observer_set;
        }

        const size_observer_set_type& size_observer_set() const
        {
            return m_size_observer_set;
        }

        size_observer_set_type& size_observer_set()
        {
            return m_size_observer_set;
        }

        const focus_observer_set_type& focus_observer_set() const
        {
            return m_focus_observer_set;
        }

        focus_observer_set_type& focus_observer_set()
        {
            return m_focus_observer_set;
        }

        const paint_observer_set_type& paint_observer_set() const
        {
            return m_paint_observer_set;
        }

        paint_observer_set_type& paint_observer_set()
        {
            return m_paint_observer_set;
        }

        const keyboard_observer_set_type& keyboard_observer_set() const
        {
            return m_keyboard_observer_set;
        }

        keyboard_observer_set_type& keyboard_observer_set()
        {
            return m_keyboard_observer_set;
        }

        const mouse_observer_set_type& mouse_observer_set() const
        {
            return m_mouse_observer_set;
        }

        mouse_observer_set_type& mouse_observer_set()
        {
            return m_mouse_observer_set;
        }

        bool destroyed() const
        {
            return m_destroyed;
        }

        void set_destroyed()
        {
            m_destroyed = true;
        }

        const details_type& details(const widget& self) const
        {
            if (m_destroyed)
                BOOST_THROW_EXCEPTION((std::runtime_error{ "This widget is destroyed." }));

            return self.details_impl();
        }

        details_type& details(widget& self)
        {
            if (m_destroyed)
                BOOST_THROW_EXCEPTION((std::runtime_error{ "This widget is destroyed." }));

            return self.details_impl();
        }

        const message_handler_map_type& message_handler_map() const
        {
            return m_message_handler_map;
        }


    private:
        // types

        using dimension_unit_type = typename dimension_type::unit_type;

        class paint_background
        {
        public:
            paint_background(widget& self) : m_self{ self } {}

            bool operator()(canvas_type& canvas) const
            {
                if (!m_self.p_background())
                    return false;

                canvas.set_background(m_self.p_background()->clone());
                canvas.fill_rectangle(position_type{}, m_self.client_dimension());

                return true;
            }

        private:
            widget& m_self;
        };


        // variables

        const message_handler_map_type m_message_handler_map;

        bool m_focused;

        bool m_destroyed;

        std::unique_ptr<background_type> m_p_background;

        std::unique_ptr<cursor_type> m_p_cursor;

        const scroll_bar_style_type m_scroll_bar_style;

        std::unique_ptr<scroll_bar_type> m_p_vertical_scroll_bar;

        std::unique_ptr<scroll_bar_type> m_p_horizontal_scroll_bar;

        child_observer_set_type m_child_observer_set;

        size_observer_set_type m_size_observer_set;

        focus_observer_set_type m_focus_observer_set;

        paint_observer_set_type m_paint_observer_set;

        keyboard_observer_set_type m_keyboard_observer_set;

        mouse_observer_set_type m_mouse_observer_set;


        // functions

        std::unique_ptr<scroll_bar_type> create_vertical_scroll_bar(widget& self)
        {
            if (m_scroll_bar_style != scroll_bar_style_type::vertical &&
                m_scroll_bar_style != scroll_bar_style_type::both)
            {
                return {};
            }

            return std::make_unique<scroll_bar_type>(self, scroll_bar_type::style_type::vertical);
        }

        std::unique_ptr<scroll_bar_type> create_horizontal_scroll_bar(widget& self)
        {
            if (m_scroll_bar_style != scroll_bar_style_type::horizontal &&
                m_scroll_bar_style != scroll_bar_style_type::both)
            {
                return {};
            }

            return std::make_unique<scroll_bar_type>(self, scroll_bar_type::style_type::horizontal);
        }
    };


    widget::~widget() = default;

    bool widget::has_parent() const
    {
        return m_p_impl->has_parent(*this);
    }

    const widget& widget::parent() const
    {
        return m_p_impl->parent(*this);
    }

    widget& widget::parent()
    {
        return m_p_impl->parent(*this);
    }

    const widget& widget::root_ancestor() const
    {
        return m_p_impl->root_ancestor(*this);
    }

    widget& widget::root_ancestor()
    {
        return m_p_impl->root_ancestor(*this);
    }

    bool widget::enabled() const
    {
        return m_p_impl->enabled(*this);
    }

    void widget::set_enabled(const bool enabled)
    {
        m_p_impl->set_enabled(enabled, *this);
    }

    bool widget::visible() const
    {
        return m_p_impl->visible(*this);
    }

    void widget::set_visible(const bool visible)
    {
        m_p_impl->set_visible(visible, *this);
    }

    bool widget::focused() const
    {
        return m_p_impl->focused();
    }

    void widget::set_focus()
    {
        m_p_impl->set_focus(*this);
    }

    widget::position_type widget::position() const
    {
        return m_p_impl->position(*this);
    }

    void widget::set_position(const position_type& position)
    {
        m_p_impl->set_position(position, *this);
    }

    widget::dimension_type widget::dimension() const
    {
        return m_p_impl->dimension(*this);
    }

    void widget::set_dimension(const dimension_type& dimension)
    {
        m_p_impl->set_dimension(dimension, *this);
    }

    widget::dimension_type widget::client_dimension() const
    {
        return m_p_impl->client_dimension(*this);
    }

    void widget::set_client_dimension(const dimension_type& client_dimension)
    {
        m_p_impl->set_client_dimension(client_dimension, *this);
    }

    void widget::set_position_and_dimension(const position_type& position, const dimension_type& dimension)
    {
        m_p_impl->set_position_and_dimension(position, dimension, *this);
    }

    widget::string_type widget::text() const
    {
        return m_p_impl->text(*this);
    }

    void widget::set_text(string_type text)
    {
        m_p_impl->set_text(std::move(text), *this);
    }

    const widget::background_type* widget::p_background() const
    {
        return m_p_impl->p_background();
    }

    void widget::set_background(std::unique_ptr<background_type> p_background)
    {
        m_p_impl->set_background(std::move(p_background));
    }

    widget::font_type widget::font() const
    {
        return m_p_impl->font(*this);
    }

    void widget::set_font(const font_type& font)
    {
        m_p_impl->set_font(font, *this);
    }

    const widget::cursor_type* widget::p_cursor() const
    {
        return m_p_impl->p_cursor();
    }

    void widget::set_cursor(std::unique_ptr<cursor_type> p_cursor)
    {
        m_p_impl->set_cursor(std::move(p_cursor));
    }

    bool widget::has_vertical_scroll_bar() const
    {
        return m_p_impl->has_vertical_scroll_bar();
    }

    const widget::scroll_bar_type& widget::vertical_scroll_bar() const
    {
        return m_p_impl->vertical_scroll_bar();
    }

    widget::scroll_bar_type& widget::vertical_scroll_bar()
    {
        return m_p_impl->vertical_scroll_bar();
    }

    bool widget::has_horizontal_scroll_bar() const
    {
        return m_p_impl->has_horizontal_scroll_bar();
    }

    const widget::scroll_bar_type& widget::horizontal_scroll_bar() const
    {
        return m_p_impl->horizontal_scroll_bar();
    }

    widget::scroll_bar_type& widget::horizontal_scroll_bar()
    {
        return m_p_impl->horizontal_scroll_bar();
    }

    std::vector<std::reference_wrapper<const widget::child_type>> widget::children() const
    {
        return m_p_impl->children(*this);
    }

    std::vector<std::reference_wrapper<widget::child_type>> widget::children()
    {
        return m_p_impl->children(*this);
    }

    void widget::repaint(const bool immediately /*= false*/) const
    {
        m_p_impl->repaint(immediately, *this);
    }

    void widget::repaint_partially(const position_type& position, const dimension_type& dimension) const
    {
        m_p_impl->repaint_partially(position, dimension, *this);
    }

    std::unique_ptr<widget::canvas_type> widget::create_canvas() const
    {
        return m_p_impl->create_canvas(*this);
    }

    void widget::click() const
    {
        m_p_impl->click();
    }

    void widget::click()
    {
        m_p_impl->click();
    }

    const widget::child_observer_set_type& widget::child_observer_set() const
    {
        return m_p_impl->child_observer_set();
    }

    widget::child_observer_set_type& widget::child_observer_set()
    {
        return m_p_impl->child_observer_set();
    }

    const widget::size_observer_set_type& widget::size_observer_set() const
    {
        return m_p_impl->size_observer_set();
    }

    widget::size_observer_set_type& widget::size_observer_set()
    {
        return m_p_impl->size_observer_set();
    }

    const widget::focus_observer_set_type& widget::focus_observer_set() const
    {
        return m_p_impl->focus_observer_set();
    }

    widget::focus_observer_set_type& widget::focus_observer_set()
    {
        return m_p_impl->focus_observer_set();
    }

    const widget::paint_observer_set_type& widget::paint_observer_set() const
    {
        return m_p_impl->paint_observer_set();
    }

    widget::paint_observer_set_type& widget::paint_observer_set()
    {
        return m_p_impl->paint_observer_set();
    }

    const widget::keyboard_observer_set_type& widget::keyboard_observer_set() const
    {
        return m_p_impl->keyboard_observer_set();
    }

    widget::keyboard_observer_set_type& widget::keyboard_observer_set()
    {
        return m_p_impl->keyboard_observer_set();
    }

    const widget::mouse_observer_set_type& widget::mouse_observer_set() const
    {
        return m_p_impl->mouse_observer_set();
    }

    widget::mouse_observer_set_type& widget::mouse_observer_set()
    {
        return m_p_impl->mouse_observer_set();
    }

    bool widget::destroyed() const
    {
        return m_p_impl->destroyed();
    }

    void widget::set_destroyed()
    {
        m_p_impl->set_destroyed();
    }

    const widget::details_type& widget::details() const
    {
        return m_p_impl->details(*this);
    }

    widget::details_type& widget::details()
    {
        return m_p_impl->details(*this);
    }

    const widget::message_handler_map_type& widget::message_handler_map() const
    {
        return m_p_impl->message_handler_map();
    }

    void widget::initialize(widget* const p_widget)
    {
        impl::initialize(p_widget);
    }

    const detail::base::widget& widget::widget_details()
    {
        return impl::widget_details();
    }

    widget::widget(const scroll_bar_style_type scroll_bar_style, message_handler_map_type&& message_handler_map)
    : m_p_impl{ std::make_unique<impl>(scroll_bar_style, std::move(message_handler_map), *this) }
    {}
}

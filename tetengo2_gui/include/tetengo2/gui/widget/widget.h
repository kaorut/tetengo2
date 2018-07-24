/*! \file
    \brief The definition of tetengo2::gui::widget::widget.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_WIDGET_H)
#define TETENGO2_GUI_WIDGET_WIDGET_H

#include <cassert>
#include <functional>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/detail/stub/drawing.h>
#include <tetengo2/detail/stub/message_handler.h>
#include <tetengo2/detail/stub/scroll.h>
#include <tetengo2/gui/cursor/cursor_base.h>
#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/canvas.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/widget_canvas.h>
#include <tetengo2/gui/message/child_observer_set.h>
#include <tetengo2/gui/message/focus_observer_set.h>
#include <tetengo2/gui/message/keyboard_observer_set.h>
#include <tetengo2/gui/message/mouse_observer_set.h>
#include <tetengo2/gui/message/paint_observer_set.h>
#include <tetengo2/gui/message/size_observer_set.h>
#include <tetengo2/gui/scroll_bar.h>
#include <tetengo2/gui/type_list.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The base class for a GUI widget.
    */
    class widget : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The position type.
        using position_type = tetengo2::gui::type_list::position_type;

        //! The dimension type.
        using dimension_type = tetengo2::gui::type_list::dimension_type;

        //! The widget details type.
        using widget_details_type = detail::base::widget;

        //! The details type.
        using details_type = typename widget_details_type::widget_details_type;

        //! The drawing details type.
        using drawing_details_type = detail::stub::drawing;

        //! The canvas type.
        using canvas_type = gui::drawing::canvas<drawing_details_type>;

        //! The widget canvas type.
        using widget_canvas_type = gui::drawing::widget_canvas<drawing_details_type>;

        //! The background type.
        using background_type = gui::drawing::background<drawing_details_type>;

        //! The font type.
        using font_type = gui::drawing::font<drawing_details_type>;

        //! The cursor type.
        using cursor_type = gui::cursor::cursor_base;

        //! The scroll details type.
        using scroll_details_type = detail::stub::scroll;

        //! The scroll bar type.
        using scroll_bar_type = gui::scroll_bar<scroll_details_type>;

        //! The scroll bar style type.
        enum class scroll_bar_style_type
        {
            none, //!< The widget has no scroll bar.
            vertical, //!< The widget has a vertical scroll bar.
            horizontal, //!< The widget has a horizontal scroll bar.
            both, //!< The widget has both vertiacal and horizontal scroll bars.
        };

        //! The message handler details type.
        using message_handler_details_type = detail::stub::message_handler;

        //! The message handler map type.
        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;

        //! The child type.
        using child_type = widget;

        //! The child observer set type.
        using child_observer_set_type = gui::message::child_observer_set<child_type>;

        //! The size observer set type.
        using size_observer_set_type = gui::message::size_observer_set;

        //! The focus observer set type.
        using focus_observer_set_type = gui::message::focus_observer_set;

        //! The paint observer set type.
        using paint_observer_set_type = gui::message::paint_observer_set<canvas_type>;

        //! The keyboard observer set type.
        using keyboard_observer_set_type = gui::message::keyboard_observer_set;

        //! The mouse observer set type.
        using mouse_observer_set_type = gui::message::mouse_observer_set;


        // constructors and destructor

        /*!
            \brief Destroys the widget.
        */
        virtual ~widget() = default;


        // functions

        /*!
            \brief Returns whether the widget has a parent.

            \retval true  When the widget has a parent.
            \retval false Otherwise.
        */
        bool has_parent() const
        {
            return widget_details().has_parent(*this);
        }

        /*!
            \brief Returns the parent.

            \return The parent.

            \throw std::logic_error When the widget has no parent.
        */
        const widget& parent() const
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION((std::logic_error{ "Has no parent." }));

            return widget_details().parent(*this);
        }

        /*!
            \brief Returns the parent.

            \return The parent.

            \throw std::logic_error When the widget has no parent.
        */
        widget& parent()
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION((std::logic_error{ "Has no parent." }));

            return widget_details().parent(*this);
        }

        /*!
            \brief Returns the root ancestor.

            \return The root ancestor.
        */
        const widget& root_ancestor() const
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION((std::logic_error{ "Has no parent." }));

            return widget_details().root_ancestor(*this);
        }

        /*!
            \brief Returns the root ancestor.

            \return The root ancestor.
        */
        widget& root_ancestor()
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION((std::logic_error{ "Has no parent." }));

            return widget_details().root_ancestor(*this);
        }

        /*!
            \brief Returns the enabled status.

            \return The enabled status.
        */
        bool enabled() const
        {
            return widget_details().enabled(*this);
        }

        /*!
            \brief Sets an enabled status.

            \param enabled An enabled status.
        */
        void set_enabled(const bool enabled)
        {
            widget_details().set_enabled(*this, enabled);
        }

        /*!
            \brief Returns the visible status.

            \return The visible status.
        */
        bool visible() const
        {
            return widget_details().visible(*this);
        }

        /*!
            \brief Sets a visible status.

            \param visible A visible status.
        */
        void set_visible(const bool visible)
        {
            widget_details().set_visible(*this, visible);
        }

        /*!
            \brief Returns the focused status.

            \return The focused status.
        */
        bool focused() const
        {
            return m_focused;
        }

        /*!
            \brief Focuses on the widget.
        */
        void set_focus()
        {
            widget_details().set_focus(*this);
        }

        /*!
            \brief Returns the position.

            \return The position.
        */
        position_type position() const
        {
            return widget_details().position(*this);
        }

        /*!
            \brief Sets a position.

            \param position A position.
        */
        void set_position(const position_type& position)
        {
            widget_details().move(*this, position, dimension());
        }

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        dimension_type dimension() const
        {
            return widget_details().dimension(*this);
        }

        /*!
            \brief Sets a dimension.

            \param dimension A dimension.
        */
        void set_dimension(const dimension_type& dimension)
        {
            widget_details().move(*this, position(), dimension);
        }

        /*!
            \brief Returns the client dimension.

            \return The client dimension.
        */
        dimension_type client_dimension() const
        {
            return widget_details().client_dimension(*this);
        }

        /*!
            \brief Sets a client dimension.

            \param client_dimension A client dimension.

            \throw std::invalid_argument When either client_dimension.first or client_dimension.second is equal to 0.
        */
        void set_client_dimension(const dimension_type& client_dimension)
        {
            if (client_dimension.width() == dimension_unit_type{} || client_dimension.height() == dimension_unit_type{})
            {
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Client dimension has zero value." }));
            }

            widget_details().set_client_dimension(*this, client_dimension);
        }

        /*!
            \brief Sets a position and a dimension.

            \param position  A position.
            \param dimension A dimension.
        */
        void set_position_and_dimension(const position_type& position, const dimension_type& dimension)
        {
            widget_details().move(*this, position, dimension);
        }

        /*!
            \brief Retuns the text.

            \return The text.
        */
        string_type text() const
        {
            return widget_details().text(*this);
        }

        /*!
            \brief Sets a text.

            \param text A text.
        */
        void set_text(string_type text)
        {
            widget_details().set_text(*this, std::move(text));
        }

        /*!
            \brief Returns the background.

            When the system default background is used, this function returns a nullptr.

            \return The pointer to the background.
        */
        const background_type* p_background() const
        {
            return m_p_background.get();
        }

        /*!
            \brief Sets a background.

            When p_background is nullptr, the system default background is used.

            \param p_background A unique pointer to a background.
        */
        void set_background(std::unique_ptr<background_type> p_background)
        {
            m_p_background = std::move(p_background);
        }

        /*!
            \brief Retuns the font.

            \return The font.
        */
        font_type font() const
        {
            const widget_details_type::font_type detail_font = widget_details().font(*this);
            return font_type{ detail_font.family, detail_font.size,      detail_font.bold,
                              detail_font.italic, detail_font.underline, detail_font.strikeout };
        }

        /*!
            \brief Sets a font.

            \param font A font.
        */
        void set_font(const font_type& font)
        {
            const widget_details_type::font_type detail_font{ font.family(), font.size(),      font.bold(),
                                                              font.italic(), font.underline(), font.strikeout() };
            widget_details().set_font(*this, detail_font);
        }

        /*!
            \brief Returns the cursor.

            \return The pointer to the cursor.
        */
        const cursor_type* p_cursor() const
        {
            return m_p_cursor.get();
        }

        /*!
            \brief Sets a cursor.

            \param p_cursor A unique pointer to a cursor.
        */
        void set_cursor(std::unique_ptr<cursor_type> p_cursor)
        {
            m_p_cursor = std::move(p_cursor);
        }

        /*!
            \brief Checks whether the widget has a vertical scroll bar.

            \retval true  The widget has a vertical scroll bar.
        */
        bool has_vertical_scroll_bar() const
        {
            return static_cast<bool>(m_p_vertical_scroll_bar);
        }

        /*!
            \brief Returns the vertical scroll bar.

            \return The vertical scroll bar.

            \throw std::logic_error When the widget has no vertical scroll bar.
        */
        const scroll_bar_type& vertical_scroll_bar() const
        {
            if (!has_vertical_scroll_bar())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The widget has no vertical scroll bar." }));

            return *m_p_vertical_scroll_bar;
        }

        /*!
            \brief Returns the vertical scroll bar.

            \return The vertical scroll bar.

            \throw std::logic_error When the widget has no vertical scroll bar.
        */
        scroll_bar_type& vertical_scroll_bar()
        {
            if (!has_vertical_scroll_bar())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The widget has no vertical scroll bar." }));

            return *m_p_vertical_scroll_bar;
        }

        /*!
            \brief Checks whether the widget has a horizontal scroll bar.

            \retval true  The widget has a horizontal scroll bar.
        */
        bool has_horizontal_scroll_bar() const
        {
            return static_cast<bool>(m_p_horizontal_scroll_bar);
        }

        /*!
            \brief Returns the horizontal scroll bar.

            \return The horizontal scroll bar.

            \throw std::logic_error When the widget has no horizontal scroll bar.
        */
        const scroll_bar_type& horizontal_scroll_bar() const
        {
            if (!has_horizontal_scroll_bar())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The widget has no horizontal scroll bar." }));

            return *m_p_horizontal_scroll_bar;
        }

        /*!
            \brief Returns the horizontal scroll bar.

            \return The horizontal scroll bar.

            \throw std::logic_error When the widget has no horizontal scroll bar.
        */
        scroll_bar_type& horizontal_scroll_bar()
        {
            if (!has_horizontal_scroll_bar())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The widget has no horizontal scroll bar." }));

            return *m_p_horizontal_scroll_bar;
        }

        /*!
            \brief Returns the constant children.

            \return The children.
        */
        std::vector<std::reference_wrapper<const child_type>> children() const
        {
            const std::vector<std::reference_wrapper<child_type>> children_ =
                widget_details().children(const_cast<widget&>(*this));
            return std::vector<std::reference_wrapper<const child_type>>{ children_.begin(), children_.end() };
        }

        /*!
            \brief Returns the children.

            \return The children.
        */
        std::vector<std::reference_wrapper<child_type>> children()
        {
            return widget_details().children(*this);
        }

        /*!
            \brief Repaints the widget.

            \param immediately Set true to request an immediate repaint.
        */
        void repaint(const bool immediately = false) const
        {
            widget_details().repaint(*this, immediately);
        }

        /*!
            \brief Repaints the widget partially.

            \param position  The position of a region to repaint.
            \param dimension The dimension of a region to repaint.
        */
        void repaint_partially(const position_type& position, const dimension_type& dimension) const
        {
            widget_details().repaint_partially(*this, position, dimension);
        }

        /*!
            \brief Creates a canvas.

            \return The unique pointer to a canvas.
        */
        std::unique_ptr<canvas_type> create_canvas() const
        {
            return std::make_unique<widget_canvas_type>(details());
        }

        /*!
            \brief Clicks this widget.
        */
        void click() const
        {
            m_mouse_observer_set.clicked()();
        }

        /*!
            \brief Clicks this widget.
        */
        void click()
        {
            m_mouse_observer_set.clicked()();
        }

        /*!
            \brief Returns the child observer set.

            \return The child observer set.
        */
        const child_observer_set_type& child_observer_set() const
        {
            return m_child_observer_set;
        }

        /*!
            \brief Returns the child observer set.

            \return The child observer set.
        */
        child_observer_set_type& child_observer_set()
        {
            return m_child_observer_set;
        }

        /*!
            \brief Returns the size observer set.

            \return The size observer set.
        */
        const size_observer_set_type& size_observer_set() const
        {
            return m_size_observer_set;
        }

        /*!
            \brief Returns the size observer set.

            \return The size observer set.
        */
        size_observer_set_type& size_observer_set()
        {
            return m_size_observer_set;
        }

        /*!
            \brief Returns the focus observer set.

            \return The focus observer set.
        */
        const focus_observer_set_type& focus_observer_set() const
        {
            return m_focus_observer_set;
        }

        /*!
            \brief Returns the focus observer set.

            \return The focus observer set.
        */
        focus_observer_set_type& focus_observer_set()
        {
            return m_focus_observer_set;
        }

        /*!
            \brief Returns the paint observer set.

            \return The paint observer set.
        */
        const paint_observer_set_type& paint_observer_set() const
        {
            return m_paint_observer_set;
        }

        /*!
            \brief Returns the paint observer set.

            \return The paint observer set.
        */
        paint_observer_set_type& paint_observer_set()
        {
            return m_paint_observer_set;
        }

        /*!
           \brief Returns the keyboard observer set.

           \return The keyboard observer set.
       */
        const keyboard_observer_set_type& keyboard_observer_set() const
        {
            return m_keyboard_observer_set;
        }

        /*!
            \brief Returns the keyboard observer set.

            \return The keyboard observer set.
        */
        keyboard_observer_set_type& keyboard_observer_set()
        {
            return m_keyboard_observer_set;
        }

        /*!
             \brief Returns the mouse observer set.

             \return The mouse observer set.
         */
        const mouse_observer_set_type& mouse_observer_set() const
        {
            return m_mouse_observer_set;
        }

        /*!
            \brief Returns the mouse observer set.

            \return The mouse observer set.
        */
        mouse_observer_set_type& mouse_observer_set()
        {
            return m_mouse_observer_set;
        }

        /*!
            \brief Returns wether the widget is destroyed.

            \retval true  When the widget is destroyed.
            \retval false Otherwise.
        */
        bool destroyed() const
        {
            return m_destroyed;
        }

        /*!
            \brief Sets the status of the widget that it is already destroyed.
        */
        void set_destroyed()
        {
            m_destroyed = true;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.

            \throw std::runtime_error When the widget is already destroyed.
        */
        const details_type& details() const
        {
            if (m_destroyed)
                BOOST_THROW_EXCEPTION((std::runtime_error{ "This widget is destroyed." }));

            return details_impl();
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.

            \throw std::runtime_error When the widget is already destroyed.
        */
        details_type& details()
        {
            if (m_destroyed)
                BOOST_THROW_EXCEPTION((std::runtime_error{ "This widget is destroyed." }));

            return details_impl();
        }

        /*!
            \brief Returns the message handler map.

            \return The message handler map.
        */
        const message_handler_map_type& message_handler_map() const
        {
            return m_message_handler_map;
        }


    protected:
        // static functions

        /*!
            \brief Initializes the widget.

            This function must be called in the constructor and only in the constructor.

            \param p_widget A pointer to a widget.
        */
        static void initialize(widget* const p_widget)
        {
            assert(p_widget);

            widget_details().associate_to_native_window_system(*p_widget);

            p_widget->set_font(font_type::dialog_font());

            p_widget->m_p_vertical_scroll_bar = p_widget->create_vertical_scroll_bar();
            p_widget->m_p_horizontal_scroll_bar = p_widget->create_horizontal_scroll_bar();
        }


        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        static const detail::base::widget& widget_details()
        {
            return detail::gui_detail_impl_set().widget_();
        }


        // constructors and destructor

        /*!
            \brief Creates a widget.

            \param scroll_bar_style    A scroll bar style.
            \param message_handler_map A message handler map.
        */
        widget(const scroll_bar_style_type scroll_bar_style, message_handler_map_type&& message_handler_map)
        :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
          m_message_handler_map{ message_handler_details_type::instance().make_widget_message_handler_map(
              *this,
              std::move(message_handler_map)) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
          m_focused{ false }, m_destroyed{ false }, m_p_background{}, m_p_cursor{},
          m_scroll_bar_style{ scroll_bar_style }, m_p_vertical_scroll_bar{}, m_p_horizontal_scroll_bar{},
          m_child_observer_set{}, m_size_observer_set{}, m_focus_observer_set{}, m_paint_observer_set{},
          m_keyboard_observer_set{}, m_mouse_observer_set{}
        {
            m_focus_observer_set.got_focus().connect([this]() { this->m_focused = true; });
            m_focus_observer_set.lost_focus().connect([this]() { this->m_focused = false; });
            m_paint_observer_set.paint_background().connect(paint_background(*this));
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


        // virtual functions

        virtual const details_type& details_impl() const = 0;

        virtual details_type& details_impl() = 0;


        // functions

        std::unique_ptr<scroll_bar_type> create_vertical_scroll_bar()
        {
            if (m_scroll_bar_style != scroll_bar_style_type::vertical &&
                m_scroll_bar_style != scroll_bar_style_type::both)
            {
                return {};
            }

            return std::make_unique<scroll_bar_type>(details(), scroll_bar_type::style_type::vertical);
        }

        std::unique_ptr<scroll_bar_type> create_horizontal_scroll_bar()
        {
            if (m_scroll_bar_style != scroll_bar_style_type::horizontal &&
                m_scroll_bar_style != scroll_bar_style_type::both)
            {
                return {};
            }

            return std::make_unique<scroll_bar_type>(details(), scroll_bar_type::style_type::horizontal);
        }
    };
}


#endif

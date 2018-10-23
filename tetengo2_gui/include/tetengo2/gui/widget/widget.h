/*! \file
    \brief The definition of tetengo2::gui::widget::widget.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_WIDGET_H)
#define TETENGO2_GUI_WIDGET_WIDGET_H

#include <functional>
#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/message_handler.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/gui/cursor/cursor_base.h>
#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/canvas.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/drawing/widget_canvas.h>
#include <tetengo2/gui/message/child_observer_set.h>
#include <tetengo2/gui/message/focus_observer_set.h>
#include <tetengo2/gui/message/keyboard_observer_set.h>
#include <tetengo2/gui/message/mouse_observer_set.h>
#include <tetengo2/gui/message/paint_observer_set.h>
#include <tetengo2/gui/message/size_observer_set.h>
#include <tetengo2/gui/scroll_bar.h>
#include <tetengo2/gui/type_list.h>
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

        //! The canvas type.
        using canvas_type = gui::drawing::canvas;

        //! The widget canvas type.
        using widget_canvas_type = gui::drawing::widget_canvas;

        //! The background type.
        using background_type = gui::drawing::background;

        //! The font type.
        using font_type = gui::drawing::font;

        //! The cursor type.
        using cursor_type = gui::cursor::cursor_base;

        //! The scroll bar type.
        using scroll_bar_type = gui::scroll_bar;

        //! The scroll bar style type.
        enum class scroll_bar_style_type
        {
            none, //!< The widget has no scroll bar.
            vertical, //!< The widget has a vertical scroll bar.
            horizontal, //!< The widget has a horizontal scroll bar.
            both, //!< The widget has both vertiacal and horizontal scroll bars.
        };

        //! The message handler details type.
        using message_handler_details_type = detail::base::message_handler;

        //! The message handler map type.
        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;

        //! The child type.
        using child_type = widget;

        //! The child observer set type.
        using child_observer_set_type = gui::message::child_observer_set;

        //! The size observer set type.
        using size_observer_set_type = gui::message::size_observer_set;

        //! The focus observer set type.
        using focus_observer_set_type = gui::message::focus_observer_set;

        //! The paint observer set type.
        using paint_observer_set_type = gui::message::paint_observer_set;

        //! The keyboard observer set type.
        using keyboard_observer_set_type = gui::message::keyboard_observer_set;

        //! The mouse observer set type.
        using mouse_observer_set_type = gui::message::mouse_observer_set;


        // constructors and destructor

        /*!
            \brief Destroys the widget.
        */
        virtual ~widget();


        // functions

        /*!
            \brief Returns whether the widget has a parent.

            \retval true  When the widget has a parent.
            \retval false Otherwise.
        */
        bool has_parent() const;

        /*!
            \brief Returns the parent.

            \return The parent.

            \throw std::logic_error When the widget has no parent.
        */
        const widget& parent() const;

        /*!
            \brief Returns the parent.

            \return The parent.

            \throw std::logic_error When the widget has no parent.
        */
        widget& parent();

        /*!
            \brief Returns the root ancestor.

            \return The root ancestor.
        */
        const widget& root_ancestor() const;

        /*!
            \brief Returns the root ancestor.

            \return The root ancestor.
        */
        widget& root_ancestor();

        /*!
            \brief Returns the enabled status.

            \return The enabled status.
        */
        bool enabled() const;

        /*!
            \brief Sets an enabled status.

            \param enabled An enabled status.
        */
        void set_enabled(bool enabled);

        /*!
            \brief Returns the visible status.

            \return The visible status.
        */
        bool visible() const;

        /*!
            \brief Sets a visible status.

            \param visible A visible status.
        */
        void set_visible(bool visible);

        /*!
            \brief Returns the focused status.

            \return The focused status.
        */
        bool focused() const;

        /*!
            \brief Focuses on the widget.
        */
        void set_focus();

        /*!
            \brief Returns the position.

            \return The position.
        */
        position_type position() const;

        /*!
            \brief Sets a position.

            \param position A position.
        */
        void set_position(const position_type& position);

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        dimension_type dimension() const;

        /*!
            \brief Sets a dimension.

            \param dimension A dimension.
        */
        void set_dimension(const dimension_type& dimension);

        /*!
            \brief Returns the client dimension.

            \return The client dimension.
        */
        dimension_type client_dimension() const;

        /*!
            \brief Sets a client dimension.

            \param client_dimension A client dimension.

            \throw std::invalid_argument When either client_dimension.first or client_dimension.second is equal to 0.
        */
        void set_client_dimension(const dimension_type& client_dimension);

        /*!
            \brief Sets a position and a dimension.

            \param position  A position.
            \param dimension A dimension.
        */
        void set_position_and_dimension(const position_type& position, const dimension_type& dimension);

        /*!
            \brief Retuns the text.

            \return The text.
        */
        string_type text() const;

        /*!
            \brief Sets a text.

            \param text A text.
        */
        void set_text(string_type text);

        /*!
            \brief Returns the background.

            When the system default background is used, this function returns a nullptr.

            \return The pointer to the background.
        */
        const background_type* p_background() const;

        /*!
            \brief Sets a background.

            When p_background is nullptr, the system default background is used.

            \param p_background A unique pointer to a background.
        */
        void set_background(std::unique_ptr<background_type> p_background);

        /*!
            \brief Retuns the font.

            \return The font.
        */
        font_type font() const;

        /*!
            \brief Sets a font.

            \param font A font.
        */
        void set_font(const font_type& font);

        /*!
            \brief Returns the cursor.

            \return The pointer to the cursor.
        */
        const cursor_type* p_cursor() const;

        /*!
            \brief Sets a cursor.

            \param p_cursor A unique pointer to a cursor.
        */
        void set_cursor(std::unique_ptr<cursor_type> p_cursor);

        /*!
            \brief Checks whether the widget has a vertical scroll bar.

            \retval true  The widget has a vertical scroll bar.
        */
        bool has_vertical_scroll_bar() const;

        /*!
            \brief Returns the vertical scroll bar.

            \return The vertical scroll bar.

            \throw std::logic_error When the widget has no vertical scroll bar.
        */
        const scroll_bar_type& vertical_scroll_bar() const;

        /*!
            \brief Returns the vertical scroll bar.

            \return The vertical scroll bar.

            \throw std::logic_error When the widget has no vertical scroll bar.
        */
        scroll_bar_type& vertical_scroll_bar();

        /*!
            \brief Checks whether the widget has a horizontal scroll bar.

            \retval true  The widget has a horizontal scroll bar.
        */
        bool has_horizontal_scroll_bar() const;

        /*!
            \brief Returns the horizontal scroll bar.

            \return The horizontal scroll bar.

            \throw std::logic_error When the widget has no horizontal scroll bar.
        */
        const scroll_bar_type& horizontal_scroll_bar() const;

        /*!
            \brief Returns the horizontal scroll bar.

            \return The horizontal scroll bar.

            \throw std::logic_error When the widget has no horizontal scroll bar.
        */
        scroll_bar_type& horizontal_scroll_bar();

        /*!
            \brief Returns the constant children.

            \return The children.
        */
        std::vector<std::reference_wrapper<const child_type>> children() const;

        /*!
            \brief Returns the children.

            \return The children.
        */
        std::vector<std::reference_wrapper<child_type>> children();

        /*!
            \brief Repaints the widget.

            \param immediately Set true to request an immediate repaint.
        */
        void repaint(bool immediately = false) const;

        /*!
            \brief Repaints the widget partially.

            \param position  The position of a region to repaint.
            \param dimension The dimension of a region to repaint.
        */
        void repaint_partially(const position_type& position, const dimension_type& dimension) const;

        /*!
            \brief Creates a canvas.

            \return The unique pointer to a canvas.
        */
        std::unique_ptr<canvas_type> create_canvas() const;

        /*!
            \brief Clicks this widget.
        */
        void click() const;

        /*!
            \brief Clicks this widget.
        */
        void click();

        /*!
            \brief Returns the child observer set.

            \return The child observer set.
        */
        const child_observer_set_type& child_observer_set() const;

        /*!
            \brief Returns the child observer set.

            \return The child observer set.
        */
        child_observer_set_type& child_observer_set();

        /*!
            \brief Returns the size observer set.

            \return The size observer set.
        */
        const size_observer_set_type& size_observer_set() const;

        /*!
            \brief Returns the size observer set.

            \return The size observer set.
        */
        size_observer_set_type& size_observer_set();

        /*!
            \brief Returns the focus observer set.

            \return The focus observer set.
        */
        const focus_observer_set_type& focus_observer_set() const;

        /*!
            \brief Returns the focus observer set.

            \return The focus observer set.
        */
        focus_observer_set_type& focus_observer_set();

        /*!
            \brief Returns the paint observer set.

            \return The paint observer set.
        */
        const paint_observer_set_type& paint_observer_set() const;

        /*!
            \brief Returns the paint observer set.

            \return The paint observer set.
        */
        paint_observer_set_type& paint_observer_set();

        /*!
           \brief Returns the keyboard observer set.

           \return The keyboard observer set.
       */
        const keyboard_observer_set_type& keyboard_observer_set() const;

        /*!
            \brief Returns the keyboard observer set.

            \return The keyboard observer set.
        */
        keyboard_observer_set_type& keyboard_observer_set();

        /*!
             \brief Returns the mouse observer set.

             \return The mouse observer set.
         */
        const mouse_observer_set_type& mouse_observer_set() const;

        /*!
            \brief Returns the mouse observer set.

            \return The mouse observer set.
        */
        mouse_observer_set_type& mouse_observer_set();

        /*!
            \brief Returns wether the widget is destroyed.

            \retval true  When the widget is destroyed.
            \retval false Otherwise.
        */
        bool destroyed() const;

        /*!
            \brief Sets the status of the widget that it is already destroyed.
        */
        void set_destroyed();

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.

            \throw std::runtime_error When the widget is already destroyed.
        */
        const details_type& details() const;

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.

            \throw std::runtime_error When the widget is already destroyed.
        */
        details_type& details();

        /*!
            \brief Returns the message handler map.

            \return The message handler map.
        */
        const message_handler_map_type& message_handler_map() const;


    protected:
        // static functions

        /*!
            \brief Initializes the widget.

            This function must be called in the constructor and only in the constructor.

            \param p_widget A pointer to a widget.
        */
        static void initialize(widget* p_widget);

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        static const detail::base::widget& widget_details();


        // constructors and destructor

        /*!
            \brief Creates a widget.

            \param scroll_bar_style    A scroll bar style.
            \param message_handler_map A message handler map.
        */
        widget(const scroll_bar_style_type scroll_bar_style, message_handler_map_type&& message_handler_map);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual const details_type& details_impl() const = 0;

        virtual details_type& details_impl() = 0;
    };
}


#endif

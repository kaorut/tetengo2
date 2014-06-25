/*! \file
    \brief The definition of tetengo2::gui::widget::custom_control.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_CUSTOMCONTROL_H)
#define TETENGO2_GUI_WIDGET_CUSTOMCONTROL_H

#include <cassert>
#include <memory>
#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/gui/measure.h>
#include <tetengo2/gui/mouse_capture.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/utility.h>


namespace tetengo2 { namespace gui { namespace widget
{
    template <typename CustomControl>
    class inner_item;


    /*!
        \brief The class template for a custom control.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam DrawingDetails        A detail implementation type of drawing.
        \tparam IconDetails           A detail implementation type of an icon.
        \tparam AlertDetails          A detail implementation type of an alert.
        \tparam CursorDetails         A detail implementation type of a cursor.
        \tparam ScrollDetails         A detail implementation type of a scroll.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
        \tparam VirtualKeyDetails     A detail implementation type of a virtual key.
        \tparam MouseCaptureDetails   A detail implementation type of a mouse capture.
    */
    template <
        typename Traits,
        typename WidgetDetails,
        typename DrawingDetails,
        typename IconDetails,
        typename AlertDetails,
        typename CursorDetails,
        typename ScrollDetails,
        typename MessageHandlerDetails,
        typename VirtualKeyDetails,
        typename MouseCaptureDetails
    >
    class custom_control :
        public control<
            typename Traits::base_type,
            WidgetDetails,
            DrawingDetails,
            IconDetails,
            AlertDetails,
            CursorDetails,
            ScrollDetails,
            MessageHandlerDetails,
            VirtualKeyDetails
        >
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The detail implementation type of a widget.
        using widget_details_type = WidgetDetails;

        //! The drawing details type.
        using drawing_details_type = DrawingDetails;

        //! The icon details type.
        using icon_details_type = IconDetails;

        //! The alert details type.
        using alert_details_type = AlertDetails;

        //! The cursor details type.
        using cursor_details_type = CursorDetails;

        //! The scroll details type.
        using scroll_details_type = ScrollDetails;

        //! The message handler details type.
        using message_handler_details_type = MessageHandlerDetails;

        //! The virtual key details type.
        using virtual_key_details_type = VirtualKeyDetails;

        //! The mouse capture details type.
        using mouse_capture_details_type = MouseCaptureDetails;

        //! The base type.
        using base_type =
            control<
                typename traits_type::base_type,
                widget_details_type,
                drawing_details_type,
                icon_details_type,
                alert_details_type,
                cursor_details_type,
                scroll_details_type,
                message_handler_details_type,
                virtual_key_details_type
            >;

        //! The widget type.
        using widget_type = typename base_type::base_type;

        //! The widget canvas type.
        using widget_canvas_type = typename base_type::widget_canvas_type;

        //! The canvas type.
        using canvas_type = typename base_type::canvas_type;

        //! The position type.
        using position_type = typename base_type::position_type;

        //! The dimension type.
        using dimension_type = typename base_type::dimension_type;

        //! The string type.
        using string_type = typename base_type::string_type;

        //! The scroll bar type.
        using scroll_bar_type = typename base_type::scroll_bar_type;

        //! The scroll bar style type.
        using scroll_bar_style_type = typename base_type::scroll_bar_style_type;

        //! The mouse observer set type.
        using mouse_observer_set_type = typename base_type::mouse_observer_set_type;

        //! The mouse button type.
        using mouse_button_type = typename mouse_observer_set_type::mouse_button_type;

        //! The mouse capture type.
        using mouse_capture_type = gui::mouse_capture<widget_type, mouse_button_type, mouse_capture_details_type>;

        //! The detail implementation type.
        using details_type = typename widget_details_type::widget_details_type;

        //! The inner item type.
        using inner_item_type = inner_item<custom_control>;


        // constructors and destructor

        /*!
            \brief Creates a custom control.

            \param parent           A parent widget.
            \param border           Set true to add border lines.
            \param scroll_bar_style A scroll bar style type.
        */
        custom_control(widget_type& parent, const bool border, const scroll_bar_style_type scroll_bar_style)
        :
#if BOOST_COMP_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            scroll_bar_style,
            message_handler_details_type::make_custom_control_message_handler_map(*this, message_handler_map_type{}),
            widget_details_type::create_custom_control(parent, border, scroll_bar_style)
        ),
#if BOOST_COMP_MSVC
#   pragma warning(pop)
#endif
        m_p_mouse_capture(),
        m_p_mouse_captured_item(nullptr)
        {
            this->initialize(this);
        }

        /*!
            \brief Destroys the custom control.
        */
        virtual ~custom_control()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // functions

        /*!
            \brief Checks whether the mouse is captured.

            When p_inner_item is nullptr, it returns true if any item is captured.

            \param p_inner_item A pointer to an inner item.

            \retval true  When the mouse is captured by the inner item.
            \retval false Otherwise.
        */
        bool mouse_captured(const inner_item_type* const p_inner_item)
        const
        {
            return static_cast<bool>(m_p_mouse_capture) && (!p_inner_item || m_p_mouse_captured_item == p_inner_item);
        }

        /*!
            \brief Checks whether the mouse is captured with the specified button.

            When p_inner_item is nullptr, it returns true if any item is captured.

            \param mouse_button A mouse button.
            \param p_inner_item A pointer to an inner item.

            \retval true  When the mouse is captured by the inner item.
            \retval false Otherwise.
        */
        bool mouse_captured(const mouse_button_type mouse_button, const inner_item_type* const p_inner_item)
        const
        {
            return
                static_cast<bool>(m_p_mouse_capture) &&
                m_p_mouse_capture->button() == mouse_button &&
                (!p_inner_item || m_p_mouse_captured_item == p_inner_item);
        }

        /*!
            \brief Sets a mouse capture to the specified inner item.
            
            \param mouse_button A mouse button.
            \param p_inner_item A pointer to an inner item.

            \retval true  When a mouse capture is set to the specified inner item.
            \retval false Otherwise.
        */
        bool set_mouse_capture(const mouse_button_type mouse_button, const inner_item_type* const p_inner_item)
        {
            if (m_p_mouse_capture)
                return false;

            m_p_mouse_capture = stdalt::make_unique<mouse_capture_type>(*this, mouse_button);
            m_p_mouse_captured_item = p_inner_item;

            return true;
        }

        /*!
            \brief Releases the mouse capture.
        */
        void release_mouse_capture()
        {
            m_p_mouse_captured_item = nullptr;
            m_p_mouse_capture.reset();
        }


    private:
        // types

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // variables

        std::unique_ptr<mouse_capture_type> m_p_mouse_capture;

        const inner_item_type* m_p_mouse_captured_item;


    };


    /*!
        \brief The class template for a inner item.

        \tparam CustomControl A custom control type.
    */
    template <typename CustomControl>
    class inner_item : boost::noncopyable
    {
    public:
        // types

        //! The custom control type.
        using custom_control_type = CustomControl;

        //! The mouse button type.
        using mouse_button_type = typename custom_control_type::mouse_button_type;

        //! The postion type.
        using position_type = typename custom_control_type::position_type;

        //! The left type.
        using left_type = typename gui::position<position_type>::left_type;

        //! The top type.
        using top_type = typename gui::position<position_type>::top_type;

        //! The postion type.
        using dimension_type = typename custom_control_type::dimension_type;

        //! The canvas type.
        using canvas_type = typename custom_control_type::canvas_type;


        // constructors and destructors

        /*!
            \brief Destroys the inner item.
        */
        virtual ~inner_item()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // functions

        /*!
            \brief Returns the position.

            \return The position.
        */
        const position_type& position()
        const
        {
            return m_position;
        }

        /*!
            \brief Sets a position.

            \param position A position.
        */
        void set_position(position_type position)
        {
            m_position = std::move(position);
        }

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        const dimension_type& dimension()
        const
        {
            return m_dimension;
        }

        /*!
            \brief Sets a dimension.

            \param dimension A dimension.
        */
        void set_dimension(dimension_type dimension)
        {
            m_dimension = std::move(dimension);
        }

        /*!
            \brief Called when the inner item is resized.
        */
        void resized()
        {
            resized_impl();
        }

        /*!
            \brief Called to repaint the inner item.

            \param canvas A canvas.
        */
        void paint(canvas_type& canvas)
        const
        {
            paint_impl(canvas);
        }

        /*!
            \brief Called when the mouse button is pressed.

            \param mouse_button    A mouse_button_type.
            \param cursor_position A mouse cursor position.
        */
        void mouse_pressed(const mouse_button_type mouse_button, const position_type& cursor_position)
        {
            if (!inside(cursor_position))
                return;

            if (!this->parent().set_mouse_capture(mouse_button, this))
                return;

            mouse_pressed_impl(cursor_position);
        }

        /*!
            \brief Called when the mouse button is released.

            \param mouse_button    A mouse_button_type.
            \param cursor_position A mouse cursor position.
        */
        void mouse_released(const mouse_button_type mouse_button, const position_type& cursor_position)
        {
            if (!this->parent().mouse_captured(mouse_button, this))
                return;

            mouse_released_impl(cursor_position);

            this->parent().release_mouse_capture();
        }

        /*!
            \brief Called when the mouse cursor is moved.

            \param cursor_position A mouse cursor position.
        */
        void mouse_moved(const position_type& cursor_position)
        {

            if (this->parent().mouse_captured(this) || inside(cursor_position))
            {
                mouse_moved_impl(cursor_position);
                if (!m_mouse_inside)
                {
                    mouse_entered_impl();
                    m_mouse_inside = true;
                }
            }
            else
            {
                if (m_mouse_inside)
                {
                    mouse_left_impl();
                    m_mouse_inside = false;
                }
            }
        }


    protected:
        // constructors

        /*!
            \brief Creates an innter item.

            \param parent    A parent.
            \param position  A position.
            \param dimension A dimension.
        */
        inner_item(custom_control_type& parent, position_type&& position, dimension_type&& dimension)
        :
        m_parent(parent),
        m_position(std::move(position)),
        m_dimension(std::move(dimension)),
        m_mouse_inside(false)
        {}


        // functions

        /*!
            \brief Returns the parent.

            \return The parent.
        */
        const custom_control_type& parent()
        const
        {
            return m_parent;
        }

        /*!
            \brief Returns the parent.

            \return The parent.
        */
        custom_control_type& parent()
        {
            return m_parent;
        }

        /*!
            \brief Casts the parent to the specified type.

            \tparam T A type.

            \return The parent as the specified type.
        */
        template <typename T>
        const T& parent_to()
        const
        {
            assert(dynamic_cast<const T*>(&m_parent));
            return dynamic_cast<const T&>(m_parent);
        }

        /*!
            \brief Casts the parent to the specified type.

            \tparam T A type.

            \return The parent as the specified type.
        */
        template <typename T>
        T& parent_to()
        {
            assert(dynamic_cast<T*>(&m_parent));
            return dynamic_cast<T&>(m_parent);
        }

        /*!
            \brief Checkes whether the position is inside the inner item.

            \param position A position.

            \retval true  When the position is inside the inner item.
            \retval false Otherwise.
        */
        bool inside(const position_type& position)
        const
        {
            const auto& left = gui::position<position_type>::left(m_position);
            const auto right = left + left_type::from(gui::dimension<dimension_type>::width(m_dimension));
            const auto& top = gui::position<position_type>::top(m_position);
            const auto bottom = top + top_type::from(gui::dimension<dimension_type>::height(m_dimension));

            const auto& cursor_left = gui::position<position_type>::left(position);
            const auto& cursor_top = gui::position<position_type>::top(position);

            return (left <= cursor_left && cursor_left < right) && (top <= cursor_top && cursor_top < bottom);
        }


    private:
        // variables

        custom_control_type& m_parent;

        position_type m_position;

        dimension_type m_dimension;

        bool m_mouse_inside;


        // virtual functions

        virtual void resized_impl()
        {}

        virtual void paint_impl(canvas_type& canvas)
        const
        {
            suppress_unused_variable_warning(canvas);
        }

        virtual void mouse_pressed_impl(const position_type& cursor_position)
        {
            suppress_unused_variable_warning(cursor_position);
        }

        virtual void mouse_released_impl(const position_type& cursor_position)
        {
            suppress_unused_variable_warning(cursor_position);
        }

        virtual void mouse_moved_impl(const position_type& cursor_position)
        {
            suppress_unused_variable_warning(cursor_position);
        }

        virtual void mouse_entered_impl()
        {}

        virtual void mouse_left_impl()
        {}


    };


}}}


#endif
/*! \file
    \brief The definition of tetengo2::gui::widget::custom_control.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_CUSTOMCONTROL_H)
#define TETENGO2_GUI_WIDGET_CUSTOMCONTROL_H

//#include <utility>

//#include <boost/noncopyable.hpp>

#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.widget.control.h"
#include "tetengo2.stdalt.h"
#include "tetengo2.utility.h"


namespace tetengo2 { namespace gui { namespace widget
{
    template <typename CustomControl>
    class inner_item;


    /*!
        \brief The class template for a custom control.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class custom_control : public control<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The mouse capture type.
        typedef typename traits_type::mouse_capture_type mouse_capture_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The base type.
        typedef control<typename traits_type::base_type, widget_details_type, message_handler_details_type> base_type;

        //! The widget type.
        typedef typename base_type::base_type widget_type;

        //! The widget canvas type.
        typedef typename base_type::widget_canvas_type widget_canvas_type;

        //! The canvas type.
        typedef typename base_type::canvas_type canvas_type;

        //! The position type.
        typedef typename base_type::position_type position_type;

        //! The dimension type.
        typedef typename base_type::dimension_type dimension_type;

        //! The string type.
        typedef typename base_type::string_type string_type;

        //! The scroll bar type.
        typedef typename base_type::scroll_bar_type scroll_bar_type;

        //! The scroll bar style type.
        typedef typename base_type::scroll_bar_style_type scroll_bar_style_type;

        //! The mouse observer set type.
        typedef typename base_type::mouse_observer_set_type mouse_observer_set_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;

        //! The inner item type.
        typedef inner_item<custom_control> inner_item_type;


        // constructors and destructor

        /*!
            \brief Creates a custom control.

            \param parent           A parent widget.
            \param border           Set true to add border lines.
            \param scroll_bar_style A scroll bar style type.
        */
        custom_control(widget_type& parent, const bool border, const scroll_bar_style_type scroll_bar_style)
        :
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            scroll_bar_style,
            message_handler_details_type::make_custom_control_message_handler_map(
                *this, message_handler_map_type()
            ),
            widget_details_type::create_custom_control(parent, border, scroll_bar_style)
        ),
#if defined(_MSC_VER)
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
        TETENGO2_STDALT_NOEXCEPT
        {}


        // functions

        /*!
            \brief Checks whether the mouse is captured.

            \param p_inner_item A pointer to an inner item.

            \retval true  When the mouse is captured by the inner item.
            \retval false Otherwise.
        */
        bool mouse_captured(const inner_item_type* const p_inner_item)
        const
        {
            return static_cast<bool>(m_p_mouse_capture) && m_p_mouse_captured_item == p_inner_item;
        }

        /*!
            \brief Sets a mouse capture to the specified inner item.
            
            \param p_inner_item A pointer to an inner item.

            \retval true  When a mouse capture is set to the specified inner item.
            \retval false Otherwise.
        */
        bool set_mouse_capture(const inner_item_type* const p_inner_item)
        {
            if (m_p_mouse_capture)
                return false;

            m_p_mouse_capture = stdalt::make_unique<mouse_capture_type>(*this);
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

        typedef typename message_handler_details_type::message_handler_map_type message_handler_map_type;


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
        typedef CustomControl custom_control_type;

        //! The postion type.
        typedef typename custom_control_type::position_type position_type;

        //! The left type.
        typedef typename gui::position<position_type>::left_type left_type;

        //! The top type.
        typedef typename gui::position<position_type>::top_type top_type;

        //! The postion type.
        typedef typename custom_control_type::dimension_type dimension_type;

        //! The width type.
        typedef typename gui::dimension<dimension_type>::width_type width_type;

        //! The height type.
        typedef typename gui::dimension<dimension_type>::height_type height_type;

        //! The canvas type.
        typedef typename custom_control_type::canvas_type canvas_type;


        // constructors and destructors

        /*!
            \brief Destroys the inner item.
        */
        virtual ~inner_item()
        TETENGO2_STDALT_NOEXCEPT
        {}


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

            \param cursor_position A mouse cursor position.
        */
        void mouse_pressed(const position_type& cursor_position)
        {
            if (!inside(cursor_position))
                return;

            if (!this->parent().set_mouse_capture(this))
                return;

            mouse_pressed_impl(cursor_position);
        }

        /*!
            \brief Called when the mouse button is released.

            \param cursor_position A mouse cursor position.
        */
        void mouse_released(const position_type& cursor_position)
        {
            if (!this->parent().mouse_captured(this))
                return;

            this->parent().release_mouse_capture();

            mouse_released_impl(cursor_position);
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

            \param T A type.

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

            \param T A type.

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

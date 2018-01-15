/*! \file
    \brief The definition of tetengo2::gui::widget::custom_control.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_CUSTOMCONTROL_H)
#define TETENGO2_GUI_WIDGET_CUSTOMCONTROL_H

#include <cassert>
#include <memory>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/gui/mouse_capture.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace widget
{
    template <typename CustomControl>
    class inner_item;


    /*!
        \brief The class template for a custom control.

        \tparam Traits              A traits type.
        \tparam DetailsTraits       A detail implementation type traits.
        \tparam MouseCaptureDetails A detail implementation type of a mouse capture.
    */
    template <typename Traits, typename DetailsTraits, typename MouseCaptureDetails>
    class custom_control : public control<Traits, DetailsTraits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The widget details type.
        using widget_details_type = typename details_traits_type::widget_details_type;

        //! The message handler details type.
        using message_handler_details_type = typename details_traits_type::message_handler_details_type;

        //! The mouse capture details type.
        using mouse_capture_details_type = MouseCaptureDetails;

        //! The base type.
        using base_type = control<traits_type, details_traits_type>;

        //! The widget type.
        using widget_type = typename base_type::base_type;

        //! The canvas type.
        using canvas_type = typename base_type::canvas_type;

        //! The position type.
        using position_type = typename base_type::position_type;

        //! The dimension type.
        using dimension_type = typename base_type::dimension_type;

        //! The scroll bar style type.
        using scroll_bar_style_type = typename base_type::scroll_bar_style_type;

        //! The mouse observer set type.
        using mouse_observer_set_type = typename base_type::mouse_observer_set_type;

        //! The mouse button type.
        using mouse_button_type = typename mouse_observer_set_type::mouse_button_type;

        //! The mouse capture type.
        using mouse_capture_type = gui::mouse_capture<widget_type, mouse_button_type, mouse_capture_details_type>;

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
            base_type::initialize(this);

            parent.child_observer_set().created()(*this);
        }

        /*!
            \brief Destroys the custom control.
        */
        virtual ~custom_control()
        noexcept
        {
            try
            {
                if (this->has_parent())
                    this->parent().child_observer_set().destroying()(*this);
            }
            catch (...)
            {}
        }


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
    class inner_item : private boost::noncopyable
    {
    public:
        // types

        //! The custom control type.
        using custom_control_type = CustomControl;

        //! The mouse button type.
        using mouse_button_type = typename custom_control_type::mouse_button_type;

        //! The postion type.
        using position_type = typename custom_control_type::position_type;

        //! The position unit type.
        using position_unit_type = typename position_type::unit_type;

        //! The dimension type.
        using dimension_type = typename custom_control_type::dimension_type;

        //! The canvas type.
        using canvas_type = typename custom_control_type::canvas_type;


        // constructors and destructors

        /*!
            \brief Destroys the inner item.
        */
        virtual ~inner_item()
        = default;


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
            const auto& left = m_position.left();
            const auto right = left + position_unit_type::from(m_dimension.width());
            const auto& top = m_position.top();
            const auto bottom = top + position_unit_type::from(m_dimension.height());

            const auto& cursor_left = position.left();
            const auto& cursor_top = position.top();

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
            boost::ignore_unused(canvas);
        }

        virtual void mouse_pressed_impl(const position_type& cursor_position)
        {
            boost::ignore_unused(cursor_position);
        }

        virtual void mouse_released_impl(const position_type& cursor_position)
        {
            boost::ignore_unused(cursor_position);
        }

        virtual void mouse_moved_impl(const position_type& cursor_position)
        {
            boost::ignore_unused(cursor_position);
        }

        virtual void mouse_entered_impl()
        {}

        virtual void mouse_left_impl()
        {}


    };


}}}


#endif

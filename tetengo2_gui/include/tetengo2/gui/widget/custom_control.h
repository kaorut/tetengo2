/*! \file
    \brief The definition of tetengo2::gui::widget::custom_control.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_CUSTOMCONTROL_H)
#define TETENGO2_GUI_WIDGET_CUSTOMCONTROL_H

#include <cassert>
#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    class inner_item;


    /*!
        \brief The class for a custom control.
    */
    class custom_control : public control
    {
    public:
        // types

        //! The mouse button type.
        using mouse_button_type = typename mouse_observer_set_type::mouse_button_type;


        // constructors and destructor

        /*!
            \brief Destroys the custom control.
        */
        virtual ~custom_control() noexcept;


        // functions

        /*!
            \brief Checks whether the mouse is captured.

            When p_inner_item is nullptr, it returns true if any item is captured.

            \param p_inner_item A pointer to an inner item.

            \retval true  When the mouse is captured by the inner item.
            \retval false Otherwise.
        */
        bool mouse_captured(const inner_item* p_inner_item) const;

        /*!
            \brief Checks whether the mouse is captured with the specified button.

            When p_inner_item is nullptr, it returns true if any item is captured.

            \param mouse_button A mouse button.
            \param p_inner_item A pointer to an inner item.

            \retval true  When the mouse is captured by the inner item.
            \retval false Otherwise.
        */
        bool mouse_captured(mouse_button_type mouse_button, const inner_item* p_inner_item) const;

        /*!
            \brief Sets a mouse capture to the specified inner item.

            \param mouse_button A mouse button.
            \param p_inner_item A pointer to an inner item.

            \retval true  When a mouse capture is set to the specified inner item.
            \retval false Otherwise.
        */
        bool set_mouse_capture(mouse_button_type mouse_button, const inner_item* p_inner_item);

        /*!
            \brief Releases the mouse capture.
        */
        void release_mouse_capture();


    protected:
        // constructors

        /*!
            \brief Creates a custom control.

            \param parent           A parent widget.
            \param border           Set true to add border lines.
            \param scroll_bar_style A scroll bar style type.
        */
        custom_control(widget& parent, bool border, scroll_bar_style_type scroll_bar_style);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };


    /*!
        \brief The class for a inner item.
    */
    class inner_item : private boost::noncopyable
    {
    public:
        // types

        //! The mouse button type.
        using mouse_button_type = custom_control::mouse_button_type;

        //! The postion type.
        using position_type = custom_control::position_type;

        //! The dimension type.
        using dimension_type = custom_control::dimension_type;

        //! The canvas type.
        using canvas_type = custom_control::canvas_type;


        // constructors and destructors

        /*!
            \brief Destroys the inner item.
        */
        virtual ~inner_item();


        // functions

        /*!
            \brief Returns the position.

            \return The position.
        */
        const position_type& position() const;

        /*!
            \brief Sets a position.

            \param position A position.
        */
        void set_position(position_type position);

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        const dimension_type& dimension() const;

        /*!
            \brief Sets a dimension.

            \param dimension A dimension.
        */
        void set_dimension(dimension_type dimension);

        /*!
            \brief Called when the inner item is resized.
        */
        void resized();

        /*!
            \brief Called to repaint the inner item.

            \param canvas A canvas.
        */
        void paint(canvas_type& canvas) const;

        /*!
            \brief Called when the mouse button is pressed.

            \param mouse_button    A mouse_button_type.
            \param cursor_position A mouse cursor position.
        */
        void mouse_pressed(mouse_button_type mouse_button, const position_type& cursor_position);

        /*!
            \brief Called when the mouse button is released.

            \param mouse_button    A mouse_button_type.
            \param cursor_position A mouse cursor position.
        */
        void mouse_released(mouse_button_type mouse_button, const position_type& cursor_position);

        /*!
            \brief Called when the mouse cursor is moved.

            \param cursor_position A mouse cursor position.
        */
        void mouse_moved(const position_type& cursor_position);


    protected:
        // constructors

        /*!
            \brief Creates an innter item.

            \param parent    A parent.
            \param position  A position.
            \param dimension A dimension.
        */
        inner_item(custom_control& parent, position_type&& position, dimension_type&& dimension);


        // functions

        /*!
            \brief Returns the parent.

            \return The parent.
        */
        const custom_control& parent() const;

        /*!
            \brief Returns the parent.

            \return The parent.
        */
        custom_control& parent();

        /*!
            \brief Casts the parent to the specified type.

            \tparam T A type.

            \return The parent as the specified type.
        */
        template <typename T>
        const T& parent_as() const
        {
            assert(dynamic_cast<const T*>(&parent()));
            return dynamic_cast<const T&>(parent());
        }

        /*!
            \brief Casts the parent to the specified type.

            \tparam T A type.

            \return The parent as the specified type.
        */
        template <typename T>
        T& parent_as()
        {
            assert(dynamic_cast<T*>(&parent()));
            return dynamic_cast<T&>(parent());
        }

        /*!
            \brief Checkes whether the position is inside the inner item.

            \param position A position.

            \retval true  When the position is inside the inner item.
            \retval false Otherwise.
        */
        bool inside(const position_type& position) const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void resized_impl();

        virtual void paint_impl(canvas_type& canvas) const;

        virtual void mouse_pressed_impl(const position_type& cursor_position);

        virtual void mouse_released_impl(const position_type& cursor_position);

        virtual void mouse_moved_impl(const position_type& cursor_position);

        virtual void mouse_entered_impl();

        virtual void mouse_left_impl();
    };
}


#endif

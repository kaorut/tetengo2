/*! \file
    \brief The definition of tetengo2::gui::widget::picture_box.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_PICTUREBOX_H)
#define TETENGO2_GUI_WIDGET_PICTUREBOX_H

//#include <memory>

#include "tetengo2.cpp11.h"
#include "tetengo2.gui.widget.control.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a picture box.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class picture_box : public control<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The fast widget canvas type.
        typedef typename Traits::fast_widget_canvas_type fast_widget_canvas_type;

        //! The fast canvas type.
        typedef typename Traits::fast_canvas_type fast_canvas_type;

        //! The fast paint observer set type.
        typedef typename traits_type::fast_paint_observer_set_type fast_paint_observer_set_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The base type.
        typedef control<typename traits_type::base_type, widget_details_type, message_handler_details_type> base_type;

        //! The widget type.
        typedef typename base_type::base_type widget_type;

        //! The position type.
        typedef typename base_type::position_type position_type;

        //! The dimension type.
        typedef typename base_type::dimension_type dimension_type;

        //! The system cursor type.
        typedef typename base_type::system_cursor_type system_cursor_type;

        //! The cursor type.
        typedef typename base_type::cursor_type cursor_type;

        //! The scroll bar type.
        typedef typename base_type::scroll_bar_type scroll_bar_type;

        //! The scroll bar style type.
        typedef typename base_type::scroll_bar_style_type scroll_bar_style_type;

        //! The mouse observer set type.
        typedef typename base_type::mouse_observer_set_type mouse_observer_set_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef typename widget_details_type::widget_details_ptr_type details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates a picture box.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style type.
        */
        picture_box(widget_type& parent, const typename scroll_bar_style_type::enum_t scroll_bar_style)
        :
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            scroll_bar_style,
            message_handler_details_type::make_picture_box_message_handler_map(*this, message_handler_map_type()),
            widget_details_type::create_picture_box(parent, scroll_bar_style)
        ),
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
        m_fast_paint_observer_set()
        {
            this->initialize(this);
            this->paint_observer_set().paint_background().connect(paint_background());
        }

        /*!
            \brief Destroys the picture box.
        */
        virtual ~picture_box()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Creates a fast canvas.

            \return The unique pointer to a fast canvas.
        */
        std::unique_ptr<fast_canvas_type> create_fast_canvas()
        const
        {
            return make_unique<fast_widget_canvas_type>(*this->details());
        }

        /*!
            \brief Returns the fast paint observer set.

            \return The fast paint observer set.
        */
        const fast_paint_observer_set_type& fast_paint_observer_set()
        const
        {
            return m_fast_paint_observer_set;
        }

        /*!
            \brief Returns the fast paint observer set.

            \return The fast paint observer set.
        */
        fast_paint_observer_set_type& fast_paint_observer_set()
        {
            return m_fast_paint_observer_set;
        }


    private:
        // types

        typedef typename message_handler_details_type::message_handler_map_type message_handler_map_type;

        struct paint_background
        {
            bool operator()(typename base_type::canvas_type& canvas)
            const
            {
                return true;
            }

        };


        // variables

        fast_paint_observer_set_type m_fast_paint_observer_set;


    };


}}}


#endif

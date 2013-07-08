/*! \file
    \brief The definition of tetengo2::gui::widget::custom_control.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_CUSTOMCONTROL_H)
#define TETENGO2_GUI_WIDGET_CUSTOMCONTROL_H

#include "tetengo2.cpp11.h"
#include "tetengo2.gui.widget.control.h"
#include "tetengo2.utility.h"


namespace tetengo2 { namespace gui { namespace widget
{
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

        //! The scroll bar style type.
        typedef typename base_type::scroll_bar_style_type scroll_bar_style_type;

        //! The mouse observer set type.
        typedef typename base_type::mouse_observer_set_type mouse_observer_set_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;


        // constructors and destructor

        /*!
            \brief Creates a custom control.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style type.
        */
        custom_control(widget_type& parent, const scroll_bar_style_type scroll_bar_style)
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
            widget_details_type::create_custom_control(parent, scroll_bar_style)
        )
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
        {
            this->initialize(this);
        }

        /*!
            \brief Destroys the custom control.
        */
        virtual ~custom_control()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef typename message_handler_details_type::message_handler_map_type message_handler_map_type;


    };


}}}


#endif

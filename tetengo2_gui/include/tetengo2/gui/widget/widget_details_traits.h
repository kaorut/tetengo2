/*! \file
    \brief The definition of tetengo2::gui::widget::widget_details_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_WIDGETDETAILSTRAITS_H)
#define TETENGO2_GUI_WIDGET_WIDGETDETAILSTRAITS_H


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The traits class template for detail implementation of a widget.

        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam DrawingDetails        A detail implementation type of drawing.
        \tparam IconDetails           A detail implementation type of an icon.
        \tparam AlertDetails          A detail implementation type of an alert.
        \tparam CursorDetails         A detail implementation type of a cursor.
        \tparam ScrollDetails         A detail implementation type of a scroll.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
        \tparam VirtualKeyDetails     A detail implementation type of a virtual key.
   */
    template <
        typename WidgetDetails,
        typename DrawingDetails,
        typename IconDetails,
        typename AlertDetails,
        typename CursorDetails,
        typename ScrollDetails,
        typename MessageHandlerDetails,
        typename VirtualKeyDetails
    >
    struct widget_details_traits
    {
        // types

        //! The widget details type.
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


    };


}}}


#endif

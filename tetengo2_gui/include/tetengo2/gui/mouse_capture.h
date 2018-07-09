/*! \file
    \brief The definition of tetengo2::gui::mouse_capture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MOUSECAPTURE_H)
#define TETENGO2_GUI_MOUSECAPTURE_H

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/message/mouse_observer_set.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui {
    /*!
        \brief The class template for a mouse capture.

        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam DrawingDetails        A detail implementation type of drawing.
        \tparam ScrollDetails         A detail implementation type of a scroll.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
        \tparam MouseCaptureDetails   A detail implementation type of a mouse capture.
    */
    template <
        typename WidgetDetails,
        typename DrawingDetails,
        typename ScrollDetails,
        typename MessageHandlerDetails,
        typename MouseCaptureDetails>
    class mouse_capture : private boost::noncopyable
    {
    public:
        // types

        //! The mouse capture details type.
        using mouse_capture_details_type = MouseCaptureDetails;

        //! The widget type.
        using widget_type = widget::widget;

        //! The mouse button type.
        using mouse_button_type = message::mouse_observer_set::mouse_button_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse capture.

            \param widget A widget.
            \param button A button.
        */
        mouse_capture(const widget_type& widget, const mouse_button_type button)
        : m_mouse_capture_details{ widget }, m_button{ button }
        {}


        // functions

        /*!
            \brief Returns the button.

            \return The button.
        */
        mouse_button_type button() const
        {
            return m_button;
        }


    private:
        // variables

        const mouse_capture_details_type m_mouse_capture_details;

        const mouse_button_type m_button;
    };
}

#endif

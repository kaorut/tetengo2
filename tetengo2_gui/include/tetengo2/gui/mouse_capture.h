/*! \file
    \brief The definition of tetengo2::gui::mouse_capture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MOUSECAPTURE_H)
#define TETENGO2_GUI_MOUSECAPTURE_H

#include <boost/core/noncopyable.hpp>


namespace tetengo2 { namespace gui {
    /*!
        \brief The class template for a mouse capture.

        \tparam Widget              A widget type.
        \tparam MouseButton         A mouse button type.
        \tparam MouseCaptureDetails A detail implementation type of a mouse_capture.
    */
    template <typename Widget, typename MouseButton, typename MouseCaptureDetails>
    class mouse_capture : private boost::noncopyable
    {
    public:
        // types

        //! The widget type.
        using widget_type = Widget;

        //! The mouse button type.
        using mouse_button_type = MouseButton;

        //! The mouse capture details type.
        using mouse_capture_details_type = MouseCaptureDetails;


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


}}

#endif

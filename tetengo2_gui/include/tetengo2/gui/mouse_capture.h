/*! \file
    \brief The definition of tetengo2::gui::mouse_capture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MOUSECAPTURE_H)
#define TETENGO2_GUI_MOUSECAPTURE_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/message/mouse_observer_set.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui {
    /*!
        \brief The class for a mouse capture.
    */
    class mouse_capture : private boost::noncopyable
    {
    public:
        // types

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
        mouse_capture(const widget_type& widget, mouse_button_type button);

        /*!
            \brief Destroys the mouse capture.
        */
        ~mouse_capture();


        // functions

        /*!
            \brief Returns the button.

            \return The button.
        */
        mouse_button_type button() const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif

/*! \file
    \brief The definition of tetengo2::gui::mouse_capture.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MOUSECAPTURE_H)
#define TETENGO2_GUI_MOUSECAPTURE_H

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a mouse capture.

        \tparam Widget              A widget type.
        \tparam MouseCaptureDetails A detail implementation type of a mouse_capture.
    */
    template <typename Widget, typename MouseCaptureDetails>
    class mouse_capture : private boost::noncopyable
    {
    public:
        // types

        //! The widget type.
        typedef Widget widget_type;

        //! The detail implementation type of a mouse capture.
        typedef MouseCaptureDetails mouse_capture_details_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse capture.

            \param widget A widget.
        */
        explicit mouse_capture(const widget_type& widget)
        :
        m_mouse_capture_details(widget)
        {}


    private:
        // variables

        const mouse_capture_details_type m_mouse_capture_details;


    };


}}

#endif

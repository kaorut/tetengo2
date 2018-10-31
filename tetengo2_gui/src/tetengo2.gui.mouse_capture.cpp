/*! \file
    \brief The definition of tetengo2::gui::mouse_capture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/mouse_capture.h>
#include <tetengo2/gui/mouse_capture.h>


namespace tetengo2::gui {
    class mouse_capture::impl : private boost::noncopyable
    {
    public:
        // types

        using widget_type = mouse_capture::widget_type;

        using mouse_button_type = mouse_capture::mouse_button_type;


        // constructors and destructor

        impl(const widget_type& widget, const mouse_button_type button)
        : m_p_mouse_capture_details{ detail::gui_detail_impl_set().create_mouse_capture(widget) }, m_button{ button }
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
        // types

        using mouse_capture_details_type = detail::base::mouse_capture;


        // variables

        const std::unique_ptr<mouse_capture_details_type> m_p_mouse_capture_details;

        const mouse_button_type m_button;
    };


    mouse_capture::mouse_capture(const widget_type& widget, const mouse_button_type button)
    : m_p_impl{ std::make_unique<impl>(widget, button) }
    {}

    mouse_capture::~mouse_capture() = default;

    mouse_capture::mouse_button_type mouse_capture::button() const
    {
        return m_p_impl->button();
    }
}

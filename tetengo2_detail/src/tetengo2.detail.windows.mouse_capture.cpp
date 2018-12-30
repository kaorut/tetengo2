/*! \file
    \brief The definition of tetengo2::detail::windows::mouse_capture.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/mouse_capture.h>
#include <tetengo2/detail/windows/widget.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::detail::windows {
    class mouse_capture::impl : private boost::noncopyable
    {
    public:
        // constructors and destructor

        explicit impl(const gui::widget::widget& widget)
        {
            ::SetCapture(reinterpret_cast<::HWND>(
                static_cast<const detail::windows::widget::windows_widget_details_type&>(widget.details()).handle));
        }

        ~impl() noexcept
        {
            ::ReleaseCapture();
        }
    };


    mouse_capture::mouse_capture(const gui::widget::widget& widget) : m_p_impl{ std::make_unique<impl>(widget) } {}

    mouse_capture::~mouse_capture() = default;
}

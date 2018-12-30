/*! \file
    \brief The definition of tetengo2::detail::stub::mouse_capture.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/stub/mouse_capture.h>
#include <tetengo2/stdalt.h>

namespace tetengo2 { namespace gui { namespace widget {
    class widget;
}}}


namespace tetengo2::detail::stub {
    class mouse_capture::impl : private boost::noncopyable
    {
    public:
        // constructors and destructor

        explicit impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) {}
    };


    mouse_capture::mouse_capture(const gui::widget::widget& widget) : m_p_impl{ std::make_unique<impl>(widget) } {}

    mouse_capture::~mouse_capture() = default;
}

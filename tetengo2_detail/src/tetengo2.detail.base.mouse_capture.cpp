/*! \file
    \brief The definition of tetengo2::detail::base::mouse_capture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/mouse_capture.h>


namespace tetengo2::detail::base {
    class mouse_capture::impl : private boost::noncopyable
    {
    };


    mouse_capture::~mouse_capture() = default;

    mouse_capture::mouse_capture() : m_p_impl{ std::make_unique<impl>() } {}
}

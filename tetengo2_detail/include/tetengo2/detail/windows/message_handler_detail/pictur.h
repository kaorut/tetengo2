/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::picture_box.

    The file name is truncated due to the path length limitation of tar command on UNIX.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_PICTUREBOX_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_PICTUREBOX_H

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/stdalt.h>

namespace tetengo2 { namespace gui { namespace widget {
    class picture_box;
}}}


namespace tetengo2::detail::windows::message_handler_detail::picture_box {
    tetengo2::stdalt::optional<::LRESULT>
    on_erase_background(gui::widget::picture_box& picture_box, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_paint(gui::widget::picture_box& picture_box, ::WPARAM w_param, ::LPARAM l_param);
}


#endif
#endif

/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::dropdown_box.

    The file name is truncated due to the path length limitation of tar command on UNIX.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_DROPDOWNBOX_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_DROPDOWNBOX_H

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
    class dropdown_box;
}}}


namespace tetengo2::detail::windows::message_handler_detail::dropdown_box {
    tetengo2::stdalt::optional<::LRESULT>
    on_tetengo2_command(gui::widget::dropdown_box& dropdown_box, ::WPARAM w_param, ::LPARAM l_param);
}


#endif
#endif

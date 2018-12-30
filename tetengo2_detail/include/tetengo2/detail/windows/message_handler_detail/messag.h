/*! \file
    \brief The definition of custom messages for tetengo2::detail::windows::message_handler_detail.

    The file name is truncated due to the path length limitation of tar command on UNIX.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_MESSAGE_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_MESSAGE_H

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2::detail::windows::message_handler_detail {
    enum class custom_message_type : ::UINT
    {
        command = WM_APP + 1,
        control_color,
    };
}


#endif
#endif

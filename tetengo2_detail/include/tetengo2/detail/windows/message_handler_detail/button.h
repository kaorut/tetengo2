/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::button.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_BUTTON_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_BUTTON_H

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/stdalt.h>

namespace tetengo2 { namespace gui { namespace widget {
    class button;
}}}


namespace tetengo2::detail::windows::message_handler_detail::button {
    tetengo2::stdalt::optional<::LRESULT>
    on_tetengo2_command(gui::widget::button& button, ::WPARAM w_param, ::LPARAM l_param);
}


#endif
#endif

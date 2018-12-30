/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::dialog.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_DIALOG_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_DIALOG_H

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
    class dialog;
}}}


namespace tetengo2::detail::windows::message_handler_detail::dialog {
    tetengo2::stdalt::optional<::LRESULT> on_command(gui::widget::dialog& dialog, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_syscommand(gui::widget::dialog& dialog, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT> on_set_focus(gui::widget::dialog& dialog, ::WPARAM w_param, ::LPARAM l_param);
}


#endif
#endif

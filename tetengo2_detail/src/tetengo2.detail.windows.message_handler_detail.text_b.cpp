/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::text_box.

    The file name is truncated due to the path length limitation of tar command on UNIX.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/message_handler_detail/text_b.h>
#include <tetengo2/gui/widget/text_box.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::detail::windows::message_handler_detail::text_box {
    tetengo2::stdalt::optional<::LRESULT> on_tetengo2_command(
        gui::widget::text_box&                      text_box,
        const ::WPARAM                              w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        switch (HIWORD(w_param))
        {
        case EN_CHANGE:
            text_box.text_box_observer_set().changed()();
            break;
        default:
            break;
        }

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }
}

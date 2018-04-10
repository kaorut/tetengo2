/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::text_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_TEXTBOX_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_TEXTBOX_H

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/stdalt.h>


namespace tetengo2::detail::windows::message_handler_detail::text_box {
    template <typename TextBox>
    tetengo2::stdalt::optional<::LRESULT>
    on_tetengo2_command(TextBox& text_box, const ::WPARAM w_param, TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
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


#endif
#endif

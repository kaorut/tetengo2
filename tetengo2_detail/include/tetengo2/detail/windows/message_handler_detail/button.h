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
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/stdalt.h>


namespace tetengo2::detail::windows::message_handler_detail::button {
    template <typename Button>
    tetengo2::stdalt::optional<::LRESULT> on_tetengo2_command(
        Button&                                     button,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        button.mouse_observer_set().clicked()();

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }
}


#endif
#endif

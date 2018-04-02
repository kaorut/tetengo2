/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::button.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_BUTTON_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_BUTTON_H

#include <boost/optional.hpp> // IWYU pragma: keep

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2::detail::windows::message_handler_detail::button {
    template <typename Button>
    boost::optional<::LRESULT> on_tetengo2_command(
        Button&                         button,
        [[maybe_unused]] const ::WPARAM w_param,
        [[maybe_unused]] const ::LPARAM l_param)
    {
        button.mouse_observer_set().clicked()();

        return boost::make_optional<::LRESULT>(0);
    }
}


#endif
#endif

/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::dropdown_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_DROPDOWNBOX_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_DROPDOWNBOX_H

#include <boost/optional.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2::detail::windows::message_handler_detail::dropdown_box {
    template <typename ListBox>
    boost::optional< ::LRESULT> on_tetengo2_command(
        ListBox&       dropdown_box,
        const ::WPARAM w_param,
        [[maybe_unused]] const ::LPARAM l_param
    )
    {
        switch (HIWORD(w_param))
        {
        case CBN_SELCHANGE:
            dropdown_box.list_selection_observer_set().selection_changed()();
            break;
        default:
            break;
        }

        return boost::make_optional< ::LRESULT>(0);
    }

}


#endif
#endif

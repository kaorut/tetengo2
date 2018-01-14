/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::text_box.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_TEXTBOX_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_TEXTBOX_H

#include <boost/core/ignore_unused.hpp> // IWYU pragma: keep
#include <boost/optional.hpp> // IWYU pragma: keep

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2 { namespace detail { namespace windows { namespace message_handler_detail
{
    namespace text_box
    {
        template <typename TextBox>
        boost::optional< ::LRESULT> on_tetengo2_command(
            TextBox&       text_box,
            const ::WPARAM w_param,
            const ::LPARAM l_param
        )
        {
            boost::ignore_unused(l_param);

            switch (HIWORD(w_param))
            {
            case EN_CHANGE:
                text_box.text_box_observer_set().changed()();
                break;
            default:
                break;
            }

            return boost::make_optional< ::LRESULT>(0);
        }


    }


}}}}


#endif
#endif

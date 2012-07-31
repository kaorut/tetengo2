/*! \file
    \brief The definition of
           tetengo2::detail::windows::message_handler_detail::message.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_MESSAGE_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_MESSAGE_H

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2 { namespace detail { namespace windows { namespace message_handler_detail
{
    struct custom_message_type { enum enum_t //!< Scoped enum.
    {
        command = WM_APP + 1,
        control_color,
    };};


}}}}


#endif
#endif

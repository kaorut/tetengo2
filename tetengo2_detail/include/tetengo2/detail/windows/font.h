/*! \file
    \brief The definition of font utilities for tetengo2::detail::windows.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_FONT_H)
#define TETENGO2_DETAIL_WINDOWS_FONT_H

#include <system_error>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief Returns a nonclient metrics.

        \param metrics A metrics where the result is stored.

        \throw std::system_error When a nonclient metrics cannot be obtained.
    */
    void get_nonclient_metrics(::NONCLIENTMETRICSW& metrics);

    /*!
        \brief Returns the message font.

        \return The message font.
    */
    ::LOGFONTW get_message_font();


}}}


#endif

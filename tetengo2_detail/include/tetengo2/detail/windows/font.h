/*! \file
    \brief The definition of font utilities for tetengo2::detail::windows.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_FONT_H)
#define TETENGO2_DETAIL_WINDOWS_FONT_H

#include <system_error>

#include <boost/throw_exception.hpp>

//#pragma warning (push)
//#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
//#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/detail/windows/windows_version.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief Returns a nonclient metrics.

        \param metrics A metrics where the result is stored.

        \throw std::system_error When a nonclient metrics cannot be obtained.
    */
    inline void get_nonclient_metrics(::NONCLIENTMETRICSW& metrics)
    {
        const ::UINT metrics_size =
            on_windows_vista_or_later() ? sizeof(::NONCLIENTMETRICSW) : sizeof(::NONCLIENTMETRICSW) - sizeof(int);
        metrics.cbSize = metrics_size;
        if (::SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, metrics_size, &metrics, 0) == 0)
        {
            BOOST_THROW_EXCEPTION((
                std::system_error{
                    std::error_code{ ERROR_FUNCTION_FAILED, win32_category() }, "Can't get non-client metrics."
                }
            ));
        }
    }

    /*!
        \brief Returns the message font.

        \return The message font.
    */
    inline ::LOGFONTW get_message_font()
    {
        ::NONCLIENTMETRICSW metrics;
        get_nonclient_metrics(metrics);

        return metrics.lfMessageFont;
    }


}}}


#endif

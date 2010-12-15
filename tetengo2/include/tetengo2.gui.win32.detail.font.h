/*! \file
    \brief The definition of tetengo2::gui::win32::detail::dialog_font.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_DETAIL_DIALOGFONT_H)
#define TETENGO2_GUI_WIN32_DETAIL_DIALOGFONT_H

#include <stdexcept>

#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>


namespace tetengo2 { namespace gui { namespace win32 { namespace detail
{
    inline void get_nonclient_metrics(::NONCLIENTMETRICSW& metrics)
    {
        ::OSVERSIONINFOW os_version_info;
        os_version_info.dwOSVersionInfoSize = sizeof(::OSVERSIONINFOW);
        if (::GetVersionEx(&os_version_info) == 0)
        {
            BOOST_THROW_EXCEPTION(
                std::runtime_error("Can't get Windows version.")
            );
        }

        const ::UINT metrics_size = os_version_info.dwMajorVersion >= 6 ?
            sizeof(::NONCLIENTMETRICSW) :
            sizeof(::NONCLIENTMETRICSW) - sizeof(int);
        metrics.cbSize = metrics_size;
        if (
            ::SystemParametersInfoW(
                SPI_GETNONCLIENTMETRICS,
                metrics_size,
                &metrics,
                0
            ) == 0
        )
        {
            BOOST_THROW_EXCEPTION(
                std::runtime_error("Can't get non-client metrics.")
            );
        }
    }

    inline ::LOGFONTW get_message_font()
    {
        ::NONCLIENTMETRICSW metrics;
        get_nonclient_metrics(metrics);

        return metrics.lfMessageFont;
    }


}}}}


#endif

/*! \file
    \brief The definition of tetengo2::gui::win32::detail::font.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_DETAIL_FONT_H)
#define TETENGO2_GUI_WIN32_DETAIL_FONT_H

#if !defined(DOCUMENTATION)
#include <stdexcept>

#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.win32.detail.windows_version.h"


namespace tetengo2 { namespace gui { namespace win32 { namespace detail
{
    inline void get_nonclient_metrics(::NONCLIENTMETRICSW& metrics)
    {
        const ::UINT metrics_size =
            tetengo2::win32::detail::on_windows_vista_or_later() ?
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


#endif

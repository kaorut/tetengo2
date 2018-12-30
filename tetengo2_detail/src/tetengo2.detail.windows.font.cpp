/*! \file
    \brief The definition of font utilities for tetengo2::detail::windows.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <system_error> // IWYU pragma: keep

#include <boost/throw_exception.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/error_category.h> // IWYU pragma: keep
#include <tetengo2/detail/windows/font.h> // IWYU pragma: keep
#include <tetengo2/detail/windows/windows_version.h> // IWYU pragma: keep


namespace tetengo2::detail::windows {
    void get_nonclient_metrics(::NONCLIENTMETRICSW& metrics)
    {
        const ::UINT metrics_size =
            on_windows_vista_or_later() ? sizeof(::NONCLIENTMETRICSW) : sizeof(::NONCLIENTMETRICSW) - sizeof(int);
        metrics.cbSize = metrics_size;
        if (::SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, metrics_size, &metrics, 0) == 0)
        {
            BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() },
                                                      "Can't get non-client metrics." }));
        }
    }

    ::LOGFONTW get_message_font()
    {
        ::NONCLIENTMETRICSW metrics;
        get_nonclient_metrics(metrics);

        return metrics.lfMessageFont;
    }
}

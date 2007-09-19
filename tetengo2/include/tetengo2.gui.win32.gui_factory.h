/*! \file
    \brief The definition of tetengo2::gui::win32::gui_factory.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_GUIFACTORY_H)
#define TETENGO2_GUI_WIN32_GUIFACTORY_H

#include <string>

#define OEMRESOURCE
#include <windows.h>
#include <gdiplus.h>

#include "tetengo2.gui.gui_factory.h"
#include "tetengo2.gui.win32.alert.h"
#include "tetengo2.gui.win32.canvas.h"
#include "tetengo2.gui.win32.gui_initializer_finalizer.h"
#include "tetengo2.gui.win32.window.h"
#include "tetengo2.win32.encode.h"


namespace tetengo2 { namespace gui { namespace win32
{
    namespace
    {
        typedef
            canvas<
                const Gdiplus::Graphics*,
                std::size_t,
                std::wstring,
                tetengo2::win32::encode,
                ::HWND
            >
            canvas_type;

        typedef alert< ::HWND, tetengo2::win32::encode> alert_type;

        typedef
            window<
                ::HWND,
                canvas_type,
                alert_type,
                std::wstring,
                tetengo2::win32::encode,
                ::WNDPROC
            >
            window_type;


    }

    //! The GUI object factory type for Win32 platforms.
    typedef
        tetengo2::gui::gui_factory<
            tetengo2::gui::win32::gui_initializer_finalizer,
            window_type
        >
        gui_factory;


}}}

#endif

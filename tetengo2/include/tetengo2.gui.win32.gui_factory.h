/*! \file
    \brief The definition of tetengo2::gui::win32::gui_factory.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_GUIFACTORY_H)
#define TETENGO2_GUI_WIN32_GUIFACTORY_H

//#include <cstddef>
//#include <string>

#include "tetengo2.gui.gui_factory.h"
#include "tetengo2.gui.menu_command.h"
#include "tetengo2.gui.menu_separator.h"
#include "tetengo2.gui.paint_observer.h"
#include "tetengo2.gui.window_observer.h"
#include "tetengo2.gui.win32.alert.h"
#include "tetengo2.gui.win32.canvas.h"
#include "tetengo2.gui.win32.gui_initializer_finalizer.h"
#include "tetengo2.gui.win32.main_menu.h"
#include "tetengo2.gui.win32.menu_item_list.h"
#include "tetengo2.gui.win32.popup_menu.h"
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
            tetengo2::gui::menu_item< ::UINT, ::HMENU, std::wstring>
            menu_item_type;

        typedef
            tetengo2::gui::win32::main_menu<
                menu_item_type,
                tetengo2::gui::win32::menu_item_list<menu_item_type>
            >
            main_menu_type;

        typedef
            window<
                ::HWND,
                canvas_type,
                alert_type,
                std::wstring,
                tetengo2::win32::encode,
                main_menu_type,
                tetengo2::gui::paint_observer<canvas_type>,
                tetengo2::gui::window_observer
            >
            window_type;

        typedef
            menu_command< ::UINT, ::HMENU, std::wstring, std::wstring>
            menu_command_type;

        typedef
            popup_menu<
                ::UINT,
                ::HMENU,
                std::wstring,
                tetengo2::gui::win32::menu_item_list<menu_item_type>
            >
            popup_menu_type;

        typedef
            menu_separator< ::UINT, ::HMENU, std::wstring>
            menu_separator_type;


    }

    //! The GUI object factory type for Win32 platforms.
    typedef
        tetengo2::gui::gui_factory<
            tetengo2::gui::win32::gui_initializer_finalizer,
            window_type,
            main_menu_type,
            menu_command_type,
            popup_menu_type,
            menu_separator_type
        >
        gui_factory;


}}}

#endif

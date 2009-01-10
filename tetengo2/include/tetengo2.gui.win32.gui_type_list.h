/*! \file
    \brief The definition of tetengo2::gui::win32::gui_type_list.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_GUITYPELIST_H)
#define TETENGO2_GUI_WIN32_GUITYPELIST_H

#include <boost/concept_check.hpp>

#include "concept_tetengo2.String.h"
#include "tetengo2.gui.menu_command.h"
#include "tetengo2.gui.menu_observer.h"
#include "tetengo2.gui.menu_separator.h"
#include "tetengo2.gui.paint_observer.h"
#include "tetengo2.gui.window_observer.h"
#include "tetengo2.gui.win32.alert.h"
#include "tetengo2.gui.win32.canvas.h"
#include "tetengo2.gui.win32.gui_initializer_finalizer.h"
#include "tetengo2.gui.win32.main_menu.h"
#include "tetengo2.gui.win32.menu_item.h"
#include "tetengo2.gui.win32.menu_item_list.h"
#include "tetengo2.gui.win32.popup_menu.h"
#include "tetengo2.gui.win32.window.h"
#include "tetengo2.win32.encode.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a GUI type list for Win32 platforms.

        \tparam Size   A size type. It must conform to
                       boost::UnsignedInteger<Size>.
        \tparam String A string type. It must conform to
                       concept_tetengo2::String<String>.
    */
    template <typename Size, typename String>
    class gui_type_list
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Size>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));


    public:
        // types

        typedef
            tetengo2::gui::win32::gui_initializer_finalizer
            gui_initializer_finalizer_type;

        typedef
            canvas<
                const Gdiplus::Graphics*,
                Size,
                String,
                tetengo2::win32::encode,
                ::HWND
            >
            canvas_type;

        typedef alert< ::HWND, tetengo2::win32::encode> alert_type;

        typedef
            tetengo2::gui::win32::menu_item<
                ::UINT,
                ::HMENU,
                String,
                tetengo2::win32::encode,
                tetengo2::gui::menu_observer
            >
            menu_item_type;

        typedef
            popup_menu<
                menu_item_type,
                tetengo2::gui::win32::menu_item_list<menu_item_type>
            >
            popup_menu_type;

        typedef
            tetengo2::gui::win32::main_menu<popup_menu_type> main_menu_type;

        typedef
            window<
                ::HWND,
                canvas_type,
                alert_type,
                String,
                tetengo2::win32::encode,
                main_menu_type,
                tetengo2::gui::paint_observer<canvas_type>,
                tetengo2::gui::window_observer
            >
            window_type;

        typedef menu_command<menu_item_type> menu_command_type;

        typedef menu_separator<menu_item_type> menu_separator_type;


    };


}}}

#endif

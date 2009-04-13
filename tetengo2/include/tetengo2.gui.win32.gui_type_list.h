/*! \file
    \brief The definition of tetengo2::gui::win32::gui_type_list.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_GUITYPELIST_H)
#define TETENGO2_GUI_WIN32_GUITYPELIST_H

//#include <boost/concept_check.hpp>

#include "tetengo2.gui.menu_command.h"
#include "tetengo2.gui.menu_observer.h"
#include "tetengo2.gui.menu_separator.h"
#include "tetengo2.gui.mouse_observer.h"
#include "tetengo2.gui.paint_observer.h"
#include "tetengo2.gui.window_observer.h"
#include "tetengo2.gui.win32.abstract_window.h"
#include "tetengo2.gui.win32.alert.h"
#include "tetengo2.gui.win32.button.h"
#include "tetengo2.gui.win32.canvas.h"
#include "tetengo2.gui.win32.dialog.h"
#include "tetengo2.gui.win32.dialog_message_loop.h"
#include "tetengo2.gui.win32.font.h"
#include "tetengo2.gui.win32.gui_initializer_finalizer.h"
#include "tetengo2.gui.win32.main_menu.h"
#include "tetengo2.gui.win32.menu_item.h"
#include "tetengo2.gui.win32.menu_item_list.h"
#include "tetengo2.gui.win32.message_loop.h"
#include "tetengo2.gui.win32.popup_menu.h"
#include "tetengo2.gui.win32.quit_message_loop.h"
#include "tetengo2.gui.win32.widget.h"
#include "tetengo2.gui.win32.window.h"
#include "tetengo2.win32.encode.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a GUI type list for Win32 platforms.

        \tparam Difference A difference type. It must conform to
                           boost::SignedInteger<Difference>.
        \tparam Size       A size type. It must conform to
                           boost::UnsignedInteger<Size>.
        \tparam String     A string type. It must conform to
                           concept_tetengo2::String<String>.
    */
    template <typename Difference, typename Size, typename String>
    class gui_type_list
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((boost::SignedInteger<Difference>));
        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Size>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));


    public:
        // types

        //! The GUI initialization and finalization manager type.
        typedef
            tetengo2::gui::win32::gui_initializer_finalizer
            gui_initializer_finalizer_type;

        //! The message loop type.
        typedef message_loop message_loop_type;

        //! The quit-message-loop type.
        typedef quit_message_loop quit_message_loop_type;

        //! The alert dialog type.
        typedef alert< ::HWND, tetengo2::win32::encode> alert_type;

        //! The font type.
        typedef font<String, Size> font_type;

        //! The canvas type.
        typedef
            canvas<
                const Gdiplus::Graphics*,
                Size,
                String,
                tetengo2::win32::encode,
                ::HWND,
                font_type
            >
            canvas_type;

    private:
        typedef
            tetengo2::gui::win32::menu_item<
                ::UINT,
                ::HMENU,
                String,
                tetengo2::win32::encode,
                tetengo2::gui::menu_observer
            >
            menu_item_type;

    public:
        //! The widget type.
        typedef
            widget<
                ::HWND,
                canvas_type,
                alert_type,
                Difference,
                Size,
                String,
                tetengo2::win32::encode,
                font_type,
                tetengo2::gui::paint_observer<canvas_type>,
                tetengo2::gui::mouse_observer
            >
            widget_type;

        //! The popup menu type.
        typedef
            popup_menu<
                menu_item_type,
                tetengo2::gui::win32::menu_item_list<menu_item_type>
            >
            popup_menu_type;

        //! The main menu type.
        typedef
            tetengo2::gui::win32::main_menu<popup_menu_type> main_menu_type;

        //! The abstract window type.
        typedef
            abstract_window<
                widget_type, main_menu_type, tetengo2::gui::window_observer
            >
            abstract_window_type;

        //! The window type.
        typedef window<abstract_window_type> window_type;

        //! The menu command type.
        typedef menu_command<menu_item_type> menu_command_type;

        //! The menu separator type.
        typedef menu_separator<menu_item_type> menu_separator_type;

        //! The dialog message loop type.
        typedef dialog_message_loop dialog_message_loop_type;

        //! The dialog type.
        typedef
            dialog<
                abstract_window_type,
                dialog_message_loop_type,
                quit_message_loop_type
            >
            dialog_type;

        //! The button type.
        typedef button<widget_type> button_type;


    private:
        // forbidden operations

        gui_type_list();


    };


}}}

#endif

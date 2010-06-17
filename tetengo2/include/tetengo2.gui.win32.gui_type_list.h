/*! \file
    \brief The definition of tetengo2::gui::win32::gui_type_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_GUITYPELIST_H)
#define TETENGO2_GUI_WIN32_GUITYPELIST_H

//#include <boost/concept_check.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <windows.h>
//#if !defined(min) && !defined(DOCUMENTATION)
//#   define min(a, b) ((a) < (b) ? (a) : (b))
//#endif
//#if !defined(max) && !defined(DOCUMENTATION)
//#   define max(a, b) ((a) > (b) ? (a) : (b))
//#endif
//#include <gdiplus.h>
//#undef min
//#undef max

#include "concept_tetengo2.String.h"
#include "concept_tetengo2.Encoder.h"
#include "tetengo2.gui.menu_observer.h"
#include "tetengo2.gui.mouse_observer.h"
#include "tetengo2.gui.paint_observer.h"
#include "tetengo2.gui.window_observer.h"
#include "tetengo2.gui.win32.abstract_popup_menu.h"
#include "tetengo2.gui.win32.abstract_window.h"
#include "tetengo2.gui.win32.alert.h"
#include "tetengo2.gui.win32.button.h"
#include "tetengo2.gui.win32.canvas.h"
#include "tetengo2.gui.win32.dialog.h"
#include "tetengo2.gui.win32.dialog_message_loop.h"
#include "tetengo2.gui.win32.font.h"
#include "tetengo2.gui.win32.gui_initializer_finalizer.h"
#include "tetengo2.gui.win32.main_menu.h"
#include "tetengo2.gui.win32.menu.h"
#include "tetengo2.gui.win32.menu_command.h"
#include "tetengo2.gui.win32.menu_separator.h"
#include "tetengo2.gui.win32.message_loop.h"
#include "tetengo2.gui.win32.popup_menu.h"
#include "tetengo2.gui.win32.quit_message_loop.h"
#include "tetengo2.gui.win32.widget.h"
#include "tetengo2.gui.win32.window.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a GUI type list for Win32 platforms.

        \tparam Difference       A difference type. It must conform to
                                 boost::SignedInteger<Difference>.
        \tparam Size             A size type. It must conform to
                                 boost::UnsignedInteger<Size>.
        \tparam String           A string type. It must conform to
                                 concept_tetengo2::String<String>.
        \tparam UiEncoder        A encoder for the user interface type. It
                                 must
                                 conform to concept_tetengo2::Encoder<UiEncoder>.
        \tparam ExceptionEncoder A encoder for exceptions. It must
                                 conform to concept_tetengo2::Encoder<ExceptionEncoder>.
    */
    template <
        typename Difference,
        typename Size,
        typename String,
        typename UiEncoder,
        typename ExceptionEncoder
    >
    class gui_type_list
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((boost::SignedInteger<Difference>));
        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Size>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::Encoder<UiEncoder>));


    public:
        // types

        //! \return The GUI initialization and finalization manager type.
        typedef
            tetengo2::gui::win32::gui_initializer_finalizer
            gui_initializer_finalizer_type;

        //! \return The message loop type.
        typedef message_loop message_loop_type;

        //! \return The quit-message-loop type.
        typedef quit_message_loop quit_message_loop_type;

        //! \return The encoder type.for the user interface.
        typedef UiEncoder ui_encoder_type;

        //! \return The encoder type.for exceptions.
        typedef ExceptionEncoder exception_encoder_type;

        //! \return The alert dialog type.
        typedef
            alert< ::HWND, ui_encoder_type, exception_encoder_type>
            alert_type;

        //! \return The font type.
        typedef font<String, Size> font_type;

        //! \return The canvas type.
        typedef
            canvas<
                const Gdiplus::Graphics*,
                Size,
                String,
                ui_encoder_type,
                ::HWND,
                font_type
            >
            canvas_type;

        //! \return The widget type.
        typedef
            widget<
                ::HWND,
                canvas_type,
                alert_type,
                Difference,
                Size,
                String,
                ui_encoder_type,
                font_type,
                tetengo2::gui::paint_observer<canvas_type>,
                tetengo2::gui::mouse_observer
            >
            widget_type;

    private:
        typedef
            tetengo2::gui::win32::menu<
                ::UINT,
                ::HMENU,
                String,
                ui_encoder_type,
                tetengo2::gui::menu_observer
            >
            menu_type;

        typedef
            tetengo2::gui::win32::abstract_popup_menu<menu_type>
            abstract_popup_menu_type;

    public:
        //! \return The main menu type.
        typedef
            tetengo2::gui::win32::main_menu<abstract_popup_menu_type>
            main_menu_type;

        //! \return The popup menu type.
        typedef popup_menu<abstract_popup_menu_type> popup_menu_type;

        //! \return The abstract window type.
        typedef
            abstract_window<
                widget_type, main_menu_type, tetengo2::gui::window_observer
            >
            abstract_window_type;

        //! \return The window type.
        typedef window<abstract_window_type> window_type;

        //! \return The menu command type.
        typedef menu_command<menu_type> menu_command_type;

        //! \return The menu separator type.
        typedef menu_separator<menu_type> menu_separator_type;

        //! \return The dialog message loop type.
        typedef dialog_message_loop dialog_message_loop_type;

        //! \return The dialog type.
        typedef
            dialog<
                abstract_window_type,
                dialog_message_loop_type,
                quit_message_loop_type
            >
            dialog_type;

        //! \return The button type.
        typedef button<widget_type> button_type;


    private:
        // forbidden operations

        gui_type_list();


    };


}}}

#endif

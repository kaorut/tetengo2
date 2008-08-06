/*! \file
    \brief The definition of stub_tetengo2::gui::gui_factory.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_GUIFACTORY_H)
#define STUBTETENGO2_GUI_GUIFACTORY_H

//#include <cstddef>
//#include <string>

#include "tetengo2.gui.gui_factory.h"
#include "tetengo2.gui.menu_command.h"
#include "tetengo2.gui.menu_observer.h"
#include "tetengo2.gui.menu_separator.h"
#include "tetengo2.gui.paint_observer.h"
#include "tetengo2.gui.window_observer.h"

#include "stub_tetengo2.gui.alert.h"
#include "stub_tetengo2.gui.canvas.h"
#include "stub_tetengo2.gui.gui_initializer_finalizer.h"
#include "stub_tetengo2.gui.main_menu.h"
#include "stub_tetengo2.gui.menu_item_list.h"
#include "stub_tetengo2.gui.popup_menu.h"
#include "stub_tetengo2.gui.window.h"
#include "stub_tetengo2.encode.h"


namespace stub_tetengo2 { namespace gui
{
    namespace
    {
        typedef
            canvas<
                const void*,
                std::size_t,
                std::wstring,
                stub_tetengo2::encode,
                const void*
            >
            canvas_type;

        typedef alert<const void*, stub_tetengo2::encode> alert_type;

        typedef
            tetengo2::gui::menu_item<
                unsigned int,
                const void*,
                std::wstring,
                stub_tetengo2::encode,
                tetengo2::gui::menu_observer
            >
            menu_item_type;

        typedef
            stub_tetengo2::gui::main_menu<
                menu_item_type,
                stub_tetengo2::gui::menu_item_list<menu_item_type>
            >
            main_menu_type;

        typedef
            window<
                const void*,
                canvas_type,
                alert_type,
                std::wstring,
                stub_tetengo2::encode,
                main_menu_type,
                tetengo2::gui::paint_observer<canvas_type>,
                tetengo2::gui::window_observer
            >
            window_type;

        typedef
            tetengo2::gui::menu_command<
                unsigned int,
                const void*,
                std::wstring,
                stub_tetengo2::encode,
                tetengo2::gui::menu_observer
            >
            menu_command_type;

        typedef
            stub_tetengo2::gui::popup_menu<
                unsigned int,
                const void*,
                std::wstring,
                stub_tetengo2::encode,
                stub_tetengo2::gui::menu_item_list<menu_item_type>,
                tetengo2::gui::menu_observer
            >
            popup_menu_type;

        typedef
            tetengo2::gui::menu_separator<
                unsigned int,
                const void*,
                std::wstring,
                stub_tetengo2::encode,
                tetengo2::gui::menu_observer
            >
            menu_separator_type;


    }

    typedef
        tetengo2::gui::gui_factory<
            stub_tetengo2::gui::gui_initializer_finalizer,
            window_type,
            main_menu_type,
            menu_command_type,
            popup_menu_type,
            menu_separator_type
        >
        gui_factory;


}}

#endif

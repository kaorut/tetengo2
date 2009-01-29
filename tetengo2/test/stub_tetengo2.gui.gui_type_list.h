/*! \file
    \brief The definition of stub_tetengo2::gui::gui_type_list.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_GUITYPELIST_H)
#define STUBTETENGO2_GUI_GUITYPELIST_H

//#include <boost/concept_check.hpp>

#include "stub_tetengo2.gui.alert.h"
#include "stub_tetengo2.gui.canvas.h"
#include "stub_tetengo2.gui.gui_initializer_finalizer.h"
#include "stub_tetengo2.gui.main_menu.h"
#include "stub_tetengo2.gui.menu_item.h"
#include "stub_tetengo2.gui.menu_item_list.h"
#include "stub_tetengo2.gui.message_loop.h"
#include "stub_tetengo2.gui.popup_menu.h"
#include "stub_tetengo2.gui.quit_message_loop.h"
#include "stub_tetengo2.gui.window.h"
#include "stub_tetengo2.encode.h"
#include "tetengo2.gui.menu_command.h"
#include "tetengo2.gui.menu_observer.h"
#include "tetengo2.gui.menu_separator.h"
#include "tetengo2.gui.paint_observer.h"
#include "tetengo2.gui.window_observer.h"


namespace stub_tetengo2 { namespace gui
{
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
            stub_tetengo2::gui::gui_initializer_finalizer
            gui_initializer_finalizer_type;

        typedef message_loop message_loop_type;

        typedef quit_message_loop quit_message_loop_type;

        typedef alert<const void*, stub_tetengo2::encode> alert_type;

    private:
        typedef
            canvas<
                const void*,
                Size,
                String,
                stub_tetengo2::encode,
                const void*
            >
            canvas_type;

        typedef
            stub_tetengo2::gui::menu_item<
                unsigned int,
                const void*,
                String,
                stub_tetengo2::encode,
                tetengo2::gui::menu_observer
            >
            menu_item_type;

    public:
        typedef
            stub_tetengo2::gui::popup_menu<
                menu_item_type,
                stub_tetengo2::gui::menu_item_list<menu_item_type>
            >
            popup_menu_type;

        typedef stub_tetengo2::gui::main_menu<popup_menu_type> main_menu_type;

        typedef
            window<
                const void*,
                canvas_type,
                alert_type,
                Size,
                String,
                stub_tetengo2::encode,
                main_menu_type,
                tetengo2::gui::paint_observer<canvas_type>,
                tetengo2::gui::window_observer
            >
            window_type;

        typedef tetengo2::gui::menu_command<menu_item_type> menu_command_type;

        typedef
            tetengo2::gui::menu_separator<menu_item_type> menu_separator_type;


    private:
        // forbidden operations

        gui_type_list();


    };


}}

#endif

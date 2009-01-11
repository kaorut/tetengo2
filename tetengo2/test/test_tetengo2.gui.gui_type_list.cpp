/*! \file
    \brief Test of class tetengo2::gui::gui_type_list.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.gui_type_list.h"

#include "stub_tetengo2.encode.h"
#include "stub_tetengo2.gui.alert.h"
#include "stub_tetengo2.gui.canvas.h"
#include "stub_tetengo2.gui.gui_initializer_finalizer.h"
#include "stub_tetengo2.gui.main_menu.h"
#include "stub_tetengo2.gui.menu_item.h"
#include "stub_tetengo2.gui.menu_item_list.h"
#include "stub_tetengo2.gui.popup_menu.h"
#include "stub_tetengo2.gui.window.h"
#include "tetengo2.gui.menu_command.h"
#include "tetengo2.gui.menu_observer.h"
#include "tetengo2.gui.menu_separator.h"
#include "tetengo2.gui.paint_observer.h"
#include "tetengo2.gui.window_observer.h"

#include "test_tetengo2.gui.gui_type_list.h"


namespace
{
    // types

    typedef
        stub_tetengo2::gui::canvas<
            const void*,
            std::size_t,
            std::wstring,
            stub_tetengo2::encode,
            const void*
        >
        canvas_type;

    typedef
        stub_tetengo2::gui::menu_item<
            unsigned int,
            const void*,
            std::wstring,
            stub_tetengo2::encode,
            tetengo2::gui::menu_observer
        >
        menu_item_type;

    typedef
        stub_tetengo2::gui::popup_menu<
            menu_item_type,
            stub_tetengo2::gui::menu_item_list<menu_item_type>
        >
        popup_menu_type;

    typedef stub_tetengo2::gui::main_menu<popup_menu_type> main_menu_type;

    typedef 
        stub_tetengo2::gui::window<
            const void*,
            canvas_type,
            stub_tetengo2::gui::alert<const void*, stub_tetengo2::encode>,
            std::wstring,
            stub_tetengo2::encode,
            main_menu_type,
            tetengo2::gui::paint_observer<canvas_type>,
            tetengo2::gui::window_observer
        >
        window_type;

    typedef tetengo2::gui::menu_command<menu_item_type> menu_command_type;

    typedef tetengo2::gui::menu_separator<menu_item_type> menu_separator_type;

    typedef
        tetengo2::gui::gui_type_list<
            stub_tetengo2::gui::gui_initializer_finalizer,
            window_type,
            main_menu_type,
            menu_command_type,
            popup_menu_type,
            menu_separator_type
        >
        gui_type_list_type;

}

namespace test_tetengo2 { namespace gui
{
    // functions

    boost::unit_test::test_suite* gui_type_list::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::gui_type_list");

        return p_suite;
    }


}}

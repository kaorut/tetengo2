/*! \file
    \brief Test of class tetengo2::gui::gui_factory.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>
//#include <memory>

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.gui_factory.h"

#include "stub_tetengo2.encode.h"
#include "stub_tetengo2.gui.alert.h"
#include "stub_tetengo2.gui.canvas.h"
#include "stub_tetengo2.gui.gui_initializer_finalizer.h"
#include "stub_tetengo2.gui.main_menu.h"
#include "stub_tetengo2.gui.menu_item_list.h"
#include "stub_tetengo2.gui.popup_menu.h"
#include "stub_tetengo2.gui.window.h"
#include "tetengo2.gui.menu_command.h"
#include "tetengo2.gui.menu_observer.h"
#include "tetengo2.gui.menu_separator.h"
#include "tetengo2.gui.paint_observer.h"
#include "tetengo2.gui.window_observer.h"

#include "test_tetengo2.gui.gui_factory.h"


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
            tetengo2::gui::menu_observer,
            stub_tetengo2::gui::menu_item_list<menu_item_type>
        >
        popup_menu_type;

    typedef tetengo2::gui::menu_separator<menu_item_type> menu_separator_type;

    typedef
        tetengo2::gui::gui_factory<
            stub_tetengo2::gui::gui_initializer_finalizer,
            window_type,
            main_menu_type,
            menu_command_type,
            popup_menu_type,
            menu_separator_type
        >
        gui_factory_type;

}

namespace test_tetengo2 { namespace gui
{
    // functions

    boost::unit_test::test_suite* gui_factory::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::gui_factory");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(create_window));

        return p_suite;
    }

    void gui_factory::construction()
    {
        BOOST_CHECKPOINT("");

        const gui_factory_type gui_factory(
            std::auto_ptr<
                const stub_tetengo2::gui::gui_initializer_finalizer
            >(
                new stub_tetengo2::gui::gui_initializer_finalizer()
            )
        );
    }

    void gui_factory::create_window()
    {
        BOOST_CHECKPOINT("");

        const gui_factory_type gui_factory(
            std::auto_ptr<
                const stub_tetengo2::gui::gui_initializer_finalizer
            >(
                new stub_tetengo2::gui::gui_initializer_finalizer()
            )
        );

        const std::auto_ptr<window_type> p_window =
            gui_factory.create_window();
        BOOST_CHECK(p_window.get() != NULL);
    }


}}

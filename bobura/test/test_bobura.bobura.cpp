/*! \file
    \brief Test of class bobura::bobura.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>

#include <boost/function.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.bobura.h"
#include "bobura.settings.h"

#include <stub_tetengo2.gui.gui_type_list.h>
#include <stub_tetengo2.gui.message_loop.h>
#include <stub_tetengo2.gui.quit_message_loop.h>

#include "test_bobura.bobura.h"


namespace
{
    // types

    typedef
        stub_tetengo2::gui::gui_type_list<std::size_t, std::wstring>
        gui_type_list_type;

    typedef
        gui_type_list_type::gui_initializer_finalizer_type
        gui_initializer_finalizer_type;

    typedef bobura::settings<std::wstring> settings_type;

    typedef
        bobura::bobura<
            settings_type, gui_type_list_type, boost::function<void ()>
        >
        bobura_type;

}

namespace test_bobura
{
    // functions

    boost::unit_test::test_suite* bobura::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::bobura");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(run));

        return p_suite;
    }

    void bobura::construction()
    {
        BOOST_CHECKPOINT("");

        const settings_type settings;
        const bobura_type bobura(settings);
    }

    void bobura::run()
    {
        BOOST_CHECKPOINT("");

        const settings_type settings;
        const bobura_type bobura(settings);

        BOOST_CHECK_EQUAL(bobura.run(), 0);
    }


}

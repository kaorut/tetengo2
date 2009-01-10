/*! \file
    \brief Test of class bobura::bobura.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <cstddef>
//#include <memory>
#include <string>

#include <boost/function.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.bobura.h"

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

    typedef
        bobura::bobura<
            gui_type_list_type,
            stub_tetengo2::gui::message_loop,
            stub_tetengo2::gui::quit_message_loop,
            boost::function<void ()>
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

        const bobura_type bobura;
    }

    void bobura::run()
    {
        BOOST_CHECKPOINT("");

        const bobura_type bobura;

        BOOST_CHECK_EQUAL(bobura.run(), 0);
    }


}

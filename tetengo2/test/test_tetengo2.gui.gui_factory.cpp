/*! \file
    \brief Test of class tetengo2::gui::gui_factory.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.gui_factory.h"

#include "test_tetengo2.gui.gui_factory.h"


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
        BOOST_WARN("Not implemented yet.");
    }

    void gui_factory::create_window()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}

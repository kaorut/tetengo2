/*! \file
    \brief Test of class tetengo2::gui::window_observer.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "tetengo2.gui.window_observer.h"

#include "test_tetengo2.gui.window_observer.h"


namespace test_tetengo2 { namespace gui
{
    // functions

    boost::unit_test::test_suite* window_observer::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::window_observer");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(destroyed));

        return p_suite;
    }

    void window_observer::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void window_observer::destroyed()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}

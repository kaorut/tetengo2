/*! \file
    \brief Test of class tetengo2::gui::paint_observer.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "tetengo2.gui.paint_observer.h"

#include "test_tetengo2.gui.paint_observer.h"


namespace test_tetengo2 { namespace gui
{
    // functions

    boost::unit_test::test_suite* paint_observer::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::paint_observer");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(paint));

        return p_suite;
    }

    void paint_observer::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void paint_observer::paint()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}

/*! \file
    \brief Test of class tetengo2::gui::win32::canvas.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.win32.canvas.h"

#include "test_tetengo2.gui.win32.canvas.h"


namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* canvas::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32::canvas");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(handle));
        p_suite->add(BOOST_TEST_CASE(draw_text));

        return p_suite;
    }

    void canvas::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void canvas::handle()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void canvas::draw_text()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}

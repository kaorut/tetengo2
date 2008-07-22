/*! \file
    \brief Test of class tetengo2::gui::win32::quit_message_loop.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.win32.quit_message_loop.h"

#include "test_tetengo2.gui.win32.quit_message_loop.h"


namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* quit_message_loop::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32::quit_message_loop");

        p_suite->add(BOOST_TEST_CASE(operator_paren));

        return p_suite;
    }

    void quit_message_loop::operator_paren()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}

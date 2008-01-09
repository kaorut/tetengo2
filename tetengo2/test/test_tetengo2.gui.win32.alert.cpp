/*! \file
    \brief Test of class tetengo2::gui::win32::alert.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "tetengo2.gui.win32.alert.h"

#include "test_tetengo2.gui.win32.alert.h"


namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* alert::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32::alert");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(operator_paren));

        return p_suite;
    }

    void alert::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void alert::operator_paren()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}

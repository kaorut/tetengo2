/*! \file
    \brief Test of class tetengo2::gui::dialog.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.win32.dialog.h"

#include "test_tetengo2.gui.win32.dialog.h"


namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* dialog::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32::dialog");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(do_modal));

        return p_suite;
    }

    void dialog::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void dialog::do_modal()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}

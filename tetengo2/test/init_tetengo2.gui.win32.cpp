/*! \file
    \brief Test of namespace tetengo2::gui::win32.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "init_tetengo2.gui.win32.h"
#include "test_tetengo2.gui.win32.alert.h"


namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32");

        p_suite->add(alert::suite());

        return p_suite;
    }


}}}

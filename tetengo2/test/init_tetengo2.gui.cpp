/*! \file
    \brief Test of namespace tetengo2::gui.

    Copyright (C) 2007 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "init_tetengo2.gui.h"
#include "init_tetengo2.gui.win32.h"


namespace test_tetengo2 { namespace gui
{
    // functions

    boost::unit_test::test_suite* suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui");

        p_suite->add(win32::suite());

        return p_suite;
    }


}}

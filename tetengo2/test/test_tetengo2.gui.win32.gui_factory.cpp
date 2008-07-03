/*! \file
    \brief Test of class tetengo2::gui::win32::gui_factory.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

//#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.win32.gui_factory.h"

#include "test_tetengo2.gui.win32.gui_factory.h"


namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* gui_factory::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32::gui_factory");

        return p_suite;
    }


}}}

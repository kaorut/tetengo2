/*! \file
    \brief Test of class tetengo2::gui::win32::gui_type_list.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.win32.gui_type_list.h"

#include "test_tetengo2.gui.win32.gui_type_list.h"


namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* gui_type_list::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32::gui_type_list");

        return p_suite;
    }


}}}

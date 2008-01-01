/*! \file
    \brief Test of class tetengo2::gui::gui_factory.

    Copyright (C) 2007 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.gui_factory.h"

#include "test_tetengo2.gui.gui_factory.h"


namespace test_tetengo2 { namespace gui
{
    // functions

    boost::unit_test::test_suite* gui_factory::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::gui_factory");

        return p_suite;
    }


}}

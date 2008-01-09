/*! \file
    \brief Test of class tetengo2::gui::win32::gui_initializer_finalizer.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "tetengo2.gui.win32.gui_initializer_finalizer.h"

#include "test_tetengo2.gui.win32.gui_initializer_finalizer.h"


namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* gui_initializer_finalizer::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32::gui_initializer_finalizer");

        p_suite->add(BOOST_TEST_CASE(construction));

        return p_suite;
    }

    void gui_initializer_finalizer::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}

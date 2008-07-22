/*! \file
    \brief Test of namespace tetengo2::gui.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "init_tetengo2.gui.h"
#if defined(_WIN32)
#include "init_tetengo2.gui.win32.h"
#endif
#include "test_tetengo2.gui.gui_factory.h"
#include "test_tetengo2.gui.paint_observer.h"
#include "test_tetengo2.gui.window_observer.h"


namespace test_tetengo2 { namespace gui
{
    // functions

    boost::unit_test::test_suite* suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui");

#if defined(_WIN32)
        p_suite->add(win32::suite());
#endif

        p_suite->add(gui_factory::suite());
        p_suite->add(paint_observer::suite());
        p_suite->add(window_observer::suite());

        return p_suite;
    }


}}

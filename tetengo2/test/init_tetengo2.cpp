/*! \file
    \brief Test of namespace tetengo2.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.test.h"

//#include <boost/test/unit_test.hpp>

#include "init_tetengo2.h"
#include "init_tetengo2.gui.h"
#if defined(_WIN32)
#include "init_tetengo2.win32.h"
#endif
#include "test_tetengo2.generator.h"


namespace test_tetengo2
{
    // functions

    boost::unit_test::test_suite* suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2");

        p_suite->add(gui::suite());
#if defined(_WIN32)
        p_suite->add(win32::suite());
#endif

        p_suite->add(generator::suite());

        return p_suite;
    }


}

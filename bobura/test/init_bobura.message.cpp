/*! \file
    \brief Test of namespace bobura::message.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "init_bobura.message.h"
#include "test_bobura.message.main_window_menu_observer.h"
#include "test_bobura.message.main_window_paint_observer.h"
#include "test_bobura.message.main_window_window_observer.h"


namespace test_bobura { namespace message
{
    // functions

    boost::unit_test::test_suite* suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::message");

        p_suite->add(main_window_menu_observer::suite());
        p_suite->add(main_window_paint_observer::suite());
        p_suite->add(main_window_window_observer::suite());

        return p_suite;
    }


}}

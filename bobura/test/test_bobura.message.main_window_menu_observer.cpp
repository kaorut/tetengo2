/*! \file
    \brief Test of class bobura::message::main_window_menu_observer.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "bobura.message.main_window_menu_observer.h"

#include "test_bobura.message.main_window_menu_observer.h"


namespace test_bobura { namespace message
{
    // functions

    boost::unit_test::test_suite* main_window_menu_observer::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE(
                "test_bobura::message::main_window_menu_observer"
            );

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(selected));

        return p_suite;
    }

    void main_window_menu_observer::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void main_window_menu_observer::selected()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}

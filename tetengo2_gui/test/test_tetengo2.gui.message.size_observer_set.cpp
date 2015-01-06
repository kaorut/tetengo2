/*! \file
    \brief Test of class tetengo2::gui::message::size_observer_set.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>


namespace
{
    // types

    using size_observer_set_type = tetengo2::gui::message::size_observer_set;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(size_observer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(resized)
    {
        BOOST_TEST_PASSPOINT();

        {
            const size_observer_set_type observer_set{};

            observer_set.resized();
        }
        {
            size_observer_set_type observer_set{};

            observer_set.resized();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

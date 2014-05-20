/*! \file
    \brief Test of class tetengo2::gui::message::focus_observer_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using focus_observer_set_type =
        boost::mpl::at<
            test_tetengo2::gui::observer_set_type_list, test_tetengo2::gui::type::observer_set::focus_observer_set
        >::type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(focus_observer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(got_focus)
    {
        BOOST_TEST_PASSPOINT();

        {
            const focus_observer_set_type observer_set{};

            observer_set.got_focus();
        }
        {
            focus_observer_set_type observer_set{};

            observer_set.got_focus();
        }
    }

    BOOST_AUTO_TEST_CASE(lost_focus)
    {
        BOOST_TEST_PASSPOINT();

        {
            const focus_observer_set_type observer_set{};

            observer_set.lost_focus();
        }
        {
            focus_observer_set_type observer_set{};

            observer_set.lost_focus();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

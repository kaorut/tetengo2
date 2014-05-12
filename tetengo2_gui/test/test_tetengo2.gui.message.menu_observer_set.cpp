/*! \file
    \brief Test of class tetengo2::gui::message::menu_observer_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using menu_observer_set_type =
        boost::mpl::at<
            test_tetengo2::gui::observer_set_type_list, test_tetengo2::gui::type::observer_set::menu_observer_set
        >::type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(menu_observer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(selected)
    {
        BOOST_TEST_PASSPOINT();

        {
            const menu_observer_set_type observer_set;

            observer_set.selected();
        }
        {
            menu_observer_set_type observer_set;

            observer_set.selected();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

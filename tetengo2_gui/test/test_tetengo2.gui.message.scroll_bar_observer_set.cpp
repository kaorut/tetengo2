/*! \file
    \brief Test of class tetengo2::gui::message::scroll_bar_observer_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::detail_type_list<test_tetengo2::gui::detail_kind::stub>;

    using type_list_type = test_tetengo2::gui::type_list<detail_type_list_type>;

    using scroll_bar_observer_set_type =
        tetengo2::gui::message::scroll_bar_observer_set<
            boost::mpl::at<type_list_type, test_tetengo2::gui::type::size>::type
        >;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(scroll_bar_observer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(scrolling)
    {
        BOOST_TEST_PASSPOINT();

        {
            const scroll_bar_observer_set_type observer_set{};

            observer_set.scrolling();
        }
        {
            scroll_bar_observer_set_type observer_set{};

            observer_set.scrolling();
        }
    }

    BOOST_AUTO_TEST_CASE(scrolled)
    {
        BOOST_TEST_PASSPOINT();

        {
            const scroll_bar_observer_set_type observer_set{};

            observer_set.scrolled();
        }
        {
            scroll_bar_observer_set_type observer_set{};

            observer_set.scrolled();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

/*! \file
    \brief Test of class tetengo2::gui::message::mouse_observer_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::detail_type_list_for_test;

    using type_list_type = test_tetengo2::gui::type_list<detail_type_list_type>;

    using mouse_observer_set_type =
        tetengo2::gui::message::mouse_observer_set<
            boost::mpl::at<type_list_type, test_tetengo2::gui::type::position>::type,
            boost::mpl::at<type_list_type, test_tetengo2::gui::type::difference>::type
        >;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(mouse_observer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(clicked)
    {
        BOOST_TEST_PASSPOINT();

        {
            const mouse_observer_set_type observer_set{};

            observer_set.clicked();
        }
        {
            mouse_observer_set_type observer_set{};

            observer_set.clicked();
        }
    }

    BOOST_AUTO_TEST_CASE(doubleclicked)
    {
        BOOST_TEST_PASSPOINT();

        {
            const mouse_observer_set_type observer_set{};

            observer_set.doubleclicked();
        }
        {
            mouse_observer_set_type observer_set{};

            observer_set.doubleclicked();
        }
    }

    BOOST_AUTO_TEST_CASE(pressed)
    {
        BOOST_TEST_PASSPOINT();

        {
            const mouse_observer_set_type observer_set{};

            observer_set.pressed();
        }
        {
            mouse_observer_set_type observer_set{};

            observer_set.pressed();
        }
    }

    BOOST_AUTO_TEST_CASE(released)
    {
        BOOST_TEST_PASSPOINT();

        {
            const mouse_observer_set_type observer_set{};

            observer_set.released();
        }
        {
            mouse_observer_set_type observer_set{};

            observer_set.released();
        }
    }

    BOOST_AUTO_TEST_CASE(moved)
    {
        BOOST_TEST_PASSPOINT();

        {
            const mouse_observer_set_type observer_set{};

            observer_set.moved();
        }
        {
            mouse_observer_set_type observer_set{};

            observer_set.moved();
        }
    }

    BOOST_AUTO_TEST_CASE(wheeled)
    {
        BOOST_TEST_PASSPOINT();

        {
            const mouse_observer_set_type observer_set{};

            observer_set.wheeled();
        }
        {
            mouse_observer_set_type observer_set{};

            observer_set.clicked();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

/*! \file
    \brief Test of class tetengo2::gui::message::paint_observer_set.

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

    using drawing_details_type =
        boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::drawing>::type;

    using canvas_traits_type =
        tetengo2::gui::drawing::canvas_traits<
            boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::size>::type,
            boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::size>::type,
            boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type,
            boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::path>::type,
            boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::position>::type,
            boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::dimension>::type,
            boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::ui_encoder>::type
        >;

    using canvas_type =
        tetengo2::gui::drawing::canvas<
            canvas_traits_type,
            drawing_details_type,
            boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::icon>::type
        >;

    using paint_observer_set_type = tetengo2::gui::message::paint_observer_set<canvas_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(paint_observer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(paint_background)
    {
        BOOST_TEST_PASSPOINT();

        {
            const paint_observer_set_type observer_set{};

            observer_set.paint_background();
        }
        {
            paint_observer_set_type observer_set{};

            observer_set.paint_background();
        }
    }

    BOOST_AUTO_TEST_CASE(paint)
    {
        BOOST_TEST_PASSPOINT();

        {
            const paint_observer_set_type observer_set{};

            observer_set.paint();
        }
        {
            paint_observer_set_type observer_set{};

            observer_set.paint();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

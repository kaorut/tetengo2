/*! \file
    \brief Test of class tetengo2::gui::drawing::widget_canvas.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

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

    using drawing_details_type =
        boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::drawing>::type;

    using canvas_type =
        tetengo2::gui::drawing::widget_canvas<
            canvas_traits_type,
            drawing_details_type,
            boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::icon>::type
        >;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(widget_canvas)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const canvas_type canvas{ 42 };
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

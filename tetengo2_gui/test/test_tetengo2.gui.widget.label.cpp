/*! \file
    \brief Test of class tetengo2::gui::widget::label.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.gui.h>
#include "tetengo2.text.h"

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using window_type =
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type;

    using dimension_type = boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::dimension>::type;

    using width_type = tetengo2::gui::dimension<dimension_type>::width_type;

    using string_type = boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type;

    using label_type =
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::label>::type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(label)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const label_type label(parent);
    }

    BOOST_AUTO_TEST_CASE(fit_to_content)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        label_type label(parent);
        label.set_text(string_type(TETENGO2_TEXT("Tetengo")));

        label.fit_to_content();

        const auto dimension = label.dimension();

        const auto answer_dimension =
            label.create_canvas()->calc_text_dimension(string_type(TETENGO2_TEXT("Tetengo")));
        BOOST_CHECK(dimension == answer_dimension);
    }

    BOOST_AUTO_TEST_CASE(fit_to_content_O_max_width)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        label_type label(parent);
        label.set_text(string_type(TETENGO2_TEXT("Tetengo")));

        label.fit_to_content(width_type(42));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

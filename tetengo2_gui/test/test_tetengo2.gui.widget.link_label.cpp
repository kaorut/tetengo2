/*! \file
    \brief Test of class tetengo2::gui::widget::link_label.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.text.h"

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type string_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type
        window_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::link_label>::type
        link_label_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(link_label)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const link_label_type label(parent);
    }

    BOOST_AUTO_TEST_CASE(target)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const link_label_type label(parent);

        BOOST_CHECK(label.target().empty());
    }

    BOOST_AUTO_TEST_CASE(set_target)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        link_label_type label(parent);

        label.set_target(string_type(TETENGO2_TEXT("http://www.tetengo.org")));

        BOOST_CHECK(label.target() == string_type(TETENGO2_TEXT("http://www.tetengo.org")));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

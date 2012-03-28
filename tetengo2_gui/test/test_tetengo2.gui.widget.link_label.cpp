/*! \file
    \brief Test of class tetengo2::gui::widget::link_label.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>
//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_tetengo2::gui::widget_type_list,
            test_tetengo2::gui::type::widget::window
        >::type
        window_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::widget_type_list,
            test_tetengo2::gui::type::widget::link_label
        >::type
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


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

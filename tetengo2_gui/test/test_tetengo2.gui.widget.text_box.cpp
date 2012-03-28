/*! \file
    \brief Test of class tetengo2::gui::widget::text_box.

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
            test_tetengo2::gui::type::widget::text_box
        >::type
        text_box_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(text_box)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const text_box_type text_box(parent);
    }

    BOOST_AUTO_TEST_CASE(read_only)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const text_box_type text_box(parent);

        BOOST_CHECK(!text_box.read_only());
    }

    BOOST_AUTO_TEST_CASE(set_read_only)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            text_box_type text_box(parent);

            text_box.set_read_only(false);

            BOOST_CHECK(!text_box.read_only());
        }
        {
            window_type parent;
            text_box_type text_box(parent);

            text_box.set_read_only(true);

            BOOST_CHECK(text_box.read_only());
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

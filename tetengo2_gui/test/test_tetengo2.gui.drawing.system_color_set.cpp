/*! \file
    \brief Test of class tetengo2::gui::drawing::system_color_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_tetengo2::gui::drawing_type_list,
            test_tetengo2::gui::type::drawing::system_color_set
        >::type
        system_color_set_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(system_color_set)
    // test cases

    BOOST_AUTO_TEST_CASE(dialog_background)
    {
        BOOST_TEST_PASSPOINT();

        system_color_set_type::dialog_background();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

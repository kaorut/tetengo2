/*! \file
    \brief Test of class tetengo2::gui::menu::popup.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <string>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_tetengo2::gui::menu_type_list,
            test_tetengo2::gui::type::menu::menu_details
        >::type
        menu_details_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::menu_type_list,
            test_tetengo2::gui::type::menu::popup
        >::type
        popup_menu_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu)
BOOST_AUTO_TEST_SUITE(popup)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const popup_menu_type popup_menu("Tetengo");
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        const popup_menu_type popup_menu("Tetengo");

        BOOST_CHECK(
            &popup_menu.style() == &menu_details_type::popup_menu_style()
        );
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

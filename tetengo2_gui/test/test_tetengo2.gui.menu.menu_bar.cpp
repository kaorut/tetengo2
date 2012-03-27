/*! \file
    \brief Test of class tetengo2::gui::menu::menu_bar.

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
            test_tetengo2::gui::type::menu::menu_bar
        >::type
        menu_bar_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu)
BOOST_AUTO_TEST_SUITE(menu_bar)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const menu_bar_type menu_bar;
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        const menu_bar_type menu_bar;

        BOOST_CHECK(
            &menu_bar.style() == &menu_details_type::menu_bar_style()
        );
    }

    BOOST_AUTO_TEST_CASE(shortcut_key_table)
    {
        BOOST_TEST_PASSPOINT();
    
        const menu_bar_type menu_bar;

        menu_bar.shortcut_key_table();
    }

    BOOST_AUTO_TEST_CASE(update_shortcut_key_table)
    {
        BOOST_TEST_PASSPOINT();
    
        menu_bar_type menu_bar;

        menu_bar.update_shortcut_key_table();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

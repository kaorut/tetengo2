/*! \file
    \brief Test of class bobura::about_dialog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type
        window_type;

    typedef
        boost::mpl::at<
            bobura::locale_type_list, bobura::type::locale::message_catalog
        >::type
        message_catalog_type;

    typedef
        boost::mpl::at<bobura::common_type_list, bobura::type::string>::type
        string_type;

    typedef
        boost::mpl::at<bobura::common_type_list, bobura::type::path>::type
        path_type;

    typedef
        boost::mpl::at<bobura::common_type_list, bobura::type::settings>::type
        settings_type;

    typedef
        boost::mpl::at<
            bobura::dialog_type_list, bobura::type::dialog::about_dialog
        >::type
        about_dialog_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(about_dialog)
    // test cases

#if __CYGWIN__ && __GNUC__ == 4 && __GNUC_MINOR__ == 5 && __GNUC_PATCHLEVEL__ == 3
#   warning "Somehow this test case does not compile in a certain environment."
#else
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        std::vector<string_type> arguments;
        path_type path;
        const settings_type settings(std::move(arguments), std::move(path));
        const about_dialog_type about_dialog(
            window, message_catalog, settings
        );
    }
#endif

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

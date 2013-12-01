/*! \file
    \brief Test of class bobura::property_bar.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <vector>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::setting_type_list, bobura::type::setting::settings>::type settings_type;

    typedef boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type message_catalog_type;

    typedef
        boost::mpl::at<bobura::main_window_type_list, bobura::type::main_window::property_bar>::type property_bar_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(property_bar)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        std::vector<string_type> arguments;
        arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
        settings_type settings(arguments);
        const message_catalog_type message_catalog;
        const property_bar_type property_bar(window, settings, message_catalog);
    }

    BOOST_AUTO_TEST_CASE(map_box)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type window;
            std::vector<string_type> arguments;
            arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
            settings_type settings(arguments);
            const message_catalog_type message_catalog;
            const property_bar_type property_bar(window, settings, message_catalog);

            property_bar.map_box();
        }
        {
            window_type window;
            std::vector<string_type> arguments;
            arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
            settings_type settings(arguments);
            const message_catalog_type message_catalog;
            property_bar_type property_bar(window, settings, message_catalog);

            property_bar.map_box();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

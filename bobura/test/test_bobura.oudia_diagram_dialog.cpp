/*! \file
    \brief Test of class bobura::oudia_diagram_dialog.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include <stdexcept>
#include <utility>
#include <vector>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

#include "bobura.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type message_catalog_type;

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef
        boost::mpl::at<bobura::dialog_type_list, bobura::type::dialog::oudia_diagram_dialog>::type
        oudia_diagram_dialog_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(oudia_diagram_dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const oudia_diagram_dialog_type oudia_diagram_dialog(window, message_catalog);
    }

    BOOST_AUTO_TEST_CASE(names)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const oudia_diagram_dialog_type oudia_diagram_dialog(window, message_catalog);

        BOOST_CHECK(oudia_diagram_dialog.names().empty());
    }

    BOOST_AUTO_TEST_CASE(set_names)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        oudia_diagram_dialog_type oudia_diagram_dialog(window, message_catalog);

        std::vector<string_type> names;
        names.push_back(string_type(TETENGO2_TEXT("hoge")));
        names.push_back(string_type(TETENGO2_TEXT("fuga")));
        names.push_back(string_type(TETENGO2_TEXT("piyo")));
        oudia_diagram_dialog.set_names(std::move(names));

        BOOST_REQUIRE_EQUAL(oudia_diagram_dialog.names().size(), 3U);
        BOOST_CHECK(oudia_diagram_dialog.names()[0] == string_type(TETENGO2_TEXT("hoge")));
        BOOST_CHECK(oudia_diagram_dialog.names()[1] == string_type(TETENGO2_TEXT("fuga")));
        BOOST_CHECK(oudia_diagram_dialog.names()[2] == string_type(TETENGO2_TEXT("piyo")));
    }

    BOOST_AUTO_TEST_CASE(selected_index)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const oudia_diagram_dialog_type oudia_diagram_dialog(window, message_catalog);

        BOOST_CHECK(!oudia_diagram_dialog.selected_index());
    }

    BOOST_AUTO_TEST_CASE(set_selected_index)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type window;
            const message_catalog_type message_catalog;
            oudia_diagram_dialog_type oudia_diagram_dialog(window, message_catalog);

            BOOST_CHECK_THROW(oudia_diagram_dialog.set_selected_index(0), std::out_of_range);
        }
        {
            window_type window;
            const message_catalog_type message_catalog;
            oudia_diagram_dialog_type oudia_diagram_dialog(window, message_catalog);

            std::vector<string_type> names;
            names.push_back(string_type(TETENGO2_TEXT("hoge")));
            names.push_back(string_type(TETENGO2_TEXT("fuga")));
            names.push_back(string_type(TETENGO2_TEXT("piyo")));
            oudia_diagram_dialog.set_names(std::move(names));

            oudia_diagram_dialog.set_selected_index(1);

            BOOST_REQUIRE(oudia_diagram_dialog.selected_index());
            BOOST_CHECK_EQUAL(*oudia_diagram_dialog.selected_index(), 1U);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

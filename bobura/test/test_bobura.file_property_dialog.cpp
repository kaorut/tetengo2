/*! \file
    \brief Test of class bobura::file_property_dialog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

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
        boost::mpl::at<bobura::dialog_type_list, bobura::type::dialog::file_property_dialog>::type
        file_property_dialog_type;


}


#if defined(__GNUC__) && defined(SKIP_COMPILATION)
#   warning Skipped the compilation to avoid errors.
#else
BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(file_property_dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const file_property_dialog_type file_property_dialog(window, message_catalog);
    }

    BOOST_AUTO_TEST_CASE(company_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const file_property_dialog_type file_property_dialog(window, message_catalog);

        BOOST_CHECK(file_property_dialog.company_name().empty());
    }

    BOOST_AUTO_TEST_CASE(set_company_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        file_property_dialog_type file_property_dialog(window, message_catalog);

        file_property_dialog.set_company_name(string_type(TETENGO2_TEXT("hoge")));

        BOOST_CHECK(file_property_dialog.company_name() == string_type(TETENGO2_TEXT("hoge")));
    }

    BOOST_AUTO_TEST_CASE(note)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const file_property_dialog_type file_property_dialog(window, message_catalog);

        BOOST_CHECK(file_property_dialog.note().empty());
    }

    BOOST_AUTO_TEST_CASE(set_note)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        file_property_dialog_type file_property_dialog(window, message_catalog);

        file_property_dialog.set_note(string_type(TETENGO2_TEXT("hoge")));

        BOOST_CHECK(file_property_dialog.note() == string_type(TETENGO2_TEXT("hoge")));
    }

    BOOST_AUTO_TEST_CASE(line_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const file_property_dialog_type file_property_dialog(window, message_catalog);

        BOOST_CHECK(file_property_dialog.line_name().empty());
    }

    BOOST_AUTO_TEST_CASE(set_line_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        file_property_dialog_type file_property_dialog(window, message_catalog);

        file_property_dialog.set_line_name(string_type(TETENGO2_TEXT("hoge")));

        BOOST_CHECK(file_property_dialog.line_name() == string_type(TETENGO2_TEXT("hoge")));
    }

    BOOST_AUTO_TEST_CASE(file_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const file_property_dialog_type file_property_dialog(window, message_catalog);

        BOOST_CHECK(file_property_dialog.file_name().empty());
    }

    BOOST_AUTO_TEST_CASE(set_file_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        file_property_dialog_type file_property_dialog(window, message_catalog);

        file_property_dialog.set_file_name(string_type(TETENGO2_TEXT("hoge")));

        BOOST_CHECK(file_property_dialog.file_name() == string_type(TETENGO2_TEXT("hoge")));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif

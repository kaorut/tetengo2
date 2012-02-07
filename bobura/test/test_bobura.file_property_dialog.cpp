/*! \file
    \brief Test of class bobura::file_property_dialog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "test_bobura.types.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(file_property_dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const file_property_dialog_type file_property_dialog(
            window, message_catalog
        );
    }

    BOOST_AUTO_TEST_CASE(line_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const file_property_dialog_type file_property_dialog(
            window, message_catalog
        );

        BOOST_CHECK(file_property_dialog.line_name().empty());
    }

    BOOST_AUTO_TEST_CASE(set_line_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        file_property_dialog_type file_property_dialog(
            window, message_catalog
        );

        file_property_dialog.set_line_name(L"hoge");

        BOOST_CHECK(file_property_dialog.line_name() == L"hoge");
    }

    BOOST_AUTO_TEST_CASE(file_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const file_property_dialog_type file_property_dialog(
            window, message_catalog
        );

        BOOST_CHECK(file_property_dialog.file_name().empty());
    }

    BOOST_AUTO_TEST_CASE(set_file_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        file_property_dialog_type file_property_dialog(
            window, message_catalog
        );

        file_property_dialog.set_file_name(L"hoge");

        BOOST_CHECK(file_property_dialog.file_name() == L"hoge");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

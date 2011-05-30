/*! \file
    \brief Test of class bobura::command::about.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <string>
//#include <utility>
//#include <vector>

//#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "test_bobura.types.h"

#include "bobura.command.about.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(about)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const message_catalog_type message_catalog;
        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        const bobura::command::about<about_dialog_type> about(
            parent, message_catalog, settings
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const message_catalog_type message_catalog;
        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        bobura::command::about<about_dialog_type> about(
            parent, message_catalog, settings
        );

        about();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

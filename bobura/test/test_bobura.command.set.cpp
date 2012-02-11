/*! \file
    \brief Test of class bobura::command::set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <string>
//#include <utility>
//#include <vector>

//#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "test_bobura.types.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(set)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        reader_type reader;
        const message_catalog_type message_catalog;
        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        const confirm_file_save_type confirm_file_save(model);
        main_window_type main_window(
            message_catalog, settings, confirm_file_save
        );
        const command_set_type command_set(
            model, reader, main_window, settings, message_catalog
        );
    }

    BOOST_AUTO_TEST_CASE(members)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        reader_type reader;
        const message_catalog_type message_catalog;
        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        const confirm_file_save_type confirm_file_save(model);
        main_window_type main_window(
            message_catalog, settings, confirm_file_save
        );
        const command_set_type command_set(
            model, reader, main_window, settings, message_catalog
        );

        command_set.about();
        command_set.exit();
        command_set.load_from_file();
        command_set.nop();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

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
        const message_catalog_type message_catalog;
        writer_type writer;
        const save_to_file_type save_to_file(false, writer, message_catalog);
        const save_to_file_type ask_file_path_and_save_to_file(
            true, writer, message_catalog
        );
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        reader_type reader;
        const load_from_file_type load_from_file(
            confirm_file_save, reader, message_catalog
        );
        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        const command_set_type command_set(
            confirm_file_save,
            load_from_file,
            save_to_file,
            ask_file_path_and_save_to_file,
            settings,
            message_catalog
        );
    }

    BOOST_AUTO_TEST_CASE(members)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        const message_catalog_type message_catalog;
        writer_type writer;
        const save_to_file_type save_to_file(false, writer, message_catalog);
        const save_to_file_type ask_file_path_and_save_to_file(
            true, writer, message_catalog
        );
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        reader_type reader;
        const load_from_file_type load_from_file(
            confirm_file_save, reader, message_catalog
        );
        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        const command_set_type command_set(
            confirm_file_save,
            load_from_file,
            save_to_file,
            ask_file_path_and_save_to_file,
            settings,
            message_catalog
        );

        command_set.about();
        command_set.exit();
        command_set.file_property();
        command_set.load_from_file();
        command_set.new_file();
        command_set.nop();
        command_set.save_to_file();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

/*! \file
    \brief Test of class bobura::message::timetable_model.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <string>
//#include <utility>
//#include <vector>

//#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "test_bobura.types.h"

#include "bobura.message.timetable_model.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(timetable_model)
BOOST_AUTO_TEST_SUITE(reset)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        writer_type writer;
        const save_to_file_type save_to_file(false, writer, message_catalog);
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        main_window_type main_window(
            message_catalog, settings, confirm_file_save
        );
        const bobura::message::timetable_model::reset<
            model_type, main_window_type
        > observer(model, main_window);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        writer_type writer;
        const save_to_file_type save_to_file(false, writer, message_catalog);
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        main_window_type main_window(
            message_catalog, settings, confirm_file_save
        );
        const bobura::message::timetable_model::reset<
            model_type, main_window_type
        > observer(model, main_window);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(changed)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        writer_type writer;
        const save_to_file_type save_to_file(false, writer, message_catalog);
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        main_window_type main_window(
            message_catalog, settings, confirm_file_save
        );
        const bobura::message::timetable_model::changed<
            model_type, main_window_type
        >
        observer(model, main_window);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        writer_type writer;
        const save_to_file_type save_to_file(false, writer, message_catalog);
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        main_window_type main_window(
            message_catalog, settings, confirm_file_save
        );
        const bobura::message::timetable_model::changed<
            model_type, main_window_type
        > observer(model, main_window);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

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

        const message_catalog_type message_catalog;
        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        main_window_type main_window(message_catalog, settings);
        const bobura::message::timetable_model::reset<
            timetable_type, boost::filesystem::path, main_window_type
        > observer(main_window);
    }

    BOOST_AUTO_TEST_CASE(clicked)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog;
        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        main_window_type main_window(message_catalog, settings);
        const bobura::message::timetable_model::reset<
            timetable_type, boost::filesystem::path, main_window_type
        > observer(main_window);

        const timetable_type timetable(L"hoge");
        observer(timetable, boost::filesystem::path());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(changed)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog;
        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        main_window_type main_window(message_catalog, settings);
        const bobura::message::timetable_model::changed<main_window_type>
        observer(main_window);
    }

    BOOST_AUTO_TEST_CASE(clicked)
    {
        BOOST_TEST_PASSPOINT();

        {
            const message_catalog_type message_catalog;
            std::vector<std::wstring> arguments;
            boost::filesystem::path path;
            const settings_type settings(std::move(arguments), std::move(path));
            main_window_type main_window(message_catalog, settings);
            const bobura::message::timetable_model::changed<main_window_type>
            observer(main_window);

            observer(false);
        }
        {
            const message_catalog_type message_catalog;
            std::vector<std::wstring> arguments;
            boost::filesystem::path path;
            const settings_type settings(std::move(arguments), std::move(path));
            main_window_type main_window(message_catalog, settings);
            const bobura::message::timetable_model::changed<main_window_type>
            observer(main_window);

            observer(true);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

/*! \file
    \brief Test of class bobura::main_window.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <string>
//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            bobura::locale_type_list, bobura::type::locale::message_catalog
        >::type
        message_catalog_type;

    typedef
        boost::mpl::at<bobura::common_type_list, bobura::type::path>::type
        path_type;

    typedef
        boost::mpl::at<bobura::common_type_list, bobura::type::settings>::type
        settings_type;

    typedef
        boost::mpl::at<
            bobura::model_type_list, bobura::type::model::model
        >::type
        model_type;

    typedef
        boost::mpl::at<
            bobura::model_type_list, bobura::type::model::writer
        >::type
        writer_type;

    typedef
        boost::mpl::at<
            bobura::load_save_type_list, bobura::type::load_save::save_to_file
        >::type
        save_to_file_type;

    typedef
        boost::mpl::at<
            bobura::load_save_type_list,
            bobura::type::load_save::confirm_file_save
        >::type
        confirm_file_save_type;

    typedef
        boost::mpl::at<
            bobura::main_window_type_list,
            bobura::type::main_window::main_window
        >::type
        main_window_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(main_window)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog;
        std::vector<std::wstring> arguments;
        path_type path;
        const settings_type settings(std::move(arguments), std::move(path));
        model_type model;
        writer_type writer;
        const save_to_file_type save_to_file(false, writer, message_catalog);
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        const main_window_type main_window(
            message_catalog, settings, confirm_file_save
        );
    }

    BOOST_AUTO_TEST_CASE(set_title)
    {
        BOOST_TEST_PASSPOINT();

        {
            const message_catalog_type message_catalog;
            std::vector<std::wstring> arguments;
            path_type path;
            const settings_type settings(std::move(arguments), std::move(path));
            model_type model;
            writer_type writer;
            const save_to_file_type save_to_file(
                false, writer, message_catalog
            );
            const confirm_file_save_type confirm_file_save(
                model, save_to_file, message_catalog
            );
            main_window_type main_window(
                message_catalog, settings, confirm_file_save
            );

            main_window.set_title(boost::none, false);
        }
        {
            const message_catalog_type message_catalog;
            std::vector<std::wstring> arguments;
            path_type path;
            const settings_type settings(
                std::move(arguments), std::move(path)
            );
            model_type model;
            writer_type writer;
            const save_to_file_type save_to_file(
                false, writer, message_catalog
            );
            const confirm_file_save_type confirm_file_save(
                model, save_to_file, message_catalog
            );
            main_window_type main_window(
                message_catalog, settings, confirm_file_save
            );

            main_window.set_title(boost::none, true);
        }
        {
            const message_catalog_type message_catalog;
            std::vector<std::wstring> arguments;
            path_type path;
            const settings_type settings(
                std::move(arguments), std::move(path)
            );
            model_type model;
            writer_type writer;
            const save_to_file_type save_to_file(
                false, writer, message_catalog
            );
            const confirm_file_save_type confirm_file_save(
                model, save_to_file, message_catalog
            );
            main_window_type main_window(
                message_catalog, settings, confirm_file_save
            );

            main_window.set_title(
                boost::make_optional<std::wstring>(L"hoge"), false
            );

            BOOST_CHECK(
                main_window.text().find(L"hoge") != std::wstring::npos
            );
        }
        {
            const message_catalog_type message_catalog;
            std::vector<std::wstring> arguments;
            path_type path;
            const settings_type settings(
                std::move(arguments), std::move(path)
            );
            model_type model;
            writer_type writer;
            const save_to_file_type save_to_file(
                false, writer, message_catalog
            );
            const confirm_file_save_type confirm_file_save(
                model, save_to_file, message_catalog
            );
            main_window_type main_window(
                message_catalog, settings, confirm_file_save
            );

            main_window.set_title(
                boost::make_optional<std::wstring>(L"hoge"), true
            );

            BOOST_CHECK(
                main_window.text().find(L"hoge") != std::wstring::npos
            );
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

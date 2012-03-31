/*! \file
    \brief Test of class bobura::main_window.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

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
        boost::mpl::at<bobura::common_type_list, bobura::type::string>::type
        string_type;

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
        std::vector<string_type> arguments;
        path_type path;
        const settings_type settings(std::move(arguments), std::move(path));
        model_type model;
        const save_to_file_type save_to_file(false, message_catalog);
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        const main_window_type main_window(
            message_catalog, settings, confirm_file_save
        );
    }

#if defined(__GNUC__) && defined(SKIP_COMPILATION)
#   warning Skipped the compilation to avoid errors.
#else
    BOOST_AUTO_TEST_CASE(set_title)
    {
        BOOST_TEST_PASSPOINT();

        {
            const message_catalog_type message_catalog;
            std::vector<string_type> arguments;
            path_type path;
            const settings_type settings(
                std::move(arguments), std::move(path)
            );
            model_type model;
            const save_to_file_type save_to_file(false, message_catalog);
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
            std::vector<string_type> arguments;
            path_type path;
            const settings_type settings(
                std::move(arguments), std::move(path)
            );
            model_type model;
            const save_to_file_type save_to_file(false, message_catalog);
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
            std::vector<string_type> arguments;
            path_type path;
            const settings_type settings(
                std::move(arguments), std::move(path)
            );
            model_type model;
            const save_to_file_type save_to_file(false, message_catalog);
            const confirm_file_save_type confirm_file_save(
                model, save_to_file, message_catalog
            );
            main_window_type main_window(
                message_catalog, settings, confirm_file_save
            );

            main_window.set_title(
                boost::make_optional<string_type>(
                    string_type(TETENGO2_TEXT("hoge"))
                ),
                false
            );

            BOOST_CHECK(
                main_window.text().find(string_type(TETENGO2_TEXT("hoge"))) !=
                string_type::npos
            );
        }
        {
            const message_catalog_type message_catalog;
            std::vector<string_type> arguments;
            path_type path;
            const settings_type settings(
                std::move(arguments), std::move(path)
            );
            model_type model;
            const save_to_file_type save_to_file(false, message_catalog);
            const confirm_file_save_type confirm_file_save(
                model, save_to_file, message_catalog
            );
            main_window_type main_window(
                message_catalog, settings, confirm_file_save
            );

            main_window.set_title(
                boost::make_optional<string_type>(
                    string_type(TETENGO2_TEXT("hoge"))
                ),
                true
            );

            BOOST_CHECK(
                main_window.text().find(string_type(TETENGO2_TEXT("hoge"))) !=
                string_type::npos
            );
        }
    }
#endif

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

/*! \file
    \brief Test of class bobura::message::timetable_model.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"

#include "bobura.message.timetable_model.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type message_catalog_type;

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::path>::type path_type;

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::settings>::type settings_type;

    typedef boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::save_to_file>::type save_to_file_type;

    typedef
        boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::confirm_file_save>::type
        confirm_file_save_type;

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef
        boost::mpl::at<bobura::main_window_type_list, bobura::type::main_window::main_window>::type main_window_type;


}


#if defined(__GNUC__) && defined(SKIP_COMPILATION)
#   warning Skipped the compilation to avoid errors.
#else
BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(timetable_model)
BOOST_AUTO_TEST_SUITE(reset)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        const message_catalog_type message_catalog;
        std::vector<string_type> arguments;
        path_type path;
        const settings_type settings(std::move(arguments), std::move(path));
        const save_to_file_type save_to_file(false, message_catalog);
        const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
        main_window_type main_window(message_catalog, settings, confirm_file_save);
        const bobura::message::timetable_model::reset<model_type, main_window_type> observer(model, main_window);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        const message_catalog_type message_catalog;
        std::vector<string_type> arguments;
        path_type path;
        const settings_type settings(std::move(arguments), std::move(path));
        const save_to_file_type save_to_file(false, message_catalog);
        const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
        main_window_type main_window(message_catalog, settings, confirm_file_save);
        const bobura::message::timetable_model::reset<model_type, main_window_type> observer(model, main_window);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(changed)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        const message_catalog_type message_catalog;
        std::vector<string_type> arguments;
        path_type path;
        const settings_type settings(std::move(arguments), std::move(path));
        const save_to_file_type save_to_file(false, message_catalog);
        const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
        main_window_type main_window(message_catalog, settings, confirm_file_save);
        const bobura::message::timetable_model::changed<model_type, main_window_type> observer(model, main_window);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        const message_catalog_type message_catalog;
        std::vector<string_type> arguments;
        path_type path;
        const settings_type settings(std::move(arguments), std::move(path));
        const save_to_file_type save_to_file(false, message_catalog);
        const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
        main_window_type main_window(message_catalog, settings, confirm_file_save);
        const bobura::message::timetable_model::changed<model_type, main_window_type> observer(model, main_window);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif

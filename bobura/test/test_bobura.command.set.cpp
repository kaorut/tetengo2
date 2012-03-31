/*! \file
    \brief Test of class bobura::command::set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            bobura::model_type_list, bobura::type::model::model
        >::type
        model_type;

    typedef
        boost::mpl::at<
            bobura::locale_type_list, bobura::type::locale::message_catalog
        >::type
        message_catalog_type;

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
            bobura::load_save_type_list, bobura::type::load_save::new_file
        >::type
        new_file_type;

    typedef
        boost::mpl::at<
            bobura::model_type_list, bobura::type::model::reader
        >::type
        reader_type;

    typedef
        boost::mpl::at<
            bobura::load_save_type_list,
            bobura::type::load_save::load_from_file
        >::type
        load_from_file_type;

    typedef
        boost::mpl::at<bobura::common_type_list, bobura::type::string>::type
        string_type;

    typedef
        boost::mpl::at<bobura::common_type_list, bobura::type::path>::type
        path_type;

    typedef
        boost::mpl::at<bobura::common_type_list, bobura::type::settings>::type
        settings_type;

    typedef
        boost::mpl::at<
            bobura::application_type_list,
            bobura::type::application::command_set
        >::type
        command_set_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(set)
    // test cases

#if defined(__GNUC__) && defined(SKIP_COMPILATION)
#   warning Skipped the compilation to avoid errors.
#else
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, message_catalog);
        const save_to_file_type ask_file_path_and_save_to_file(
            true, message_catalog
        );
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        const new_file_type new_file(confirm_file_save);
        reader_type reader;
        const load_from_file_type load_from_file(
            confirm_file_save, reader, message_catalog
        );
        std::vector<string_type> arguments;
        path_type path;
        const settings_type settings(std::move(arguments), std::move(path));
        const command_set_type command_set(
            new_file,
            load_from_file,
            save_to_file,
            ask_file_path_and_save_to_file,
            settings,
            message_catalog
        );
    }
#endif

#if defined(__GNUC__) && defined(SKIP_COMPILATION)
#   warning Skipped the compilation to avoid errors.
#else
    BOOST_AUTO_TEST_CASE(members)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, message_catalog);
        const save_to_file_type ask_file_path_and_save_to_file(
            true, message_catalog
        );
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        const new_file_type new_file(confirm_file_save);
        reader_type reader;
        const load_from_file_type load_from_file(
            confirm_file_save, reader, message_catalog
        );
        std::vector<string_type> arguments;
        path_type path;
        const settings_type settings(std::move(arguments), std::move(path));
        const command_set_type command_set(
            new_file,
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
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

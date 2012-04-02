/*! \file
    \brief Test of class bobura::command::save_to_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.detail.stub.common_dialog.h>

#include "bobura.type_list.h"

#include "bobura.command.save_to_file.h"


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
            bobura::ui_type_list, bobura::type::ui::abstract_window
        >::type
        abstract_window_type;

    typedef
        boost::mpl::at<
            bobura::load_save_type_list, bobura::type::load_save::save_to_file
        >::type
        save_to_file_type;

    typedef
        boost::mpl::at<
            bobura::locale_type_list, bobura::type::locale::message_catalog
        >::type
        message_catalog_type;

    typedef
        boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type
        window_type;

    typedef
        bobura::command::save_to_file<
            model_type, abstract_window_type, save_to_file_type
        >
        save_to_file_command_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(save_to_file_command)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, message_catalog);
        const save_to_file_command_type save_to_file_command(save_to_file);
    }

#if defined(__GNUC__) && defined(SKIP_COMPILATION)
#   warning Skipped the compilation to avoid errors.
#else
    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, message_catalog);
        const save_to_file_command_type save_to_file_command(save_to_file);

        model_type model;
        window_type parent;
        save_to_file_command(model, parent);

        BOOST_CHECK(boost::filesystem::exists(model.path()));
        boost::filesystem::remove(model.path());
}
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

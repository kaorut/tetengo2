/*! \file
    \brief Test of class bobura::command::load_from_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.detail.stub.common_dialog.h>
#include <tetengo2.gui.common_dialog.file_open.h>

#include "bobura.type_list.h"

#include "bobura.command.load_from_file.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::abstract_window >::type abstract_window_type;

    typedef
        boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::load_from_file>::type load_from_file_type;

    typedef boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type message_catalog_type;

    typedef boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::save_to_file>::type save_to_file_type;

    typedef
        boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::confirm_file_save>::type
        confirm_file_save_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef
        bobura::command::load_from_file<model_type, abstract_window_type, load_from_file_type>
        load_from_file_command_type;


}


#if defined(__GNUC__) && defined(SKIP_COMPILATION)
#   warning Skipped the compilation to avoid errors.
#else
BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(load_from_file)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, message_catalog);
        const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
        const load_from_file_type load_from_file(false, confirm_file_save, message_catalog);
        const load_from_file_command_type load_from_file_command(load_from_file);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif

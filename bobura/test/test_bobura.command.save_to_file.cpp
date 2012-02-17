/*! \file
    \brief Test of class bobura::command::save_to_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.detail.stub.common_dialog.h>

#include "test_bobura.types.h"

#include "bobura.command.save_to_file.h"


namespace
{
    // types

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

        writer_type writer;
        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, writer, message_catalog);
        const save_to_file_command_type save_to_file_command(save_to_file);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        writer_type writer;
        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(
            false, writer, message_catalog
        );
        const save_to_file_command_type save_to_file_command(save_to_file);

        model_type model;
        window_type parent;
        save_to_file_command(model, parent);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

/*! \file
    \brief Test of class bobura::command::load_from_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if __CYGWIN__ && __GNUC__ == 4 && __GNUC_MINOR__ == 5 && __GNUC_PATCHLEVEL__ == 3
#   warning "This file does not compile with g++ 4.5.3 on Cygwin."
#else

#include <boost/test/unit_test.hpp>

#include <tetengo2.detail.stub.common_dialog.h>
#include <tetengo2.gui.common_dialog.file_open.h>

#include "test_bobura.types.h"

#include "bobura.command.load_from_file.h"


namespace
{
    // types

    typedef
        bobura::command::load_from_file<
            model_type, abstract_window_type, load_from_file_type
        >
        load_from_file_command_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(load_from_file)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        writer_type writer;
        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, writer, message_catalog);
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        reader_type reader;
        const load_from_file_type load_from_file(
            confirm_file_save, reader, message_catalog
        );
        const load_from_file_command_type load_from_file_command(
            load_from_file
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        writer_type writer;
        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, writer, message_catalog);
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        reader_type reader;
        const load_from_file_type load_from_file(
            confirm_file_save, reader, message_catalog
        );
        const load_from_file_command_type load_from_file_command(
            load_from_file
        );

        window_type parent;
        load_from_file_command(model, parent);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

#endif

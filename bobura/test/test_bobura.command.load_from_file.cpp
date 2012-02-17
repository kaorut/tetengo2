/*! \file
    \brief Test of class bobura::command::load_from_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

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
            model_type,
            abstract_window_type,
            message_box_type,
            file_open_type,
            confirm_file_save_type,
            reader_type,
            message_catalog_type
        >
        load_from_file_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(load_from_file)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        model_type model;
        const message_catalog_type message_catalog;
        const confirm_file_save_type confirm_file_save(
            model, message_catalog
        );
        reader_type reader;
        const load_from_file_type load_from_file(
            parent, confirm_file_save, model, reader, message_catalog
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        model_type model;
        const message_catalog_type message_catalog;
        const confirm_file_save_type confirm_file_save(
            model, message_catalog
        );
        reader_type reader;
        load_from_file_type load_from_file(
            parent, confirm_file_save, model, reader, message_catalog
        );

        load_from_file(model, parent);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

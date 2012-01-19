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


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(load_from_file)
    // test cases

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        model_type model;
        reader_type reader;
        const message_catalog_type message_catalog;
        bobura::command::load_from_file<
            file_open_type,
            model_type,
            reader_type,
            message_catalog_type
        >
        load_from_file(parent, model, reader, message_catalog);

        load_from_file();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

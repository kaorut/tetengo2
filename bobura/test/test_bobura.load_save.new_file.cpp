/*! \file
    \brief Test of class bobura::load_save::new_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "test_bobura.types.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(load_save)
BOOST_AUTO_TEST_SUITE(new_file)
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
        const new_file_type new_file(confirm_file_save);
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
        const new_file_type new_file(confirm_file_save);

        window_type parent;
        new_file(model, parent);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

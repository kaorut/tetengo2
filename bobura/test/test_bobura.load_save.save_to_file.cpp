/*! \file
    \brief Test of class bobura::load_save::save_to_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.detail.stub.common_dialog.h>

#include "test_bobura.types.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(load_save)
BOOST_AUTO_TEST_SUITE(save_to_file)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        writer_type writer;
        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, writer, message_catalog);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        {
            writer_type writer;
            const message_catalog_type message_catalog;
            const save_to_file_type save_to_file(
                false, writer, message_catalog
            );

            model_type model;
            window_type parent;
            const bool result = save_to_file(model, parent);

            BOOST_CHECK(!result);
        }
        {
            writer_type writer;
            const message_catalog_type message_catalog;
            const save_to_file_type save_to_file(
                false, writer, message_catalog
            );

            model_type model;
            model.set_changed(true);
            window_type parent;
            const bool result = save_to_file(model, parent);

            BOOST_CHECK(result);
        }
        {
            writer_type writer;
            const message_catalog_type message_catalog;
            const save_to_file_type save_to_file(
                true, writer, message_catalog
            );

            model_type model;
            window_type parent;
            const bool result = save_to_file(model, parent);

            BOOST_CHECK(result);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

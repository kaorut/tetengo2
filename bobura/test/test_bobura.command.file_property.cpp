/*! \file
    \brief Test of class bobura::command::file_property.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <string>
//#include <utility>
//#include <vector>

//#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "test_bobura.types.h"

#include "bobura.command.file_property.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(file_property)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const message_catalog_type message_catalog;
        const bobura::command::file_property<file_property_dialog_type>
        file_property(parent, message_catalog);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const message_catalog_type message_catalog;
        bobura::command::file_property<file_property_dialog_type>
        file_property(parent, message_catalog);

        file_property();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

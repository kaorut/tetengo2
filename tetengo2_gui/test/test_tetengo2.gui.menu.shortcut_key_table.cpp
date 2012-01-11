/*! \file
    \brief Test of class tetengo2::gui::menu::shortcut_key_table.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.virtual_key.h"
#include "tetengo2.gui.menu.shortcut_key.h"
#include "tetengo2.gui.virtual_key.h"

#include "tetengo2.gui.menu.shortcut_key_table.h"

namespace
{
    // types

    typedef
        tetengo2::detail::stub::virtual_key<std::string>
        virtual_key_details_type;

    typedef
        tetengo2::gui::virtual_key<virtual_key_details_type> virtual_key_type;

    typedef
        tetengo2::gui::menu::shortcut_key<virtual_key_type>
        shortcut_key_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu)
BOOST_AUTO_TEST_SUITE(shortcut_key_table)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

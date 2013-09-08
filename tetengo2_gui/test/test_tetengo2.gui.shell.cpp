/*! \file
    \brief Test of class tetengo2::gui::shell.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.shell.h"

#include "tetengo2.gui.shell.h"


namespace
{
    // types

    typedef tetengo2::gui::shell<tetengo2::detail::stub::shell> shell_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(shell)
    // test cases

    BOOST_AUTO_TEST_CASE(instance)
    {
        BOOST_TEST_PASSPOINT();

        shell_type::instance();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

/*! \file
    \brief Test of class bobura::command::about.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "bobura.command.about.h"

#include "test_bobura.command.about.h"


namespace test_bobura { namespace command
{
    // functions

    boost::unit_test::test_suite* about::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE(
                "test_bobura::command::about"
            );

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(operator_paren));

        return p_suite;
    }

    void about::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void about::operator_paren()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}

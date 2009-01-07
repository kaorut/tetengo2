/*! \file
    \brief Test of class bobura::command::exit.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "bobura.command.exit.h"

#include "test_bobura.command.exit.h"


namespace test_bobura { namespace command
{
    // functions

    boost::unit_test::test_suite* exit::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE(
                "test_bobura::command::exit"
            );

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(operator_paren));

        return p_suite;
    }

    void exit::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void exit::operator_paren()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}

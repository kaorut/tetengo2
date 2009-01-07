/*! \file
    \brief Test of class bobura::command::nop.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "bobura.command.nop.h"

#include "test_bobura.command.nop.h"


namespace test_bobura { namespace command
{
    // functions

    boost::unit_test::test_suite* nop::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE(
                "test_bobura::command::nop"
            );

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(operator_paren));

        return p_suite;
    }

    void nop::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void nop::operator_paren()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}

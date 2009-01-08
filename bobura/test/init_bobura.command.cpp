/*! \file
    \brief Test of namespace bobura::command.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "init_bobura.command.h"
#include "test_bobura.command.about.h"
#include "test_bobura.command.exit.h"
#include "test_bobura.command.nop.h"


namespace test_bobura { namespace command
{
    // functions

    boost::unit_test::test_suite* suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::command");

        p_suite->add(about::suite());
        p_suite->add(exit::suite());
        p_suite->add(nop::suite());

        return p_suite;
    }


}}

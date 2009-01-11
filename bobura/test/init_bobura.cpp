/*! \file
    \brief Test of namespace bobura.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "init_bobura.h"
#include "init_bobura.command.h"
#include "init_bobura.message.h"
#include "test_bobura.bobura.h"
#include "test_bobura.type_list.h"


namespace test_bobura
{
    // functions

    boost::unit_test::test_suite* suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura");

        p_suite->add(command::suite());
        p_suite->add(message::suite());

        p_suite->add(bobura::suite());
        p_suite->add(type_list::suite());

        return p_suite;
    }


}

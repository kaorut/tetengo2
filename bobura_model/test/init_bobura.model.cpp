/*! \file
    \brief Test of namespace bobura::model.

    Copyright (C) 2007 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "init_bobura.model.h"
#include "test_bobura.model.timetable.h"


namespace test_bobura { namespace model
{
    // functions

    boost::unit_test::test_suite* suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::model");

        p_suite->add(test_bobura::model::timetable::suite());

        return p_suite;
    }


}}

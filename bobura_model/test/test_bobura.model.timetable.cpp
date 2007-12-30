/*! \file
    \brief Test of class bobura::model::timetable.

    Copyright (C) 2007 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "bobura.model.timetable.h"

#include "test_bobura.model.timetable.h"


namespace test_bobura { namespace model
{
    // functions

    boost::unit_test::test_suite* timetable::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::model::timetable");

        p_suite->add(
            BOOST_TEST_CASE(test_bobura::model::timetable::construction)
        );

        return p_suite;
    }

    void timetable::construction()
    {
        
    }

}}

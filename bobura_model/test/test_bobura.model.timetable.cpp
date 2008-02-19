/*! \file
    \brief Test of class bobura::model::timetable.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

#include "bobura.model.timetable.h"

#include "test_bobura.model.timetable.h"


namespace test_bobura { namespace model
{
    // functions

    boost::unit_test::test_suite* timetable::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::model::timetable");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_equal));
        p_suite->add(BOOST_TEST_CASE(p_stations));

        return p_suite;
    }

    void timetable::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void timetable::swap()
    {
        BOOST_WARN("Not implemented.");
    }

    void timetable::operator_assign()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void timetable::operator_equal()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void timetable::p_stations()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}

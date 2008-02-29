/*! \file
    \brief Test of class bobura::model::train_info::time.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.test.h"

//#include <boost/test/unit_test.hpp>

#include "bobura.model.station.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.train_info.time.h"

#include "test_bobura.model.train_info.time.h"


namespace test_bobura { namespace model { namespace train_info
{
    // functions

    boost::unit_test::test_suite* time::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE(
                "test_bobura::model::train_info::time"
            );

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_equal));

        return p_suite;
    }

    void time::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void time::swap()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void time::operator_assign()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void time::operator_equal()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}

/*! \file
    \brief Test of class bobura::model::train.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.test.h"

//#include <boost/test/unit_test.hpp>

#include "bobura.model.station.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.train.h"

#include "test_bobura.model.train.h"


namespace test_bobura { namespace model
{
    // functions

    boost::unit_test::test_suite* train::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE(
                "test_bobura::model::train"
            );

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_equal));

        return p_suite;
    }

    void train::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void train::swap()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void train::operator_assign()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void train::operator_equal()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}

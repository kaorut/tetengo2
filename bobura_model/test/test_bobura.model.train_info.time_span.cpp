/*! \file
    \brief Test of class bobura::model::train_info::time_span.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.test.h"

//#include <boost/test/unit_test.hpp>

#include "bobura.model.train_info.time_span.h"

#include "test_bobura.model.train_info.time_span.h"


namespace test_bobura { namespace model { namespace train_info
{
    // functions

    boost::unit_test::test_suite* time_span::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE(
                "test_bobura::model::train_info::time_span"
            );

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_equal));

        return p_suite;
    }

    void time_span::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void time_span::swap()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void time_span::operator_assign()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void time_span::operator_equal()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}

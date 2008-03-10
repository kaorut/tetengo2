/*! \file
    \brief Test of class bobura::model::train_info::stop.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.test.h"

//#include <boost/test/unit_test.hpp>

#include "bobura.model.train_info.stop.h"

#include "test_bobura.model.train_info.stop.h"


namespace test_bobura { namespace model { namespace train_info
{
    // functions

    boost::unit_test::test_suite* stop::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::model::train_info::stop");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_equal));

        return p_suite;
    }

    void stop::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void stop::swap()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void stop::operator_assign()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void stop::operator_equal()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}

/*! \file
    \brief Test of class tetengo2::concurrent::progressive_future.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <string>
#include <utility>

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(concurrent)
BOOST_AUTO_TEST_SUITE(progressive_future)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            using future_type = tetengo2::concurrent::progressive_future<std::string, int>;

            future_type future1;
            const future_type future2{ std::move(future1) };
        }
        {
            using future_type = tetengo2::concurrent::progressive_future<const std::string&, int>;

            future_type future1;
            const future_type future2{ std::move(future1) };
        }
        {
            using future_type = tetengo2::concurrent::progressive_future<void, int>;

            future_type future1;
            const future_type future2{ std::move(future1) };
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

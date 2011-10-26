/*! \file
    \brief Test of class tetengo2::concurrent::channel.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <queue>

//#include <boost/noncopyable.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.concurrent.channel.h"


namespace
{
    // types

    typedef tetengo2::concurrent::channel<int, std::size_t> channel_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(concurrent)
BOOST_AUTO_TEST_SUITE(channel)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const channel_type channel(3);
    }

    BOOST_AUTO_TEST_CASE(insert)
    {
        BOOST_TEST_PASSPOINT();

        channel_type channel(3);

        channel.insert(12);
        channel.insert(34);
        channel.insert(56);
    }

    BOOST_AUTO_TEST_CASE(take)
    {
        BOOST_TEST_PASSPOINT();

        {
            channel_type channel(3);

            channel.insert(12);
            channel.insert(34);
            channel.insert(56);

            BOOST_CHECK_EQUAL(channel.take(), 12);
            BOOST_CHECK_EQUAL(channel.take(), 34);
            BOOST_CHECK_EQUAL(channel.take(), 56);
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

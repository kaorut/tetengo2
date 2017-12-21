/*! \file
    \brief Test of class tetengo2::concurrent::consumer.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <stdexcept>

#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/concurrent/channel.h>
#include <tetengo2/concurrent/consumer.h>


namespace
{
    // types

    using value_type = int;

    using channel_type = tetengo2::concurrent::channel<value_type>;

    using consumer_type = tetengo2::concurrent::consumer<value_type>;


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(concurrent)
BOOST_AUTO_TEST_SUITE(consumer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        channel_type channel{ 42 }; 
        const consumer_type consumer{ channel };

        channel.close();
    }

    BOOST_AUTO_TEST_CASE(closed)
    {
        BOOST_TEST_PASSPOINT();

        channel_type channel{ 42 }; 
        consumer_type consumer{ channel };

        channel.close();

        BOOST_TEST(consumer.closed());
    }

    BOOST_AUTO_TEST_CASE(peek)
    {
        BOOST_TEST_PASSPOINT();

        {
            channel_type channel{ 42 };
            channel.insert(123);
            consumer_type consumer{ channel };

            BOOST_TEST(consumer.peek() == 123);
            channel.close();
        }
        {
            channel_type channel{ 42 }; 
            consumer_type consumer{ channel };

            channel.close();

            BOOST_CHECK_THROW(consumer.peek(), std::logic_error);
        }
    }
    
    BOOST_AUTO_TEST_CASE(take)
    {
        BOOST_TEST_PASSPOINT();

        channel_type channel{ 42 }; 
        consumer_type consumer{ channel };

        channel.close();

        BOOST_CHECK_THROW(consumer.take(), std::logic_error);
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

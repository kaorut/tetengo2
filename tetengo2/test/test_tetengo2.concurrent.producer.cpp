/*! \file
    \brief Test of class tetengo2::concurrent::producer.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <stdexcept>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/concurrent/channel.h>
#include <tetengo2/concurrent/producer.h>


namespace {
    // types

    using value_type = int;

    using channel_type = tetengo2::concurrent::channel<value_type>;

    using producer_type = tetengo2::concurrent::producer<value_type>;

    void generate(channel_type& channel)
    {
        for (int count = 0;; ++count)
        {
            if (count > 4)
                return;

            channel.insert(count * 10 + 10);
        }
    }

    void throw_exception(channel_type&)
    {
        BOOST_THROW_EXCEPTION((std::runtime_error{ "test exception" }));
    }
}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(concurrent)
        BOOST_AUTO_TEST_SUITE(producer)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                channel_type  channel{ 42 };
                producer_type producer{ generate, channel };
                producer.join();
            }

            BOOST_AUTO_TEST_CASE(join)
            {
                BOOST_TEST_PASSPOINT();

                {
                    channel_type  channel{ 42 };
                    producer_type producer{ generate, channel };

                    BOOST_TEST(channel.peek() == 10);
                    channel.take();
                    BOOST_TEST(channel.peek() == 20);
                    channel.take();
                    BOOST_TEST(channel.peek() == 30);
                    channel.take();
                    BOOST_TEST(channel.peek() == 40);
                    channel.take();
                    BOOST_TEST(channel.peek() == 50);
                    channel.take();

                    producer.join();
                    BOOST_TEST(channel.closed());
                }
                {
                    channel_type  channel{ 42 };
                    producer_type producer{ throw_exception, channel };

                    BOOST_CHECK_THROW(channel.peek(), std::runtime_error);
                    channel.take();

                    producer.join();
                    BOOST_TEST(channel.closed());
                }
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

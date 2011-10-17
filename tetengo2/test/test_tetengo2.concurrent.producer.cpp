/*! \file
    \brief Test of class tetengo2::concurrent::producer.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <queue>

//#include <boost/noncopyable.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.concurrent.producer.h"


namespace
{
    // types

    class channel_type : private boost::noncopyable
    {
    public:
        typedef int value_type;

        channel_type(const bool empty)
        :
        m_values(make_values(empty))
        {}

        bool empty()
        const
        {
            return m_values.empty();
        }

        int pop()
        {
            const int result = m_values.front();
            m_values.pop();
            return result;
        }

        void push(int value)
        {
            m_values.push(value);
        }

    private:
        static std::queue<int> make_values(const bool empty)
        {
            std::queue<int> queue;

            if (!empty)
            {
                queue.push(123);
                queue.push(456);
                queue.push(789);
            }

            return queue;
        }

        std::queue<int> m_values;
    };

    void generate(channel_type& channel)
    {
        for (int count = 0; ; ++count)
        {
            if (count > 4) return;

            channel.push(count * 10 + 10);
        }
    }

    typedef tetengo2::concurrent::producer<channel_type> producer_type;


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(concurrent)
BOOST_AUTO_TEST_SUITE(producer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        channel_type channel(true);
        producer_type producer(channel, generate);
        producer.join();
    }

    BOOST_AUTO_TEST_CASE(join)
    {
        BOOST_TEST_PASSPOINT();

        {
            channel_type channel(true);
            producer_type producer(channel, generate);
            producer.join();

            BOOST_CHECK_EQUAL(channel.pop(), 10);
            BOOST_CHECK_EQUAL(channel.pop(), 20);
            BOOST_CHECK_EQUAL(channel.pop(), 30);
            BOOST_CHECK_EQUAL(channel.pop(), 40);
            BOOST_CHECK_EQUAL(channel.pop(), 50);
            BOOST_CHECK(channel.empty());
        }
        {
            channel_type channel(false);
            producer_type producer(channel, generate);
            producer.join();

            BOOST_CHECK_EQUAL(channel.pop(), 123);
            BOOST_CHECK_EQUAL(channel.pop(), 456);
            BOOST_CHECK_EQUAL(channel.pop(), 789);
            BOOST_CHECK_EQUAL(channel.pop(), 10);
            BOOST_CHECK_EQUAL(channel.pop(), 20);
            BOOST_CHECK_EQUAL(channel.pop(), 30);
            BOOST_CHECK_EQUAL(channel.pop(), 40);
            BOOST_CHECK_EQUAL(channel.pop(), 50);
            BOOST_CHECK(channel.empty());
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

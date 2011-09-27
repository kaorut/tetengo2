/*! \file
    \brief Test of class tetengo2::concurrent::consumer.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <queue>

#include <boost/noncopyable.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.concurrent.consumer.h"


namespace
{
    // types

    class channel_type : private boost::noncopyable
    {
    public:
        channel_type()
        :
        m_values(make_values())
        {}

        int pop()
        {
            const int result = m_values.front();
            m_values.pop();
            return result;
        }

    private:
        static std::queue<int> make_values()
        {
            std::queue<int> queue;

            queue.push(123);
            queue.push(456);
            queue.push(789);

            return queue;
        }

        std::queue<int> m_values;
    };

    typedef tetengo2::concurrent::consumer<int, channel_type> consumer_type;


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(concurrent)
BOOST_AUTO_TEST_SUITE(consumer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        channel_type channel; 
        const consumer_type consumer(channel);
    }

    BOOST_AUTO_TEST_CASE(pop)
    {
        BOOST_TEST_PASSPOINT();

        channel_type channel; 
        consumer_type consumer(channel);

        BOOST_CHECK_EQUAL(consumer.pop(), 123);
        BOOST_CHECK_EQUAL(consumer.pop(), 456);
        BOOST_CHECK_EQUAL(consumer.pop(), 789);
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

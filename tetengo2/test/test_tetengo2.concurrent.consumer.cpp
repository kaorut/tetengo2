/*! \file
    \brief Test of class tetengo2::concurrent::consumer.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <queue>
#include <stdexcept>

#include <boost/core/noncopyable.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>


namespace
{
    // types

    class channel_type : private boost::noncopyable
    {
    public:
        using value_type = int;

        channel_type(const bool empty)
        :
        m_values(make_values(empty))
        {}

        const int& peek()
        const
        {
            return m_values.front();
        }

        void take()
        {
            m_values.pop();
        }

        void insert(int value)
        {
            m_values.push(value);
        }

        bool close_requested()
        const
        {
            return false;
        }

        void request_close()
        {}

        bool closed()
        const
        {
            return m_values.empty();
        }

    private:
        static std::queue<int> make_values(const bool closed)
        {
            std::queue<int> queue{};

            if (!closed)
            {
                queue.push(123);
                queue.push(456);
                queue.push(789);
            }

            return queue;
        }

        std::queue<int> m_values;
    };

    using consumer_type = tetengo2::concurrent::consumer<channel_type>;


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(concurrent)
BOOST_AUTO_TEST_SUITE(consumer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        channel_type channel{ true }; 
        const consumer_type consumer{ channel };
    }

    BOOST_AUTO_TEST_CASE(closed)
    {
        BOOST_TEST_PASSPOINT();

        {
            channel_type channel{ false }; 
            consumer_type consumer{ channel };

            BOOST_CHECK(!consumer.closed());
        }
        {
            channel_type channel{ true }; 
            consumer_type consumer{ channel };

            BOOST_CHECK(consumer.closed());
        }
    }

    BOOST_AUTO_TEST_CASE(peek)
    {
        BOOST_TEST_PASSPOINT();

        {
            channel_type channel{ false }; 
            consumer_type consumer{ channel };

            BOOST_CHECK_EQUAL(consumer.peek(), 123);
        }
        {
            channel_type channel{ true }; 
            consumer_type consumer{ channel };

            BOOST_CHECK_THROW(consumer.take(), std::logic_error);
        }
    }
    
    BOOST_AUTO_TEST_CASE(take)
    {
        BOOST_TEST_PASSPOINT();

        {
            channel_type channel{ false }; 
            consumer_type consumer{ channel };

            consumer.take();
            consumer.take();
            consumer.take();
            BOOST_CHECK_THROW(consumer.take(), std::logic_error);
        }
        {
            channel_type channel{ true }; 
            consumer_type consumer{ channel };

            BOOST_CHECK_THROW(consumer.take(), std::logic_error);
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

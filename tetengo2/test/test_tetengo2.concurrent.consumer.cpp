/*! \file
    \brief Test of class tetengo2::concurrent::consumer.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <queue>
#include <stdexcept>

#include <boost/core/noncopyable.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/concurrent/channel.h>
#include <tetengo2/concurrent/consumer.h>


namespace
{
    // types

#if 0
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
#endif

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

/*! \file
    \brief Test of class tetengo2::concurrent::producer.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <exception>
#include <queue>
#include <stdexcept>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/throw_exception.hpp>

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
        m_values(make_values(empty)),
        m_exceptions()
        {}

        void insert(int value)
        {
            m_values.push(value);
        }

        void insert_exception(const std::exception_ptr& p_exception)
        {
            m_exceptions.push(p_exception);
        }

        int take()
        {
            if (!m_exceptions.empty())
            {
                const auto p_exception = m_exceptions.front();
                m_exceptions.pop();
                std::rethrow_exception(p_exception);
            }

            const auto result = m_values.front();
            m_values.pop();
            return result;
        }

        void close()
        {}

        bool closed()
        const
        {
            return m_values.empty() && m_exceptions.empty();
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

        std::queue<std::exception_ptr> m_exceptions;

    };

    void generate(channel_type& channel)
    {
        for (int count = 0; ; ++count)
        {
            if (count > 4) return;

            channel.insert(count * 10 + 10);
        }
    }

    void throw_exception(channel_type& channel)
    {
        boost::ignore_unused(channel);

        BOOST_THROW_EXCEPTION((std::runtime_error{ "test exception" }));
    }

    using producer_type = tetengo2::concurrent::producer<channel_type>;


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(concurrent)
BOOST_AUTO_TEST_SUITE(producer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        channel_type channel{ true };
        producer_type producer{ generate, channel };
        producer.join();
    }

    BOOST_AUTO_TEST_CASE(join)
    {
        BOOST_TEST_PASSPOINT();

        {
            channel_type channel{ true };
            producer_type producer{ generate, channel };
            producer.join();

            BOOST_TEST(channel.take() == 10);
            BOOST_TEST(channel.take() == 20);
            BOOST_TEST(channel.take() == 30);
            BOOST_TEST(channel.take() == 40);
            BOOST_TEST(channel.take() == 50);
            BOOST_TEST(channel.closed());
        }
        {
            channel_type channel{ false };
            producer_type producer{ generate, channel };
            producer.join();

            BOOST_TEST(channel.take() == 123);
            BOOST_TEST(channel.take() == 456);
            BOOST_TEST(channel.take() == 789);
            BOOST_TEST(channel.take() == 10);
            BOOST_TEST(channel.take() == 20);
            BOOST_TEST(channel.take() == 30);
            BOOST_TEST(channel.take() == 40);
            BOOST_TEST(channel.take() == 50);
            BOOST_TEST(channel.closed());
        }
        {
            channel_type channel{ true };
            producer_type producer{ throw_exception, channel };
            producer.join();

            BOOST_CHECK_THROW(channel.take(), std::runtime_error);
            BOOST_TEST(channel.closed());
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

/*! \file
    \brief Test of class tetengo2::concurrent::channel.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <cassert>
#include <chrono>
#include <exception>
#include <stdexcept>
#include <string>
#include <thread>

#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/concurrent/channel.h>


namespace
{
    // types

    using channel_type = tetengo2::concurrent::channel<int>;

    struct test_exception : public std::runtime_error
    {
        test_exception() : std::runtime_error("fuga") {}
    };


    // functions

    void produce(channel_type* const p_channel)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
        p_channel->insert(12);
        std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
        p_channel->insert(34);
        std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
        p_channel->insert(56);

        std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
        p_channel->close();
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(concurrent)
BOOST_AUTO_TEST_SUITE(channel)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const channel_type channel{ 3 };
        }
        {
            BOOST_CHECK_THROW(const channel_type channel{ 0 }, std::invalid_argument);
        }
    }

    BOOST_AUTO_TEST_CASE(insert)
    {
        BOOST_TEST_PASSPOINT();

        channel_type channel{ 3 };

        channel.insert(12);
        channel.insert(34);
        channel.insert(56);
    }

    BOOST_AUTO_TEST_CASE(insert_exception)
    {
        BOOST_TEST_PASSPOINT();

        channel_type channel{ 3 };

        channel.insert_exception(std::make_exception_ptr(std::runtime_error{ "hoge" }));
    }

    BOOST_AUTO_TEST_CASE(peek)
    {
        BOOST_TEST_PASSPOINT();

        {
            channel_type channel{ 3 };

            channel.insert(12);
            channel.insert(34);

            BOOST_TEST(channel.peek() == 12);
        }
        {
            channel_type channel{ 3 };

            channel.insert_exception(std::make_exception_ptr(std::runtime_error{ "hoge" }));

            try
            {
                channel.peek();
            }
            catch (const std::runtime_error& e)
            {
                BOOST_CHECK((std::string{ e.what() } == "hoge"));
            }
            catch (...)
            {
                BOOST_ERROR("Unknown exception.");
            }
        }
    }

    BOOST_AUTO_TEST_CASE(take)
    {
        BOOST_TEST_PASSPOINT();

        {
            channel_type channel{ 3 };

            channel.insert(12);
            channel.insert(34);
            channel.insert(56);

            channel.take();
            channel.take();
            channel.take();
        }
        {
            channel_type channel{ 3 };

            channel.insert_exception(std::make_exception_ptr(std::runtime_error{ "hoge" }));
            channel.insert_exception(std::make_exception_ptr(test_exception{}));

            channel.take();
            channel.take();
        }
    }

    BOOST_AUTO_TEST_CASE(close_requested)
    {
        BOOST_TEST_PASSPOINT();

        const channel_type channel{ 3 };

        BOOST_TEST(!channel.close_requested());
    }

    BOOST_AUTO_TEST_CASE(request_close)
    {
        BOOST_TEST_PASSPOINT();

        channel_type channel{ 3 };

        channel.request_close();

        BOOST_TEST(channel.close_requested());
    }

    BOOST_AUTO_TEST_CASE(close)
    {
        BOOST_TEST_PASSPOINT();

        {
            channel_type channel{ 3 };

            channel.insert(12);

            channel.close();

            channel.insert(34);
        }
        {
            channel_type channel{ 3 };

            channel.insert(12);

            channel.close();

            BOOST_TEST(channel.peek() == 12);
            channel.take();
            BOOST_CHECK_THROW(channel.peek(), std::logic_error);
        }
        {
            channel_type channel{ 3 };

            channel.insert(12);

            channel.close();

            channel.close();
        }
    }

    BOOST_AUTO_TEST_CASE(closed)
    {
        BOOST_TEST_PASSPOINT();

        {
            channel_type channel{ 3 };

            channel.close();

            BOOST_TEST(channel.closed());
        }
        {
            channel_type channel{ 3 };

            channel.insert(12);

            channel.close();

            BOOST_TEST(!channel.closed());

            channel.take();

            BOOST_TEST(channel.closed());
        }
        {
            channel_type channel{ 3 };

            std::thread producing_thread{ produce, &channel };

            BOOST_TEST(channel.peek() == 12);
            channel.take();
            BOOST_TEST(channel.peek() == 34);
            channel.take();
            BOOST_TEST(channel.peek() == 56);
            channel.take();

            BOOST_TEST(channel.closed());

            assert(producing_thread.joinable());
            producing_thread.join();
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

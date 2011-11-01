/*! \file
    \brief Test of class tetengo2::concurrent::channel.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <cstddef>
//#include <stdexcept>
#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>
//#include <boost/exception_ptr.hpp>
#include <boost/test/unit_test.hpp>
//#include <boost/thread.hpp>

#include "tetengo2.cpp11.h"

#include "tetengo2.concurrent.channel.h"


namespace
{
    // types

    typedef tetengo2::concurrent::channel<int, std::size_t> channel_type;

    struct test_exception : public std::runtime_error
    {
        test_exception() : std::runtime_error("fuga") {}
    };


    // functions

    void produce(channel_type& channel)
    {
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        channel.insert(12);
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        channel.insert(34);
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        channel.insert(56);

        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        channel.finish_insertion();
    }


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

    BOOST_AUTO_TEST_CASE(insert_exception)
    {
        BOOST_TEST_PASSPOINT();

        channel_type channel(3);

        channel.insert_exception(
            boost::copy_exception(std::runtime_error("hoge"))
        );
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
        {
            channel_type channel(3);

            channel.insert_exception(
                boost::copy_exception(std::runtime_error("hoge"))
            );
            channel.insert_exception(boost::copy_exception(test_exception()));

            try
            {
                channel.take();
            }
            catch (const std::runtime_error& e)
            {
                BOOST_CHECK(std::string(e.what()) == "hoge");
            }
            catch (...)
            {
                BOOST_ERROR("Unknown exception.");
            }
            try
            {
                channel.take();
            }
            catch (const test_exception& e)
            {
                BOOST_CHECK(std::string(e.what()) == test_exception().what());
            }
            catch (...)
            {
                BOOST_ERROR("Unknown exception.");
            }
        }
    }

    BOOST_AUTO_TEST_CASE(finish_insertion)
    {
        BOOST_TEST_PASSPOINT();

        {
            channel_type channel(3);

            channel.insert(12);

            channel.finish_insertion();

            BOOST_CHECK_THROW(channel.insert(34), std::logic_error);
        }
        {
            channel_type channel(3);

            channel.insert(12);

            channel.finish_insertion();

            BOOST_CHECK_EQUAL(channel.take(), 12);
            BOOST_CHECK_THROW(channel.take(), std::logic_error);
        }
        {
            channel_type channel(3);

            channel.insert(12);

            channel.finish_insertion();
            BOOST_CHECK_THROW(channel.finish_insertion(), std::logic_error);
        }
    }

    BOOST_AUTO_TEST_CASE(has_no_more)
    {
        BOOST_TEST_PASSPOINT();

        {
            channel_type channel(3);

            channel.finish_insertion();

            BOOST_CHECK(channel.has_no_more());
        }
        {
            channel_type channel(3);

            channel.insert(12);

            channel.finish_insertion();

            BOOST_CHECK(!channel.has_no_more());

            channel.take();

            BOOST_CHECK(channel.has_no_more());
        }
        {
            channel_type channel(3);

            boost::thread producing_thread(
                produce, tetengo2::cpp11::ref(channel)
            );

            BOOST_CHECK_EQUAL(channel.take(), 12);
            BOOST_CHECK_EQUAL(channel.take(), 34);
            BOOST_CHECK_EQUAL(channel.take(), 56);

            BOOST_CHECK(channel.has_no_more());

            producing_thread.join();
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
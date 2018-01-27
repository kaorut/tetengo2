/*! \file
    \brief Test of class tetengo2::concurrent::progressive_future.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <chrono>
#include <future>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/concurrent/progressive_future.h>


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(concurrent)
BOOST_AUTO_TEST_SUITE(progressive_future)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            using future_type = tetengo2::concurrent::progressive_future<std::string>;

            future_type future1{};
            const future_type future2{ std::move(future1) };
        }
        {
            using future_type = tetengo2::concurrent::progressive_future<const std::string&>;

            future_type future1{};
            const future_type future2{ std::move(future1) };
        }
        {
            using future_type = tetengo2::concurrent::progressive_future<void>;

            future_type future1{};
            const future_type future2{ std::move(future1) };
        }
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        {
            using future_type = tetengo2::concurrent::progressive_future<std::string>;

            future_type future1{};
            future_type future2{};
            future2 = std::move(future1);
        }
        {
            using future_type = tetengo2::concurrent::progressive_future<const std::string&>;

            future_type future1{};
            future_type future2{};
            future2 = std::move(future1);
        }
        {
            using future_type = tetengo2::concurrent::progressive_future<void>;

            future_type future1{};
            future_type future2{};
            future2 = std::move(future1);
        }
    }

    BOOST_AUTO_TEST_CASE(get)
    {
        BOOST_TEST_PASSPOINT();

        {
            using future_type = tetengo2::concurrent::progressive_future<std::string>;

            future_type future{};
            BOOST_CHECK_THROW(future.get(), std::future_error);
        }
        {
            using future_type = tetengo2::concurrent::progressive_future<const std::string&>;

            future_type future{};
            BOOST_CHECK_THROW(future.get(), std::future_error);
        }
        {
            using future_type = tetengo2::concurrent::progressive_future<void>;

            future_type future{};
            BOOST_CHECK_THROW(future.get(), std::future_error);
        }
    }

    BOOST_AUTO_TEST_CASE(valid)
    {
        BOOST_TEST_PASSPOINT();

        using future_type = tetengo2::concurrent::progressive_future<std::string>;

        future_type future{};
        BOOST_TEST(!future.valid());
    }

    BOOST_AUTO_TEST_CASE(wait)
    {
        BOOST_TEST_PASSPOINT();

        using future_type = tetengo2::concurrent::progressive_future<std::string>;

        future_type future{};
        BOOST_CHECK_THROW(future.wait(), std::future_error);
    }

    BOOST_AUTO_TEST_CASE(wait_for)
    {
        BOOST_TEST_PASSPOINT();

        using future_type = tetengo2::concurrent::progressive_future<std::string>;

        future_type future{};
        const std::chrono::seconds rel_time{ 42 };
        BOOST_CHECK_THROW(future.wait_for(rel_time), std::future_error);
    }

    BOOST_AUTO_TEST_CASE(wait_until)
    {
        BOOST_TEST_PASSPOINT();

        using future_type = tetengo2::concurrent::progressive_future<std::string>;

        future_type future{};
        const auto abs_time = std::chrono::system_clock::now() + std::chrono::seconds{ 42 };
        BOOST_CHECK_THROW(future.wait_until(abs_time), std::future_error);
    }

    BOOST_AUTO_TEST_CASE(progress)
    {
        BOOST_TEST_PASSPOINT();

        using future_type = tetengo2::concurrent::progressive_future<std::string>;

        future_type future{};
        BOOST_CHECK_THROW(future.progress(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(request_abort)
    {
        BOOST_TEST_PASSPOINT();

        using future_type = tetengo2::concurrent::progressive_future<std::string>;

        future_type future{};
        BOOST_CHECK_THROW(future.request_abort(), std::logic_error);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

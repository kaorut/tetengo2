/*! \file
    \brief Test of class tetengo2::concurrent::progressive_promise.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <future>
#include <memory>
#include <string>
#include <utility>

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(concurrent)
BOOST_AUTO_TEST_SUITE(progressive_promise)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            using promise_type = tetengo2::concurrent::progressive_promise<std::string, int>;

            const promise_type promise1{};
            promise_type promise2{ std::allocator_arg, std::allocator<promise_type>{} };
            const promise_type promise3{ std::move(promise2) };
        }
        {
            using promise_type = tetengo2::concurrent::progressive_promise<const std::string&, int>;

            const promise_type promise1{};
            promise_type promise2{ std::allocator_arg, std::allocator<promise_type>{} };
            const promise_type promise3{ std::move(promise2) };
        }
        {
            using promise_type = tetengo2::concurrent::progressive_promise<void, int>;

            const promise_type promise1{};
            promise_type promise2{ std::allocator_arg, std::allocator<promise_type>{} };
            const promise_type promise3{ std::move(promise2) };
        }
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        {
            using promise_type = tetengo2::concurrent::progressive_promise<std::string, int>;

            promise_type promise1{};
            promise_type promise2{};

            promise1 = std::move(promise2);
        }
        {
            using promise_type = tetengo2::concurrent::progressive_promise<const std::string&, int>;

            promise_type promise1{};
            promise_type promise2{};

            promise1 = std::move(promise2);
        }
        {
            using promise_type = tetengo2::concurrent::progressive_promise<void, int>;

            promise_type promise1{};
            promise_type promise2{};

            promise1 = std::move(promise2);
        }
    }

    BOOST_AUTO_TEST_CASE(swap)
    {
        BOOST_TEST_PASSPOINT();

        {
            using promise_type = tetengo2::concurrent::progressive_promise<std::string, int>;

            promise_type promise1{};
            promise_type promise2{};

            promise1.swap(promise2);

            std::swap(promise1, promise2);
        }
        {
            using promise_type = tetengo2::concurrent::progressive_promise<const std::string&, int>;

            promise_type promise1{};
            promise_type promise2{};

            promise1.swap(promise2);

            std::swap(promise1, promise2);
        }
        {
            using promise_type = tetengo2::concurrent::progressive_promise<void, int>;

            promise_type promise1{};
            promise_type promise2{};

            promise1.swap(promise2);

            std::swap(promise1, promise2);
        }
    }

    BOOST_AUTO_TEST_CASE(get_future)
    {
        BOOST_TEST_PASSPOINT();

        using promise_type = tetengo2::concurrent::progressive_promise<std::string, int>;

        {
            promise_type promise{};

            const auto future = promise.get_future();
            BOOST_CHECK(future.valid());
        }
        {
            promise_type promise{};

            promise.set_value("hoge");

            const auto future = promise.get_future();

            BOOST_CHECK_THROW(promise.get_future(), std::future_error);
        }
    }

    BOOST_AUTO_TEST_CASE(set_value)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_exception)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_value_at_thread_exit)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_exception_at_thread_exit)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

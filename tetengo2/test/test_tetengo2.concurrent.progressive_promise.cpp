/*! \file
    \brief Test of class tetengo2::concurrent::progressive_promise.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <chrono>
#include <exception>
#include <future>
#include <memory>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <type_traits>
#include <utility>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/concurrent/progressive_future.h>
#include <tetengo2/concurrent/progressive_promise.h>


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(concurrent)
        BOOST_AUTO_TEST_SUITE(progressive_promise)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                {
                    using promise_type = tetengo2::concurrent::progressive_promise<std::string>;

                    const promise_type promise1{ 0 };
                    promise_type       promise2{ 0, std::allocator_arg, std::allocator<promise_type>{} };
                    const promise_type promise3{ std::move(promise2) };
                }
                {
                    using promise_type = tetengo2::concurrent::progressive_promise<const std::string&>;

                    const promise_type promise1{ 0 };
                    promise_type       promise2{ 0, std::allocator_arg, std::allocator<promise_type>{} };
                    const promise_type promise3{ std::move(promise2) };
                }
                {
                    using promise_type = tetengo2::concurrent::progressive_promise<void>;

                    const promise_type promise1{ 0 };
                    promise_type       promise2{ 0, std::allocator_arg, std::allocator<promise_type>{} };
                    const promise_type promise3{ std::move(promise2) };
                }
            }

            BOOST_AUTO_TEST_CASE(operator_assign)
            {
                BOOST_TEST_PASSPOINT();

                {
                    using promise_type = tetengo2::concurrent::progressive_promise<std::string>;

                    promise_type promise1{ 0 };
                    promise_type promise2{ 0 };

                    promise1 = std::move(promise2);
                }
                {
                    using promise_type = tetengo2::concurrent::progressive_promise<const std::string&>;

                    promise_type promise1{ 0 };
                    promise_type promise2{ 0 };

                    promise1 = std::move(promise2);
                }
                {
                    using promise_type = tetengo2::concurrent::progressive_promise<void>;

                    promise_type promise1{ 0 };
                    promise_type promise2{ 0 };

                    promise1 = std::move(promise2);
                }
            }

            BOOST_AUTO_TEST_CASE(swap)
            {
                BOOST_TEST_PASSPOINT();

                {
                    using promise_type = tetengo2::concurrent::progressive_promise<std::string>;

                    promise_type promise1{ 0 };
                    promise_type promise2{ 0 };

                    promise1.swap(promise2);

                    std::swap(promise1, promise2);
                }
                {
                    using promise_type = tetengo2::concurrent::progressive_promise<const std::string&>;

                    promise_type promise1{ 0 };
                    promise_type promise2{ 0 };

                    promise1.swap(promise2);

                    std::swap(promise1, promise2);
                }
                {
                    using promise_type = tetengo2::concurrent::progressive_promise<void>;

                    promise_type promise1{ 0 };
                    promise_type promise2{ 0 };

                    promise1.swap(promise2);

                    std::swap(promise1, promise2);
                }
            }

            BOOST_AUTO_TEST_CASE(get_future)
            {
                BOOST_TEST_PASSPOINT();

                using promise_type = tetengo2::concurrent::progressive_promise<std::string>;

                {
                    promise_type promise{ 0 };

                    const auto future = promise.get_future();
                    BOOST_TEST(future.valid());
                }
                {
                    promise_type promise{ 0 };

                    promise.set_value("hoge");

                    promise.get_future();

                    BOOST_CHECK_THROW(promise.get_future(), std::future_error);
                }
            }

            BOOST_AUTO_TEST_CASE(set_value)
            {
                BOOST_TEST_PASSPOINT();

                struct test_exception : public std::runtime_error
                {
                    test_exception() : std::runtime_error{ "test exception" } {}
                };

                {
                    using promise_type = tetengo2::concurrent::progressive_promise<std::string>;

                    {
                        promise_type promise{ 0 };
                        auto         future = promise.get_future();
                        BOOST_CHECK(future.wait_for(std::chrono::seconds(0)) != std::future_status::ready);

                        const std::string value{ "hoge" };
                        promise.set_value(value);

                        BOOST_CHECK(future.wait_for(std::chrono::seconds(0)) == std::future_status::ready);
                        BOOST_CHECK(future.get() == "hoge");

                        BOOST_CHECK_THROW(promise.set_value("fuga"), std::future_error);
                        BOOST_CHECK_THROW(
                            promise.set_exception(std::make_exception_ptr(test_exception{})), std::future_error);
                    }
                    {
                        promise_type promise{ 0 };
                        auto         future = promise.get_future();
                        BOOST_CHECK(future.wait_for(std::chrono::seconds(0)) != std::future_status::ready);

                        promise.set_value("hoge");

                        BOOST_CHECK(future.wait_for(std::chrono::seconds(0)) == std::future_status::ready);
                        BOOST_CHECK(future.get() == "hoge");

                        BOOST_CHECK_THROW(promise.set_value("fuga"), std::future_error);
                        BOOST_CHECK_THROW(
                            promise.set_exception(std::make_exception_ptr(test_exception{})), std::future_error);
                    }
                }
                {
                    using promise_type = tetengo2::concurrent::progressive_promise<const std::string&>;

                    promise_type promise{ 0 };
                    auto         future = promise.get_future();
                    BOOST_CHECK(future.wait_for(std::chrono::seconds(0)) != std::future_status::ready);

                    const std::string value{ "hoge" };
                    promise.set_value(value);

                    BOOST_CHECK(future.wait_for(std::chrono::seconds(0)) == std::future_status::ready);
                    BOOST_CHECK(future.get() == "hoge");

                    BOOST_CHECK_THROW(promise.set_value("fuga"), std::future_error);
                    BOOST_CHECK_THROW(
                        promise.set_exception(std::make_exception_ptr(test_exception{})), std::future_error);
                }
                {
                    using promise_type = tetengo2::concurrent::progressive_promise<void>;

                    promise_type promise{ 0 };
                    auto         future = promise.get_future();
                    BOOST_CHECK(future.wait_for(std::chrono::seconds(0)) != std::future_status::ready);

                    promise.set_value();

                    BOOST_CHECK(future.wait_for(std::chrono::seconds(0)) == std::future_status::ready);

                    BOOST_CHECK_THROW(promise.set_value(), std::future_error);
                    BOOST_CHECK_THROW(
                        promise.set_exception(std::make_exception_ptr(test_exception{})), std::future_error);
                }
            }

            BOOST_AUTO_TEST_CASE(set_exception)
            {
                BOOST_TEST_PASSPOINT();

                struct test_exception : public std::runtime_error
                {
                    test_exception() : std::runtime_error{ "test exception" } {}
                };

                using promise_type = tetengo2::concurrent::progressive_promise<std::string>;

                promise_type promise{ 0 };
                auto         future = promise.get_future();
                BOOST_CHECK(future.wait_for(std::chrono::seconds(0)) != std::future_status::ready);

                promise.set_exception(std::make_exception_ptr(test_exception{}));

                BOOST_CHECK(future.wait_for(std::chrono::seconds(0)) == std::future_status::ready);
                BOOST_CHECK_THROW(future.get(), test_exception);

                BOOST_CHECK_THROW(promise.set_value("fuga"), std::future_error);
                BOOST_CHECK_THROW(promise.set_exception(std::make_exception_ptr(test_exception{})), std::future_error);
            }

            BOOST_AUTO_TEST_CASE(set_value_at_thread_exit)
            {
                BOOST_TEST_PASSPOINT();

                struct test_exception : public std::runtime_error
                {
                    test_exception() : std::runtime_error{ "test exception" } {}
                };

                {
                    using promise_type = tetengo2::concurrent::progressive_promise<std::string>;

                    {
                        promise_type promise{ 0 };
                        auto         future = promise.get_future();
                        BOOST_CHECK(future.wait_for(std::chrono::seconds(0)) != std::future_status::ready);

                        auto thread_function = [&promise]() {
                            const std::string value{ "hoge" };
                            promise.set_value_at_thread_exit(value);
                        };
                        std::thread thread{ std::move(thread_function) };

                        BOOST_CHECK(future.get() == "hoge");

                        thread.join();
                    }
                    {
                        promise_type promise{ 0 };
                        auto         future = promise.get_future();
                        BOOST_CHECK(future.wait_for(std::chrono::seconds(0)) != std::future_status::ready);

                        std::thread thread{ [&promise]() { promise.set_value_at_thread_exit("hoge"); } };

                        BOOST_CHECK(future.get() == "hoge");

                        thread.join();
                    }
                }
                {
                    using promise_type = tetengo2::concurrent::progressive_promise<const std::string&>;

                    promise_type promise{ 0 };
                    auto         future = promise.get_future();
                    BOOST_CHECK(future.wait_for(std::chrono::seconds(0)) != std::future_status::ready);

                    const std::string value{ "hoge" };
                    std::thread       thread{ [&promise, &value]() { promise.set_value_at_thread_exit(value); } };

                    BOOST_CHECK(future.get() == "hoge");

                    thread.join();
                }
                {
                    using promise_type = tetengo2::concurrent::progressive_promise<void>;

                    promise_type promise{ 0 };
                    auto         future = promise.get_future();
                    BOOST_CHECK(future.wait_for(std::chrono::seconds(0)) != std::future_status::ready);

                    std::thread thread{ [&promise]() { promise.set_value(); } };

                    thread.join();
                }
            }

            BOOST_AUTO_TEST_CASE(set_exception_at_thread_exit)
            {
                BOOST_TEST_PASSPOINT();

                struct test_exception : public std::runtime_error
                {
                    test_exception() : std::runtime_error{ "test exception" } {}
                };

                using promise_type = tetengo2::concurrent::progressive_promise<std::string>;

                promise_type promise{ 0 };
                auto         future = promise.get_future();
                BOOST_CHECK(future.wait_for(std::chrono::seconds(0)) != std::future_status::ready);

                std::thread thread{ [&promise]() {
                    promise.set_exception(std::make_exception_ptr(test_exception{}));
                } };

                BOOST_CHECK_THROW(future.get(), test_exception);

                thread.join();
            }

            BOOST_AUTO_TEST_CASE(set_progress)
            {
                BOOST_TEST_PASSPOINT();

                using promise_type = tetengo2::concurrent::progressive_promise<std::string>;

                promise_type promise{ 0 };
                auto         future = promise.get_future();

                BOOST_TEST(future.progress() == 0);

                promise.set_progress(42);

                BOOST_TEST(future.progress() == 42);
            }

            BOOST_AUTO_TEST_CASE(abort_requested)
            {
                BOOST_TEST_PASSPOINT();

                using promise_type = tetengo2::concurrent::progressive_promise<std::string>;

                promise_type promise{ 0 };
                auto         future = promise.get_future();

                BOOST_TEST(!promise.abort_requested());

                future.request_abort();

                BOOST_TEST(promise.abort_requested());

                future.request_abort();

                BOOST_TEST(promise.abort_requested());
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

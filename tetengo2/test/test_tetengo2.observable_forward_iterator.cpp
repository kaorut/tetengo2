/*! \file
    \brief Test of class tetengo2::observable_forward_iterator.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <forward_list>

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(observable_forward_iterator)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::forward_list<int> list{ 42, 43, 44, 45, };

        const tetengo2::observable_forward_iterator<std::forward_list<int>::iterator> iterator{ list.begin() };
    }

    BOOST_AUTO_TEST_CASE(dereference)
    {
        BOOST_TEST_PASSPOINT();

        std::forward_list<int> list{ 42, 43, 44, 45, };

        tetengo2::observable_forward_iterator<std::forward_list<int>::iterator> iterator{ list.begin() };

        BOOST_CHECK_EQUAL(*iterator, 42);

        *iterator = 24;

        BOOST_CHECK_EQUAL(list.front(), 24);
    }

    BOOST_AUTO_TEST_CASE(equal)
    {
        BOOST_TEST_PASSPOINT();

        std::forward_list<int> list{ 42, 43, 44, 45, };

        const tetengo2::observable_forward_iterator<std::forward_list<int>::iterator> iterator1{ list.begin() };
        const tetengo2::observable_forward_iterator<std::forward_list<int>::iterator> iterator2{ list.begin() };

        BOOST_CHECK(iterator1 == iterator2);
    }

    BOOST_AUTO_TEST_CASE(increment)
    {
        BOOST_TEST_PASSPOINT();

        std::forward_list<int> list{ 42, 43, 44, 45, };

        tetengo2::observable_forward_iterator<std::forward_list<int>::iterator> iterator{ list.begin() };

        ++iterator;

        BOOST_CHECK_EQUAL(*iterator, 43);

        ++iterator;
        ++iterator;
        ++iterator;

        const tetengo2::observable_forward_iterator<std::forward_list<int>::iterator> last{ list.end() };
        BOOST_CHECK(iterator == last);
    }

    BOOST_AUTO_TEST_CASE(increment_signal)
    {
        BOOST_TEST_PASSPOINT();

        std::forward_list<int> list{ 42, 43, 44, 45, };

        tetengo2::observable_forward_iterator<std::forward_list<int>::iterator> iterator{ list.begin() };
        
        int count = 0;
        iterator.increment_signal().connect([&count]() { ++count; });

        ++iterator;

        BOOST_CHECK_EQUAL(count, 1);

        ++iterator;
        ++iterator;
        ++iterator;

        BOOST_CHECK_EQUAL(count, 4);
    }


BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_CASE(make_observable_forward_iterator)
{
    BOOST_TEST_PASSPOINT();

    std::forward_list<int> list{ 42, 43, 44, 45, };

    const auto iterator = tetengo2::make_observable_forward_iterator<std::forward_list<int>::iterator>(list.begin());

    BOOST_CHECK_EQUAL(*iterator, 42);
}


BOOST_AUTO_TEST_SUITE_END()

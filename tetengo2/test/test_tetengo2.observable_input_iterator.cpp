/*! \file
    \brief Test of class tetengo2::observable_input_iterator.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <vector>

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(observable_input_iterator)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<int> v{ 42, 43, 44, 45, };

        const tetengo2::observable_input_iterator<std::vector<int>::iterator> iterator{ v.begin() };
    }

    BOOST_AUTO_TEST_CASE(dereference)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<int> v{ 42, 43, 44, 45, };

        const tetengo2::observable_input_iterator<std::vector<int>::iterator> iterator{ v.begin() };

        BOOST_CHECK_EQUAL(*iterator, 42);
    }

    BOOST_AUTO_TEST_CASE(equal)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<int> v{ 42, 43, 44, 45, };

        const tetengo2::observable_input_iterator<std::vector<int>::iterator> iterator1{ v.begin() };
        const tetengo2::observable_input_iterator<std::vector<int>::iterator> iterator2{ v.begin() };

        BOOST_CHECK(iterator1 == iterator2);
    }

    BOOST_AUTO_TEST_CASE(increment)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<int> v{ 42, 43, 44, 45, };

        tetengo2::observable_input_iterator<std::vector<int>::iterator> iterator{ v.begin() };

        ++iterator;

        BOOST_CHECK_EQUAL(*iterator, 43);

        ++iterator;
        ++iterator;
        ++iterator;

        const tetengo2::observable_input_iterator<std::vector<int>::iterator> last{ v.end() };
        BOOST_CHECK(iterator == last);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

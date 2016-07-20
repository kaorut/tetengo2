/*! \file
    \brief Test of class tetengo2::iterator::observable_forward_iterator.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <forward_list>

#include <boost/test/unit_test.hpp>

#include <tetengo2/iterator/observable_forward_iterator.h>


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(iterator)
BOOST_AUTO_TEST_SUITE(observable_forward_iterator)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::forward_list<int> list{ 42, 43, 44, 45, };

        const tetengo2::iterator::observable_forward_iterator<std::forward_list<int>::iterator> iterator{
            list.begin()
        };
    }

    BOOST_AUTO_TEST_CASE(dereference)
    {
        BOOST_TEST_PASSPOINT();

        std::forward_list<int> list{ 42, 43, 44, 45, };

        tetengo2::iterator::observable_forward_iterator<std::forward_list<int>::iterator> iterator{ list.begin() };

        BOOST_TEST(*iterator == 42);

        *iterator = 24;

        BOOST_TEST(list.front() == 24);
    }

    BOOST_AUTO_TEST_CASE(equal)
    {
        BOOST_TEST_PASSPOINT();

        std::forward_list<int> list{ 42, 43, 44, 45, };

        const tetengo2::iterator::observable_forward_iterator<std::forward_list<int>::iterator> iterator1{
            list.begin()
        };
        const tetengo2::iterator::observable_forward_iterator<std::forward_list<int>::iterator> iterator2{
            list.begin()
        };

        BOOST_CHECK(iterator1 == iterator2);
    }

    BOOST_AUTO_TEST_CASE(increment)
    {
        BOOST_TEST_PASSPOINT();

        std::forward_list<int> list{ 42, 43, 44, 45, };

        tetengo2::iterator::observable_forward_iterator<std::forward_list<int>::iterator> iterator{ list.begin() };

        ++iterator;

        BOOST_TEST(*iterator == 43);

        ++iterator;
        ++iterator;
        ++iterator;

        const tetengo2::iterator::observable_forward_iterator<std::forward_list<int>::iterator> last{ list.end() };
        BOOST_CHECK(iterator == last);
    }

    BOOST_AUTO_TEST_CASE(distance_to)
    {
        BOOST_TEST_PASSPOINT();

        std::forward_list<int> list{ 42, 43, 44, 45, };

        const tetengo2::iterator::observable_forward_iterator<std::forward_list<int>::iterator> iterator1{
            list.begin()
        };
        const tetengo2::iterator::observable_forward_iterator<std::forward_list<int>::iterator> iterator2{
            list.end()
        };
        
        BOOST_TEST(iterator1.distance_to(iterator1) == 0);
        BOOST_TEST(iterator1.distance_to(iterator2) == 4);
    }

    BOOST_AUTO_TEST_CASE(set_increment_observer)
    {
        BOOST_TEST_PASSPOINT();

        std::forward_list<int> list{ 42, 43, 44, 45, };

        tetengo2::iterator::observable_forward_iterator<std::forward_list<int>::iterator> iterator{ list.begin() };
        
        int count = 0;
        iterator.set_increment_observer(
            [&count](const tetengo2::iterator::observable_forward_iterator<std::forward_list<int>::iterator>&)
            {
                ++count;
            }
        );

        ++iterator;

        BOOST_TEST(count == 1);

        ++iterator;
        ++iterator;
        ++iterator;

        BOOST_TEST(count == 4);
    }


BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_CASE(make_observable_forward_iterator)
{
    BOOST_TEST_PASSPOINT();

    std::forward_list<int> list{ 42, 43, 44, 45, };

    const auto iterator =
        tetengo2::iterator::make_observable_forward_iterator<std::forward_list<int>::iterator>(list.begin());

    BOOST_TEST(*iterator == 42);
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

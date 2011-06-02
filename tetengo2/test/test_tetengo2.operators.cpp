/*! \file
    \brief Test of class tetengo2::text.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <utility>

#include <boost/test/unit_test.hpp>

#include "tetengo2.operators.h"


namespace
{
    // types

    template <typename T, typename U = T>
    struct addable_class :
        private tetengo2::addable<addable_class<T, U>, addable_class<U>>
    {
        T value;

        addable_class(T value) : value(value) {}

        addable_class& operator+=(const addable_class<U>& another)
        {
            value += another.value;
            return *this;
        }


    };

    template <typename T, typename U = T>
    struct substractable_class :
        private tetengo2::substractable<
            substractable_class<T, U>, substractable_class<U>
        >
    {
        T value;

        substractable_class(T value) : value(value) {}

        substractable_class& operator-=(const substractable_class<U>& another)
        {
            value -= another.value;
            return *this;
        }


    };


};


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(addable)
    // test cases

    BOOST_AUTO_TEST_CASE(operator_plus)
    {
        BOOST_TEST_PASSPOINT();

        {
            const addable_class<int, unsigned short> tc1(123);
            const addable_class<unsigned short> tc2(456);

            const addable_class<int, unsigned short> tc3 = tc1 + tc2;

            BOOST_CHECK_EQUAL(tc3.value, 579);
        }
        {
            const addable_class<int, unsigned short> tc1(123);
            addable_class<unsigned short> tc2(456);

            const addable_class<int, unsigned short> tc3 =
                tc1 + std::move(tc2);

            BOOST_CHECK_EQUAL(tc3.value, 579);
        }
        {
            addable_class<int, unsigned short> tc1(123);
            const addable_class<unsigned short> tc2(456);

            const addable_class<int, unsigned short> tc3 =
                std::move(tc1) + tc2;

            BOOST_CHECK_EQUAL(tc3.value, 579);
        }
        {
            addable_class<int, unsigned short> tc1(123);
            addable_class<unsigned short> tc2(456);

            const addable_class<int, unsigned short> tc3 =
                std::move(tc1) + std::move(tc2);

            BOOST_CHECK_EQUAL(tc3.value, 579);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(substractable)
    // test cases

    BOOST_AUTO_TEST_CASE(operator_minus)
    {
        BOOST_TEST_PASSPOINT();

        {
            const substractable_class<int, unsigned short> tc1(123);
            const substractable_class<unsigned short> tc2(456);

            const substractable_class<int, unsigned short> tc3 = tc1 - tc2;

            BOOST_CHECK_EQUAL(tc3.value, -333);
        }
        {
            const substractable_class<int, unsigned short> tc1(123);
            substractable_class<unsigned short> tc2(456);

            const substractable_class<int, unsigned short> tc3 =
                tc1 - std::move(tc2);

            BOOST_CHECK_EQUAL(tc3.value, -333);
        }
        {
            substractable_class<int, unsigned short> tc1(123);
            const substractable_class<unsigned short> tc2(456);

            const substractable_class<int, unsigned short> tc3 =
                std::move(tc1) - tc2;

            BOOST_CHECK_EQUAL(tc3.value, -333);
        }
        {
            substractable_class<int, unsigned short> tc1(123);
            substractable_class<unsigned short> tc2(456);

            const substractable_class<int, unsigned short> tc3 =
                std::move(tc1) - std::move(tc2);

            BOOST_CHECK_EQUAL(tc3.value, -333);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

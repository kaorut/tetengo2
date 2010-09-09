/*! \file
    \brief Test of class tetengo2::swappable.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <boost/swap.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.swappable.h"


namespace
{
    // types

    struct test_class : private tetengo2::swappable<test_class>
    {
        int m_value;

        test_class(const int value)
        :
        m_value(value)
        {}

        void swap(test_class& another)
        TETENGO2_NOEXCEPT
        {
            const int temp = m_value;
            m_value = another.m_value;
            another.m_value = temp;
        }


    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(swappable)
    // test cases

    BOOST_AUTO_TEST_CASE(swap)
    {
        test_class x(123);
        test_class y(456);

        boost::swap(x, y);

        BOOST_CHECK_EQUAL(x.m_value, 456);
        BOOST_CHECK_EQUAL(y.m_value, 123);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

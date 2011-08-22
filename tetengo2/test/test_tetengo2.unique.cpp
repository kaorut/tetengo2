/*! \file
    \brief Test of class tetengo2::unique.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.cpp0x.h"

#include "tetengo2.unique.h"


namespace
{
    struct Class0
    {};

    struct Class1
    {
        int m_value1;
        Class1(int value1) : m_value1(value1) {}
    };

    struct Base
    {};

    struct Derived : public Base
    {};
    

}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(unique)
    // test cases

    BOOST_AUTO_TEST_CASE(make_unique)
    {
        {
            const tetengo2::cpp0x::unique_ptr<Class0>::type p(
                tetengo2::make_unique<Class0>()
            );

            BOOST_CHECK(p);
        }
        {
            const tetengo2::cpp0x::unique_ptr<Class1>::type p(
                tetengo2::make_unique<Class1>(42)
            );

            BOOST_CHECK(p);
            BOOST_CHECK_EQUAL(p->m_value1, 42);
        }
    }

    BOOST_AUTO_TEST_CASE(unique_ptr_upcast)
    {
        const tetengo2::cpp0x::unique_ptr<Base>::type p(
            tetengo2::unique_ptr_upcast<Base, Derived>(
                tetengo2::make_unique<Derived>()
            )
        );

        BOOST_CHECK(p);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

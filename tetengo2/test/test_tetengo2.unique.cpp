/*! \file
    \brief Test of class tetengo2::unique.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <memory>

#include <boost/test/unit_test.hpp>

#include "tetengo2.unique.h"


namespace
{
    struct Class0
    {};

    struct Class1
    {
        int m_value1;
        
        Class1(const int value1)
        :
        m_value1(value1)
        {}
    };

    struct Class2
    {
        int m_value1;
        int m_value2;
        
        Class2(const int value1, const int value2)
        :
        m_value1(value1),
        m_value2(value2)
        {}
    };

    struct Class3
    {
        int m_value1;
        int m_value2;
        int m_value3;
        
        Class3(const int value1, const int value2, const int value3)
        :
        m_value1(value1),
        m_value2(value2),
        m_value3(value3)
        {}
    };

    struct Class4
    {
        int m_value1;
        int m_value2;
        int m_value3;
        int m_value4;
        
        Class4(
            const int value1,
            const int value2,
            const int value3,
            const int value4
        )
        :
        m_value1(value1),
        m_value2(value2),
        m_value3(value3),
        m_value4(value4)
        {}
    };

    struct Class5
    {
        int m_value1;
        int m_value2;
        int m_value3;
        int m_value4;
        int m_value5;
        
        Class5(
            const int value1,
            const int value2,
            const int value3,
            const int value4,
            const int value5
        )
        :
        m_value1(value1),
        m_value2(value2),
        m_value3(value3),
        m_value4(value4),
        m_value5(value5)
        {}
    };

    struct Class6
    {
        int m_value1;
        int m_value2;
        int m_value3;
        int m_value4;
        int m_value5;
        int m_value6;
        
        Class6(
            const int value1,
            const int value2,
            const int value3,
            const int value4,
            const int value5,
            const int value6
        )
        :
        m_value1(value1),
        m_value2(value2),
        m_value3(value3),
        m_value4(value4),
        m_value5(value5),
        m_value6(value6)
        {}
    };

    struct Class7
    {
        int m_value1;
        int m_value2;
        int m_value3;
        int m_value4;
        int m_value5;
        int m_value6;
        int m_value7;
        
        Class7(
            const int value1,
            const int value2,
            const int value3,
            const int value4,
            const int value5,
            const int value6,
            const int value7
        )
        :
        m_value1(value1),
        m_value2(value2),
        m_value3(value3),
        m_value4(value4),
        m_value5(value5),
        m_value6(value6),
        m_value7(value7)
        {}
    };

    struct Class8
    {
        int m_value1;
        int m_value2;
        int m_value3;
        int m_value4;
        int m_value5;
        int m_value6;
        int m_value7;
        int m_value8;
        
        Class8(
            const int value1,
            const int value2,
            const int value3,
            const int value4,
            const int value5,
            const int value6,
            const int value7,
            const int value8
        )
        :
        m_value1(value1),
        m_value2(value2),
        m_value3(value3),
        m_value4(value4),
        m_value5(value5),
        m_value6(value6),
        m_value7(value7),
        m_value8(value8)
        {}
    };

    struct Class9
    {
        int m_value1;
        int m_value2;
        int m_value3;
        int m_value4;
        int m_value5;
        int m_value6;
        int m_value7;
        int m_value8;
        int m_value9;
        
        Class9(
            const int value1,
            const int value2,
            const int value3,
            const int value4,
            const int value5,
            const int value6,
            const int value7,
            const int value8,
            const int value9
        )
        :
        m_value1(value1),
        m_value2(value2),
        m_value3(value3),
        m_value4(value4),
        m_value5(value5),
        m_value6(value6),
        m_value7(value7),
        m_value8(value8),
        m_value9(value9)
        {}
    };

    struct Class10
    {
        int m_value1;
        int m_value2;
        int m_value3;
        int m_value4;
        int m_value5;
        int m_value6;
        int m_value7;
        int m_value8;
        int m_value9;
        int m_value10;
        
        Class10(
            const int value1,
            const int value2,
            const int value3,
            const int value4,
            const int value5,
            const int value6,
            const int value7,
            const int value8,
            const int value9,
            const int value10
        )
        :
        m_value1(value1),
        m_value2(value2),
        m_value3(value3),
        m_value4(value4),
        m_value5(value5),
        m_value6(value6),
        m_value7(value7),
        m_value8(value8),
        m_value9(value9),
        m_value10(value10)
        {}
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
            const std::unique_ptr<Class0> p(tetengo2::make_unique<Class0>());

            BOOST_CHECK(p);
        }
        {
            const std::unique_ptr<Class1> p(
                tetengo2::make_unique<Class1>(42)
            );

            BOOST_CHECK(p);
            BOOST_CHECK_EQUAL(p->m_value1, 42);
        }
        {
            const std::unique_ptr<Class2> p(
                tetengo2::make_unique<Class2>(12, 34)
            );

            BOOST_CHECK(p);
            BOOST_CHECK_EQUAL(p->m_value1, 12);
            BOOST_CHECK_EQUAL(p->m_value2, 34);
        }
        {
            const std::unique_ptr<Class3> p(
                tetengo2::make_unique<Class3>(12, 34, 56)
            );

            BOOST_CHECK(p);
            BOOST_CHECK_EQUAL(p->m_value1, 12);
            BOOST_CHECK_EQUAL(p->m_value2, 34);
            BOOST_CHECK_EQUAL(p->m_value3, 56);
        }
        {
            const std::unique_ptr<Class4> p(
                tetengo2::make_unique<Class4>(12, 34, 56, 78)
            );

            BOOST_CHECK(p);
            BOOST_CHECK_EQUAL(p->m_value1, 12);
            BOOST_CHECK_EQUAL(p->m_value2, 34);
            BOOST_CHECK_EQUAL(p->m_value3, 56);
            BOOST_CHECK_EQUAL(p->m_value4, 78);
        }
        {
            const std::unique_ptr<Class5> p(
                tetengo2::make_unique<Class5>(12, 34, 56, 78, 90)
            );

            BOOST_CHECK(p);
            BOOST_CHECK_EQUAL(p->m_value1, 12);
            BOOST_CHECK_EQUAL(p->m_value2, 34);
            BOOST_CHECK_EQUAL(p->m_value3, 56);
            BOOST_CHECK_EQUAL(p->m_value4, 78);
            BOOST_CHECK_EQUAL(p->m_value5, 90);
        }
        {
            const std::unique_ptr<Class6> p(
                tetengo2::make_unique<Class6>(12, 34, 56, 78, 90, 12)
            );

            BOOST_CHECK(p);
            BOOST_CHECK_EQUAL(p->m_value1, 12);
            BOOST_CHECK_EQUAL(p->m_value2, 34);
            BOOST_CHECK_EQUAL(p->m_value3, 56);
            BOOST_CHECK_EQUAL(p->m_value4, 78);
            BOOST_CHECK_EQUAL(p->m_value5, 90);
            BOOST_CHECK_EQUAL(p->m_value6, 12);
        }
        {
            const std::unique_ptr<Class7> p(
                tetengo2::make_unique<Class7>(12, 34, 56, 78, 90, 12, 34)
            );

            BOOST_CHECK(p);
            BOOST_CHECK_EQUAL(p->m_value1, 12);
            BOOST_CHECK_EQUAL(p->m_value2, 34);
            BOOST_CHECK_EQUAL(p->m_value3, 56);
            BOOST_CHECK_EQUAL(p->m_value4, 78);
            BOOST_CHECK_EQUAL(p->m_value5, 90);
            BOOST_CHECK_EQUAL(p->m_value6, 12);
            BOOST_CHECK_EQUAL(p->m_value7, 34);
        }
        {
            const std::unique_ptr<Class8> p(
                tetengo2::make_unique<Class8>(12, 34, 56, 78, 90, 12, 34, 56)
            );

            BOOST_CHECK(p);
            BOOST_CHECK_EQUAL(p->m_value1, 12);
            BOOST_CHECK_EQUAL(p->m_value2, 34);
            BOOST_CHECK_EQUAL(p->m_value3, 56);
            BOOST_CHECK_EQUAL(p->m_value4, 78);
            BOOST_CHECK_EQUAL(p->m_value5, 90);
            BOOST_CHECK_EQUAL(p->m_value6, 12);
            BOOST_CHECK_EQUAL(p->m_value7, 34);
            BOOST_CHECK_EQUAL(p->m_value8, 56);
        }
        {
            const std::unique_ptr<Class9> p(
                tetengo2::make_unique<Class9>(
                    12, 34, 56, 78, 90, 12, 34, 56, 78
                )
            );

            BOOST_CHECK(p);
            BOOST_CHECK_EQUAL(p->m_value1, 12);
            BOOST_CHECK_EQUAL(p->m_value2, 34);
            BOOST_CHECK_EQUAL(p->m_value3, 56);
            BOOST_CHECK_EQUAL(p->m_value4, 78);
            BOOST_CHECK_EQUAL(p->m_value5, 90);
            BOOST_CHECK_EQUAL(p->m_value6, 12);
            BOOST_CHECK_EQUAL(p->m_value7, 34);
            BOOST_CHECK_EQUAL(p->m_value8, 56);
            BOOST_CHECK_EQUAL(p->m_value9, 78);
        }
        {
            const std::unique_ptr<Class10> p(
                tetengo2::make_unique<Class10>(
                    12, 34, 56, 78, 90, 12, 34, 56, 78, 90
                )
            );

            BOOST_CHECK(p);
            BOOST_CHECK_EQUAL(p->m_value1, 12);
            BOOST_CHECK_EQUAL(p->m_value2, 34);
            BOOST_CHECK_EQUAL(p->m_value3, 56);
            BOOST_CHECK_EQUAL(p->m_value4, 78);
            BOOST_CHECK_EQUAL(p->m_value5, 90);
            BOOST_CHECK_EQUAL(p->m_value6, 12);
            BOOST_CHECK_EQUAL(p->m_value7, 34);
            BOOST_CHECK_EQUAL(p->m_value8, 56);
            BOOST_CHECK_EQUAL(p->m_value9, 78);
            BOOST_CHECK_EQUAL(p->m_value10, 90);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

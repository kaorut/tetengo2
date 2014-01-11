/*! \file
    \brief Test of class bobura::view::scale_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <cstddef>
#include <string>

#include <boost/rational.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.view.scale_list.h"


namespace
{
    // types

    typedef boost::rational<int> scale_type;

    typedef bobura::view::scale_list<scale_type, std::size_t, std::string> scale_list_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(scale_list)
    // test cases

    BOOST_AUTO_TEST_CASE(size)
    {
        BOOST_TEST_PASSPOINT();

        const scale_list_type scale_list;

        BOOST_CHECK_EQUAL(scale_list.size(), 8U);
    }

    BOOST_AUTO_TEST_CASE(at)
    {
        BOOST_TEST_PASSPOINT();

        const scale_list_type scale_list;

        BOOST_CHECK(scale_list.at(0) == scale_type(1, 10));
        BOOST_CHECK(scale_list.at(1) == scale_type(1, 4));
        BOOST_CHECK(scale_list.at(2) == scale_type(1, 2));
        BOOST_CHECK(scale_list.at(3) == scale_type(3, 4));
        BOOST_CHECK(scale_list.at(4) == scale_type(1));
        BOOST_CHECK(scale_list.at(5) == scale_type(3, 2));
        BOOST_CHECK(scale_list.at(6) == scale_type(2));
        BOOST_CHECK(scale_list.at(7) == scale_type(4));
    }

    BOOST_AUTO_TEST_CASE(label_at)
    {
        BOOST_TEST_PASSPOINT();

        const scale_list_type scale_list;

        BOOST_CHECK(scale_list.label_at(0) == "10%");
        BOOST_CHECK(scale_list.label_at(1) == "25%");
        BOOST_CHECK(scale_list.label_at(2) == "50%");
        BOOST_CHECK(scale_list.label_at(3) == "75%");
        BOOST_CHECK(scale_list.label_at(4) == "100%");
        BOOST_CHECK(scale_list.label_at(5) == "150%");
        BOOST_CHECK(scale_list.label_at(6) == "200%");
        BOOST_CHECK(scale_list.label_at(7) == "400%");
    }

    BOOST_AUTO_TEST_CASE(index_of)
    {
        BOOST_TEST_PASSPOINT();

        const scale_list_type scale_list;

        BOOST_CHECK_EQUAL(*scale_list.index_of(scale_type(1, 10)), 0U);
        BOOST_CHECK_EQUAL(*scale_list.index_of(scale_type(1, 4)), 1U);
        BOOST_CHECK_EQUAL(*scale_list.index_of(scale_type(1, 2)), 2U);
        BOOST_CHECK_EQUAL(*scale_list.index_of(scale_type(3, 4)), 3U);
        BOOST_CHECK_EQUAL(*scale_list.index_of(scale_type(1)), 4U);
        BOOST_CHECK_EQUAL(*scale_list.index_of(scale_type(3, 2)), 5U);
        BOOST_CHECK_EQUAL(*scale_list.index_of(scale_type(2)), 6U);
        BOOST_CHECK_EQUAL(*scale_list.index_of(scale_type(4)), 7U);
        BOOST_CHECK(!scale_list.index_of(scale_type(3)));
    }

    BOOST_AUTO_TEST_CASE(larger)
    {
        BOOST_TEST_PASSPOINT();

        const scale_list_type scale_list;

        BOOST_CHECK(scale_list.larger(scale_type(7, 8)) == scale_type(1));
        BOOST_CHECK(scale_list.larger(scale_type(3, 2)) == scale_type(2));
        BOOST_CHECK(scale_list.larger(scale_type(4)) == scale_type(4));
        BOOST_CHECK(scale_list.larger(scale_type(5)) == scale_type(4));
    }

    BOOST_AUTO_TEST_CASE(smaller)
    {
        BOOST_TEST_PASSPOINT();

        const scale_list_type scale_list;

        BOOST_CHECK(scale_list.smaller(scale_type(1, 12)) == scale_type(1, 10));
        BOOST_CHECK(scale_list.smaller(scale_type(1, 10)) == scale_type(1, 10));
        BOOST_CHECK(scale_list.smaller(scale_type(7, 8)) == scale_type(3, 4));
        BOOST_CHECK(scale_list.smaller(scale_type(3, 2)) == scale_type(1));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

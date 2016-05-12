/*! \file
    \brief Test of class tetengo2::text::character_iterator.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include "test_tetengo2.type_list.h"


namespace
{
    // types

    using common_type_list_type = test_tetengo2::type_list::common;

    using string_type = common_type_list_type::string_type;

    using character_iterator_type = tetengo2::text::character_iterator<string_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(text)
BOOST_AUTO_TEST_SUITE(character_iterator)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const string_type string;
        const character_iterator_type iterator(string);
    }

    BOOST_AUTO_TEST_CASE(dereference)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Implement it.");
    }

    BOOST_AUTO_TEST_CASE(equal)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Implement it.");
    }

    BOOST_AUTO_TEST_CASE(increment)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Implement it.");
    }


BOOST_AUTO_TEST_SUITE_END()
    // test cases

    BOOST_AUTO_TEST_CASE(make_character_iterator)
    {
        BOOST_TEST_PASSPOINT();

        const string_type string;
        tetengo2::text::make_character_iterator(string);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

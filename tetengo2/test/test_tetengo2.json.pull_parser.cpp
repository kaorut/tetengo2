/*! \file
    \brief Test of class tetengo2::json::pull_parser.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.json.grammar.h"
#include "tetengo2.json.push_parser.h"

#include "tetengo2.json.pull_parser.h"


namespace
{
    // types

    typedef std::string::const_iterator iterator;

    typedef
        tetengo2::json::push_parser<
            iterator, tetengo2::json::grammar<iterator>, int, double
        >
        push_parser_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(json)
BOOST_AUTO_TEST_SUITE(pull_parser)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

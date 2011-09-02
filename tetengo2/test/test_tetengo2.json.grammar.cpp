/*! \file
    \brief Test of class tetengo2::json::grammar.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.json.grammar.h"


namespace
{
    // functions

    template <typename ForwardIterator, typename Parser, typename Attribute>
    bool full_match(
        const ForwardIterator first,
        const ForwardIterator last,
        const Parser&         parser,
        Attribute&            output
    )
    {
        ForwardIterator mutable_first = first;
        const bool result =
            boost::spirit::qi::phrase_parse(
                mutable_first, last, parser, boost::spirit::qi::space, output
            );
        return result && mutable_first == last;
    }
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(json)
BOOST_AUTO_TEST_SUITE(grammar)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const tetengo2::json::grammar<std::string::const_iterator> grammar;
    }

    BOOST_AUTO_TEST_CASE(parse)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(string)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string input("\"hoge\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.string(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == "\"hoge\"");
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

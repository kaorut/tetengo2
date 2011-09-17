/*! \file
    \brief Test of class tetengo2::json::push_parser.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.json.grammar.h"
#include "tetengo2.unique.h"

#include "tetengo2.json.push_parser.h"


namespace
{
    // types

    typedef tetengo2::json::grammar<std::string::const_iterator> grammar_type;

    typedef
        tetengo2::json::push_parser<
            std::string::const_iterator, grammar_type, int, double
        >
        push_parser_type;


    // functions

    void observer0(
        push_parser_type::structure_type    structure,
        const push_parser_type::value_type& value
        )
    {}


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(json)
BOOST_AUTO_TEST_SUITE(push_parser)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string input;

            push_parser_type parser(
                input.begin(),
                input.end(),
                tetengo2::make_unique<grammar_type>()
            );
        }
        {
            const std::string input = "{}";

            push_parser_type parser(
                input.begin(),
                input.end(),
                tetengo2::make_unique<grammar_type>()
            );
        }
    }

    BOOST_AUTO_TEST_CASE(structure_passed)
    {
        BOOST_TEST_PASSPOINT();

        const std::string input = "{}";

        {
            const std::string input = "{}";

            push_parser_type parser(
                input.begin(),
                input.end(),
                tetengo2::make_unique<grammar_type>()
            );

            parser.structure_passed().connect(observer0);
        }
        {
            const std::string input = "{}";

            const push_parser_type parser(
                input.begin(),
                input.end(),
                tetengo2::make_unique<grammar_type>()
            );

            parser.structure_passed();
        }
    }

    BOOST_AUTO_TEST_CASE(parse)
    {
        BOOST_TEST_PASSPOINT();

    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

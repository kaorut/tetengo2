/*! \file
    \brief Test of class tetengo2::json::push_parser.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <string>
#include <utility>

#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.cpp11.h"
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

    typedef
        std::pair<
            push_parser_type::structure_type,
            boost::optional<push_parser_type::value_type>
        >
        parsed_structure_type;


    // functions

    void observer0(
        const push_parser_type::structure_type               structure,
        const boost::optional<push_parser_type::value_type>& value
    )
    {}

    void observer1(
        const push_parser_type::structure_type               structure,
        const boost::optional<push_parser_type::value_type>& value,
        std::vector<parsed_structure_type>&                  parsed_structures
    )
    {
        parsed_structures.push_back(std::make_pair(structure, value));
    }


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

        {
            const std::string input;
            std::vector<parsed_structure_type> parsed;

            push_parser_type parser(
                input.begin(),
                input.end(),
                tetengo2::make_unique<grammar_type>()
            );
            parser.structure_passed().connect(
                TETENGO2_CPP11_BIND(
                    observer1,
                    tetengo2::cpp11::placeholders_1(),
                    tetengo2::cpp11::placeholders_2(),
                    tetengo2::cpp11::ref(parsed)
                )
            );

            BOOST_CHECK(!parser.parse());
        }
        {
            const std::string input = "[]";
            std::vector<parsed_structure_type> parsed;

            push_parser_type parser(
                input.begin(),
                input.end(),
                tetengo2::make_unique<grammar_type>()
            );
            parser.structure_passed().connect(
                TETENGO2_CPP11_BIND(
                    observer1,
                    tetengo2::cpp11::placeholders_1(),
                    tetengo2::cpp11::placeholders_2(),
                    tetengo2::cpp11::ref(parsed)
                )
            );

            BOOST_CHECK(parser.parse());
            BOOST_CHECK_EQUAL(parsed.size(), 2);

            BOOST_CHECK_EQUAL(
                parsed[0].first, push_parser_type::structure_array_begin
            );

            BOOST_CHECK_EQUAL(
                parsed[1].first, push_parser_type::structure_array_end
            );
        }
        {
            const std::string input =
                "["
                "    false,"
                "    null,"
                "    true,"
                "    \"hoge\""
                "]";
            std::vector<parsed_structure_type> parsed;

            push_parser_type parser(
                input.begin(),
                input.end(),
                tetengo2::make_unique<grammar_type>()
            );
            parser.structure_passed().connect(
                TETENGO2_CPP11_BIND(
                    observer1,
                    tetengo2::cpp11::placeholders_1(),
                    tetengo2::cpp11::placeholders_2(),
                    tetengo2::cpp11::ref(parsed)
                )
            );

            BOOST_CHECK(parser.parse());
            BOOST_CHECK_EQUAL(parsed.size(), 6);

            BOOST_CHECK_EQUAL(
                parsed[0].first, push_parser_type::structure_array_begin
            );

            BOOST_CHECK_EQUAL(
                parsed[5].first, push_parser_type::structure_array_end
            );
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

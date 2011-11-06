/*! \file
    \brief Test of class tetengo2::json::pull_parser.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <boost/test/unit_test.hpp>

#include "tetengo2.json.grammar.h"
#include "tetengo2.json.push_parser.h"
#include "tetengo2.unique.h"

#include "tetengo2.json.pull_parser.h"


namespace
{
    // types

    typedef std::string::const_iterator iterator;

    typedef tetengo2::json::grammar<iterator> grammar_type;

    typedef
        tetengo2::json::push_parser<iterator, grammar_type, int, double>
        push_parser_type;

    typedef
        tetengo2::json::pull_parser<push_parser_type, std::size_t>
        pull_parser_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(json)
BOOST_AUTO_TEST_SUITE(pull_parser)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::string json_text;
        std::unique_ptr<push_parser_type> p_push_parser(
            tetengo2::make_unique<push_parser_type>(
                json_text.begin(),
                json_text.end(),
                tetengo2::make_unique<grammar_type>()
            )
        );

        const pull_parser_type pull_parser(std::move(p_push_parser), 3);
    }

    BOOST_AUTO_TEST_CASE(has_next)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::string json_text;
            std::unique_ptr<push_parser_type> p_push_parser(
                tetengo2::make_unique<push_parser_type>(
                    json_text.begin(),
                    json_text.end(),
                    tetengo2::make_unique<grammar_type>()
                )
            );

            const pull_parser_type pull_parser(std::move(p_push_parser), 3);

            BOOST_CHECK(!pull_parser.has_next());
        }
        {
            std::string json_text = "{}";
            std::unique_ptr<push_parser_type> p_push_parser(
                tetengo2::make_unique<push_parser_type>(
                    json_text.begin(),
                    json_text.end(),
                    tetengo2::make_unique<grammar_type>()
                )
            );

            const pull_parser_type pull_parser(std::move(p_push_parser), 3);

            BOOST_CHECK(pull_parser.has_next());
        }
    }

    BOOST_AUTO_TEST_CASE(next)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

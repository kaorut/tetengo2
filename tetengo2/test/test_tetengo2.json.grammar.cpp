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
            boost::spirit::qi::parse(mutable_first, last, parser, output);
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

    BOOST_AUTO_TEST_CASE(json_text)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string input("{}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.json_text(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("[]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.json_text(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.json_text(), output);

            BOOST_CHECK(!result);
        }
    }
    BOOST_AUTO_TEST_CASE(value)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string input("false");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.value(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("null");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.value(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("true");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.value(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("{}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.value(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("[]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.value(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("hoge");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.value(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.value(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("\"hoge\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.value(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
    }

    BOOST_AUTO_TEST_CASE(object)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string input("{}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.object(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("{\"hoge\": 42}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.object(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("{\"hoge\": 42, \"hoge\": 42}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.object(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input(
                "{\"hoge\": 42, \"hoge\": 42, \"hoge\": 42}"
            );

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.object(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("{\n  \"hoge\": 42\n,\t\"hoge\": 42}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.object(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("{\"hoge\": 42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.object(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("{\"hoge\": 42,}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.object(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("[]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.object(), output);

            BOOST_CHECK(!result);
        }
    }

    BOOST_AUTO_TEST_CASE(member)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string input("\"hoge\": 42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.member(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
    }

    BOOST_AUTO_TEST_CASE(array)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string input("[]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.array(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("[42]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.array(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("[42, 42]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.array(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("[42, 42, 42]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.array(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("[\n  42\n,\t42]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.array(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("[42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.array(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("[42,]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.array(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("{}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.array(), output);

            BOOST_CHECK(!result);
        }
    }

    BOOST_AUTO_TEST_CASE(number)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string input("42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("0");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("02");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("-42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("-0");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("-02");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42.42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("42.42.42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42e+42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("42.42e+42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("42E+42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("42e-42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("42e+42.42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42e+42e+42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42f+42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42e*42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42e");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.number(), output);

            BOOST_CHECK(!result);
        }
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
            BOOST_CHECK(output == input);
        }
        {
            const std::wstring input(L"\"hoge\"");

            const tetengo2::json::grammar<std::wstring::const_iterator> g;
            std::wstring output;
            const bool result =
                full_match(input.begin(), input.end(), g.string(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("\"hoge\"fuga");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.string(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"hoge");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.string(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("hoge");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.string(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"a\\\"a\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.string(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("\"a\"a\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.string(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"\\n\\u12ABXYZ\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.string(), output);

            BOOST_CHECK(result);
            BOOST_CHECK(output == input);
        }
        {
            const std::string input("\"\\m\\u12ABXYZ\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.string(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"\\n\\u12PQXYZ\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.string(), output);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"\\n\\u12\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            std::string output;
            const bool result =
                full_match(input.begin(), input.end(), g.string(), output);

            BOOST_CHECK(!result);
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

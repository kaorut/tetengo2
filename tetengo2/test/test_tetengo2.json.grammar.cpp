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

    template <typename ForwardIterator, typename Parser>
    bool full_match(
        const ForwardIterator first,
        const ForwardIterator last,
        const Parser&         parser
    )
    {
        ForwardIterator mutable_first = first;
        const bool result =
            boost::spirit::qi::parse(mutable_first, last, parser);
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

        {
            const std::string input("{}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result = full_match(input.begin(), input.end(), g);

            BOOST_CHECK(result);
        }
        {
            const std::string input("[]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result = full_match(input.begin(), input.end(), g);

            BOOST_CHECK(result);
        }
        {
            const std::string input("");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result = full_match(input.begin(), input.end(), g);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result = full_match(input.begin(), input.end(), g);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("[[[]], {}]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result = full_match(input.begin(), input.end(), g);

            BOOST_CHECK(result);
        }
        {
            const std::string input("[[[]]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result = full_match(input.begin(), input.end(), g);

            BOOST_CHECK(!result);
        }
        {
            const std::string input(
                "[\n"
                "    42,\n"
                "    \"hoge\",\n"
                "    {\"key\": {\"value-key\": 42}},\n"
                "    [1, 2, 3, \"foo\", \"bar\"]\n"
                "]\n"
            );

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result = full_match(input.begin(), input.end(), g);

            BOOST_CHECK(result);
        }
    }

    BOOST_AUTO_TEST_CASE(json_text)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::json::grammar<std::string::const_iterator> g;

            BOOST_CHECK(g.json_text().name() == "JSON-text");
        }
        {
            const std::string input("{}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.json_text());

            BOOST_CHECK(result);
        }
        {
            const std::string input("[]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.json_text());

            BOOST_CHECK(result);
        }
        {
            const std::string input("");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.json_text());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.json_text());

            BOOST_CHECK(!result);
        }
    }

    BOOST_AUTO_TEST_CASE(value)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::json::grammar<std::string::const_iterator> g;

            BOOST_CHECK(g.value().name() == "value");
        }
        {
            const std::string input("false");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(result);
        }
        {
            const std::string input("null");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(result);
        }
        {
            const std::string input("true");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(result);
        }
        {
            const std::string input("{}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(result);
        }
        {
            const std::string input("[]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(result);
        }
        {
            const std::string input("hoge");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(result);
        }
        {
            const std::string input("\"hoge\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(result);
        }
    }

    BOOST_AUTO_TEST_CASE(object)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::json::grammar<std::string::const_iterator> g;

            BOOST_CHECK(g.object().name() == "object");
        }
        {
            const std::string input("{}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(result);
        }
        {
            const std::string input("{\"hoge\": 42}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(result);
        }
        {
            const std::string input("{\"hoge\": 42, \"hoge\": 42}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(result);
        }
        {
            const std::string input(
                "{\"hoge\": 42, \"hoge\": 42, \"hoge\": 42}"
            );

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(result);
        }
        {
            const std::string input("{\n  \"hoge\": 42\n,\t\"hoge\": 42}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(result);
        }
        {
            const std::string input("{\"hoge\": 42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("{\"hoge\": 42,}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("[]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(!result);
        }
    }

    BOOST_AUTO_TEST_CASE(member)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::json::grammar<std::string::const_iterator> g;

            BOOST_CHECK(g.member().name() == "member");
        }
        {
            const std::string input("\"hoge\": 42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.member());

            BOOST_CHECK(result);
        }
        {
            const std::string input("\"hoge\"\t:\n\n42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.member());

            BOOST_CHECK(result);
        }
        {
            const std::string input("42: \"hoge\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.member());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"hoge\": 42: 42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.member());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"hoge\":");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.member());

            BOOST_CHECK(!result);
        }
    }

    BOOST_AUTO_TEST_CASE(array)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::json::grammar<std::string::const_iterator> g;

            BOOST_CHECK(g.array().name() == "array");
        }
        {
            const std::string input("[]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(result);
        }
        {
            const std::string input("[42]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(result);
        }
        {
            const std::string input("[42, 42]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(result);
        }
        {
            const std::string input("[42, 42, 42]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(result);
        }
        {
            const std::string input("[\n  42\n,\t42]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(result);
        }
        {
            const std::string input("[42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("[42,]");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("{}");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(!result);
        }
    }

    BOOST_AUTO_TEST_CASE(number)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::json::grammar<std::string::const_iterator> g;

            BOOST_CHECK(g.number().name() == "number");
        }
        {
            const std::string input("42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("0");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("02");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("-42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("-0");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("-02");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42.42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("42.42.42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42e+42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("42.42e+42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("42E+42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("42e-42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("42e+42.42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42e+42e+42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42f+42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42e*42");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42e");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
    }

    BOOST_AUTO_TEST_CASE(string)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::json::grammar<std::string::const_iterator> g;

            BOOST_CHECK(g.string().name() == "string");
        }
        {
            const std::string input("\"hoge\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(result);
        }
        {
            const std::wstring input(L"\"hoge\"");

            const tetengo2::json::grammar<std::wstring::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(result);
        }
        {
            const std::string input("\"hoge\"fuga");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"hoge");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("hoge");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"a\\\"a\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(result);
        }
        {
            const std::string input("\"a\"a\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"\\n\\u12ABXYZ\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(result);
        }
        {
            const std::string input("\"\\m\\u12ABXYZ\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"\\n\\u12PQXYZ\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"\\n\\u12\"");

            const tetengo2::json::grammar<std::string::const_iterator> g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(!result);
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

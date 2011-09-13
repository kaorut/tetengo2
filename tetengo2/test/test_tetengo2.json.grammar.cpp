/*! \file
    \brief Test of class tetengo2::json::grammar.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <cassert>
#include <stdexcept>
//#include <string>

//#include <boost/spirit/include/qi.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.cpp0x.h"

#include "tetengo2.json.grammar.h"


namespace
{
    // types

    typedef
        tetengo2::json::grammar<std::string::const_iterator>
        grammar_type;

    typedef
        tetengo2::json::grammar<std::wstring::const_iterator>
        wide_grammar_type;

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

    void on_structure(
        std::string&                            output,
        const grammar_type::structure_type_type type
    )
    {
        switch (type)
        {
        case grammar_type::structure_type_object_begin:
            {
                output += "OB, ";
                break;
            }
        case grammar_type::structure_type_object_end:
            {
                output += "OE, ";
                break;
            }
        case grammar_type::structure_type_member_begin:
            {
                output += "MB, ";
                break;
            }
        case grammar_type::structure_type_member_end:
            {
                output += "ME, ";
                break;
            }
        case grammar_type::structure_type_array_begin:
            {
                output += "AB, ";
                break;
            }
        case grammar_type::structure_type_array_end:
            {
                output += "AE, ";
                break;
            }
        default:
            {
                assert(false);
                throw std::logic_error("Must not come here.");
            }
        }
    }

    void on_value(
        std::string&                        output,
        const grammar_type::value_type_type type,
        const std::string&                  parsed
    )
    {
        switch (type)
        {
        case grammar_type::value_type_string:
            {
                output += "S:";
                break;
            }
        case grammar_type::value_type_number:
            {
                output += "N:";
                break;
            }
        case grammar_type::value_type_boolean:
            {
                output += "B:";
                break;
            }
        case grammar_type::value_type_null:
            {
                output += "L:";
                break;
            }
        default:
            {
                assert(false);
                throw std::logic_error("Must not come here.");
            }
        }

        output += parsed + ", ";
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(json)
BOOST_AUTO_TEST_SUITE(grammar)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const grammar_type grammar;
    }

    BOOST_AUTO_TEST_CASE(add_structure_observer)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string input("{}");

            grammar_type g;
            std::string output;
            g.add_structure_observer(
                TETENGO2_CPP11_BIND(
                    on_structure,
                    tetengo2::cpp11::ref(output),
                    tetengo2::cpp11::placeholders_1()
                )
            );
            g.add_value_observer(
                TETENGO2_CPP11_BIND(
                    on_value,
                    tetengo2::cpp11::ref(output),
                    tetengo2::cpp11::placeholders_1(),
                    tetengo2::cpp11::placeholders_2()
                )
            );

            const bool result = full_match(input.begin(), input.end(), g);
            BOOST_CHECK(result);
            BOOST_CHECK(output == "OB, OE, ");
        }
        {
            const std::string input(
                "{\n"
                "    \"hoge\": 42,\n"
                "    \"fuga\": [42, 42, 42]\n"
                "}\n"
            );

            grammar_type g;
            std::string output;
            g.add_structure_observer(
                TETENGO2_CPP11_BIND(
                    on_structure,
                    tetengo2::cpp11::ref(output),
                    tetengo2::cpp11::placeholders_1()
                )
            );
            g.add_value_observer(
                TETENGO2_CPP11_BIND(
                    on_value,
                    tetengo2::cpp11::ref(output),
                    tetengo2::cpp11::placeholders_1(),
                    tetengo2::cpp11::placeholders_2()
                )
            );

            const bool result = full_match(input.begin(), input.end(), g);
            BOOST_CHECK(result);
            BOOST_CHECK(
                output ==
                "OB, "
                "MB, S:\"hoge\", N:42, ME, "
                "MB, S:\"fuga\", AB, N:42, N:42, N:42, AE, ME, "
                "OE, "
            );
        }
    }

    BOOST_AUTO_TEST_CASE(add_value_observer)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string input("[\"hoge\", 42, true, false, null]");

            grammar_type g;
            std::string output;
            g.add_structure_observer(
                TETENGO2_CPP11_BIND(
                    on_structure,
                    tetengo2::cpp11::ref(output),
                    tetengo2::cpp11::placeholders_1()
                )
            );
            g.add_value_observer(
                TETENGO2_CPP11_BIND(
                    on_value,
                    tetengo2::cpp11::ref(output),
                    tetengo2::cpp11::placeholders_1(),
                    tetengo2::cpp11::placeholders_2()
                )
            );

            const bool result = full_match(input.begin(), input.end(), g);
            BOOST_CHECK(result);
            BOOST_CHECK(
                output ==
                "AB, S:\"hoge\", N:42, B:true, B:false, L:null, AE, "
            );
        }
    }

    BOOST_AUTO_TEST_CASE(parse)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string input("{}");

            const grammar_type g;
            const bool result = full_match(input.begin(), input.end(), g);

            BOOST_CHECK(result);
        }
        {
            const std::string input("[]");

            const grammar_type g;
            const bool result = full_match(input.begin(), input.end(), g);

            BOOST_CHECK(result);
        }
        {
            const std::string input("");

            const grammar_type g;
            const bool result = full_match(input.begin(), input.end(), g);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42");

            const grammar_type g;
            const bool result = full_match(input.begin(), input.end(), g);

            BOOST_CHECK(!result);
        }
        {
            const std::string input("[[[]], {}]");

            const grammar_type g;
            const bool result = full_match(input.begin(), input.end(), g);

            BOOST_CHECK(result);
        }
        {
            const std::string input("[[[]]");

            const grammar_type g;
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

            const grammar_type g;
            const bool result = full_match(input.begin(), input.end(), g);

            BOOST_CHECK(result);
        }
    }

    BOOST_AUTO_TEST_CASE(json_text)
    {
        BOOST_TEST_PASSPOINT();

        {
            const grammar_type g;

            BOOST_CHECK(g.json_text().name() == "JSON-text");
        }
        {
            const std::string input("{}");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.json_text());

            BOOST_CHECK(result);
        }
        {
            const std::string input("[]");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.json_text());

            BOOST_CHECK(result);
        }
        {
            const std::string input("");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.json_text());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.json_text());

            BOOST_CHECK(!result);
        }
    }

    BOOST_AUTO_TEST_CASE(value)
    {
        BOOST_TEST_PASSPOINT();

        {
            const grammar_type g;

            BOOST_CHECK(g.value().name() == "value");
        }
        {
            const std::string input("false");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(result);
        }
        {
            const std::string input("null");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(result);
        }
        {
            const std::string input("true");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(result);
        }
        {
            const std::string input("{}");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(result);
        }
        {
            const std::string input("[]");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(result);
        }
        {
            const std::string input("hoge");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(result);
        }
        {
            const std::string input("\"hoge\"");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.value());

            BOOST_CHECK(result);
        }
    }

    BOOST_AUTO_TEST_CASE(object)
    {
        BOOST_TEST_PASSPOINT();

        {
            const grammar_type g;

            BOOST_CHECK(g.object().name() == "object");
        }
        {
            const std::string input("{}");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(result);
        }
        {
            const std::string input("{\"hoge\": 42}");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(result);
        }
        {
            const std::string input("{\"hoge\": 42, \"hoge\": 42}");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(result);
        }
        {
            const std::string input(
                "{\"hoge\": 42, \"hoge\": 42, \"hoge\": 42}"
            );

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(result);
        }
        {
            const std::string input("{\n  \"hoge\": 42\n,\t\"hoge\": 42}");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(result);
        }
        {
            const std::string input("{\"hoge\": 42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("{\"hoge\": 42,}");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("[]");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.object());

            BOOST_CHECK(!result);
        }
    }

    BOOST_AUTO_TEST_CASE(member)
    {
        BOOST_TEST_PASSPOINT();

        {
            const grammar_type g;

            BOOST_CHECK(g.member().name() == "member");
        }
        {
            const std::string input("\"hoge\": 42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.member());

            BOOST_CHECK(result);
        }
        {
            const std::string input("\"hoge\"\t:\n\n42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.member());

            BOOST_CHECK(result);
        }
        {
            const std::string input("42: \"hoge\"");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.member());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"hoge\": 42: 42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.member());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"hoge\":");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.member());

            BOOST_CHECK(!result);
        }
    }

    BOOST_AUTO_TEST_CASE(array)
    {
        BOOST_TEST_PASSPOINT();

        {
            const grammar_type g;

            BOOST_CHECK(g.array().name() == "array");
        }
        {
            const std::string input("[]");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(result);
        }
        {
            const std::string input("[42]");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(result);
        }
        {
            const std::string input("[42, 42]");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(result);
        }
        {
            const std::string input("[42, 42, 42]");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(result);
        }
        {
            const std::string input("[\n  42\n,\t42]");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(result);
        }
        {
            const std::string input("[42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("[42,]");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("{}");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.array());

            BOOST_CHECK(!result);
        }
    }

    BOOST_AUTO_TEST_CASE(number)
    {
        BOOST_TEST_PASSPOINT();

        {
            const grammar_type g;

            BOOST_CHECK(g.number().name() == "number");
        }
        {
            const std::string input("42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("0");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("02");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("-42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("-0");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("-02");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42.42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("42.42.42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42e+42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("42.42e+42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("42E+42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("42e-42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(result);
        }
        {
            const std::string input("42e+42.42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42e+42e+42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42f+42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42e*42");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("42e");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.number());

            BOOST_CHECK(!result);
        }
    }

    BOOST_AUTO_TEST_CASE(string)
    {
        BOOST_TEST_PASSPOINT();

        {
            const grammar_type g;

            BOOST_CHECK(g.string().name() == "string");
        }
        {
            const std::string input("\"hoge\"");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(result);
        }
        {
            const std::wstring input(L"\"hoge\"");

            const wide_grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(result);
        }
        {
            const std::string input("\"hoge\"fuga");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"hoge");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("hoge");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"a\\\"a\"");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(result);
        }
        {
            const std::string input("\"a\"a\"");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"\\n\\u12ABXYZ\"");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(result);
        }
        {
            const std::string input("\"\\m\\u12ABXYZ\"");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"\\n\\u12PQXYZ\"");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(!result);
        }
        {
            const std::string input("\"\\n\\u12\"");

            const grammar_type g;
            const bool result =
                full_match(input.begin(), input.end(), g.string());

            BOOST_CHECK(!result);
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

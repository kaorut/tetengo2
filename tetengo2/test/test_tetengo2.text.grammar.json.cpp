/*! \file
    \brief Test of class tetengo2::text::grammar::json.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <stdexcept>
//#include <string>
//#include <tuple>
//#include <vector>

//#include <boost/spirit/include/qi.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/throw_exception.hpp>

#include "tetengo2.cpp11.h"

#include "tetengo2.text.grammar.json.h"


namespace
{
    // types

    typedef
        tetengo2::text::grammar::json<std::string::const_iterator>
        grammar_type;

    typedef grammar_type::structure_attribute_type structure_attribute_type;


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

    void structure_attribute_passed(
        std::string&                    output,
        const structure_attribute_type& structure_attribute
    );

    void structure_begun(
        std::string&                                 output,
        const std::string&                           type,
        const std::vector<structure_attribute_type>& structure_attributes
    )
    {
        if      (type == "object")
        {
            output += "OB, ";
        }
        else if (type == "member")
        {
            output += "MB, ";
            std::for_each(
                structure_attributes.begin(),
                structure_attributes.end(),
                TETENGO2_CPP11_BIND(
                    structure_attribute_passed,
                    tetengo2::cpp11::ref(output),
                    tetengo2::cpp11::placeholders_1()
                )
            );
        }
        else if (type == "array")
        {
            output += "AB, ";
        }
        else
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Must not come here."));
        }
    }

    void structure_ended(std::string& output, const std::string& type)
    {
        if      (type == "object")
        {
            output += "OE, ";
        }
        else if (type == "member")
        {
            output += "ME, ";
        }
        else if (type == "array")
        {
            output += "AE, ";
        }
        else
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Must not come here."));
        }
    }

    void value_passed(
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
                BOOST_THROW_EXCEPTION(
                    std::logic_error("Must not come here.")
                );
            }
        }

        output += parsed + ", ";
    }

    void structure_attribute_passed(
        std::string&                    output,
        const structure_attribute_type& structure_attribute
    )
    {
        value_passed(
            output,
            std::get<1>(structure_attribute),
            std::get<2>(structure_attribute)
        );
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(text)
BOOST_AUTO_TEST_SUITE(grammar)
BOOST_AUTO_TEST_SUITE(json)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const grammar_type grammar;
    }

    BOOST_AUTO_TEST_CASE(on_structure_begin_end)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string input("{}");

            grammar_type g;
            std::string output;
            g.on_structure_begin().connect(
                TETENGO2_CPP11_BIND(
                    structure_begun,
                    tetengo2::cpp11::ref(output),
                    tetengo2::cpp11::placeholders_1(),
                    tetengo2::cpp11::placeholders_2()
                )
            );
            g.on_structure_end().connect(
                TETENGO2_CPP11_BIND(
                    structure_ended,
                    tetengo2::cpp11::ref(output),
                    tetengo2::cpp11::placeholders_1()
                )
            );
            g.on_value().connect(
                TETENGO2_CPP11_BIND(
                    value_passed,
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
            g.on_structure_begin().connect(
                TETENGO2_CPP11_BIND(
                    structure_begun,
                    tetengo2::cpp11::ref(output),
                    tetengo2::cpp11::placeholders_1(),
                    tetengo2::cpp11::placeholders_2()
                )
            );
            g.on_structure_end().connect(
                TETENGO2_CPP11_BIND(
                    structure_ended,
                    tetengo2::cpp11::ref(output),
                    tetengo2::cpp11::placeholders_1()
                )
            );
            g.on_value().connect(
                TETENGO2_CPP11_BIND(
                    value_passed,
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

    BOOST_AUTO_TEST_CASE(on_value)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string input("[\"hoge\", 42, true, false, null]");

            grammar_type g;
            std::string output;
            g.on_structure_begin().connect(
                TETENGO2_CPP11_BIND(
                    structure_begun,
                    tetengo2::cpp11::ref(output),
                    tetengo2::cpp11::placeholders_1(),
                    tetengo2::cpp11::placeholders_2()
                )
            );
            g.on_structure_end().connect(
                TETENGO2_CPP11_BIND(
                    structure_ended,
                    tetengo2::cpp11::ref(output),
                    tetengo2::cpp11::placeholders_1()
                )
            );
            g.on_value().connect(
                TETENGO2_CPP11_BIND(
                    value_passed,
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
BOOST_AUTO_TEST_SUITE_END()

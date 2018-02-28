/*! \file
    \brief Test of class tetengo2::text::grammar::json.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/text/grammar/grammar.h>
#include <tetengo2/text/grammar/json.h>


namespace {
    // types

    using grammar_type = tetengo2::text::grammar::json<std::string::const_iterator>;

    using structure_attribute_type = tetengo2::text::grammar::structure_attribute<std::string>;

    using value_type_type = structure_attribute_type::value_type_type;


    // functions

    template <typename ForwardIterator, typename Parser>
    bool full_match(const ForwardIterator first, const ForwardIterator last, const Parser& parser)
    {
        auto       mutable_first = first;
        const auto result = boost::spirit::qi::parse(mutable_first, last, parser);
        return result && mutable_first == last;
    }

    void structure_attribute_passed(std::string& output, const structure_attribute_type& structure_attribute);

    bool structure_begun(
        std::string&                                 output,
        const std::string&                           type,
        const std::vector<structure_attribute_type>& structure_attributes)
    {
        if (type == "object")
        {
            output += "OB, ";
        }
        else if (type == "member")
        {
            output += "MB, ";
            std::for_each(
                structure_attributes.begin(),
                structure_attributes.end(),
                [&output](const structure_attribute_type& structure_attribute) {
                    structure_attribute_passed(output, structure_attribute);
                });
        }
        else if (type == "array")
        {
            output += "AB, ";
        }
        else
        {
            assert(false);
            BOOST_THROW_EXCEPTION((std::logic_error{ "Must not come here." }));
        }

        return true;
    }

    bool structure_ended(std::string& output, const std::string& type)
    {
        if (type == "object")
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
            BOOST_THROW_EXCEPTION((std::logic_error{ "Must not come here." }));
        }

        return true;
    }

    bool value_passed(std::string& output, const value_type_type type, const std::string& parsed)
    {
        switch (type)
        {
        case value_type_type::string:
        {
            output += "S:";
            break;
        }
        case value_type_type::number:
        {
            output += "N:";
            break;
        }
        case value_type_type::boolean:
        {
            output += "B:";
            break;
        }
        case value_type_type::null:
        {
            output += "L:";
            break;
        }
        default:
        {
            assert(false);
            BOOST_THROW_EXCEPTION((std::logic_error{ "Must not come here." }));
        }
        }

        output += parsed + ", ";

        return true;
    }

    void structure_attribute_passed(std::string& output, const structure_attribute_type& structure_attribute)
    {
        value_passed(output, structure_attribute.value_type(), structure_attribute.attribute());
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

                    const grammar_type grammar{};
                }

                BOOST_AUTO_TEST_CASE(on_structure_begin_end)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const std::string input{ "{}" };

                        grammar_type g{};
                        std::string  output{};
                        g.on_structure_begin().connect(
                            [&output](
                                const std::string&                           type,
                                const std::vector<structure_attribute_type>& structure_attributes) {
                                return structure_begun(output, type, structure_attributes);
                            });
                        g.on_structure_end().connect(
                            [&output](
                                const std::string&                           type,
                                const std::vector<structure_attribute_type>& structure_attributes) {
                                boost::ignore_unused(structure_attributes);

                                return structure_ended(output, type);
                            });
                        g.on_value().connect([&output](const value_type_type type, const std::string& parsed) {
                            return value_passed(output, type, parsed);
                        });

                        const auto result = full_match(input.begin(), input.end(), g);
                        BOOST_TEST(result);
                        BOOST_CHECK(output == "OB, OE, ");
                    }
                    {
                        const std::string input{
                            "{\n"
                            "    \"hoge\": 42,\n"
                            "    \"fuga\": [42, 42, 42]\n"
                            "}\n"
                        };

                        grammar_type g{};
                        std::string  output{};
                        g.on_structure_begin().connect(
                            [&output](
                                const std::string&                           type,
                                const std::vector<structure_attribute_type>& structure_attributes) {
                                return structure_begun(output, type, structure_attributes);
                            });
                        g.on_structure_end().connect(
                            [&output](
                                const std::string&                           type,
                                const std::vector<structure_attribute_type>& structure_attributes) {
                                boost::ignore_unused(structure_attributes);

                                return structure_ended(output, type);
                            });
                        g.on_value().connect([&output](const value_type_type type, const std::string& parsed) {
                            return value_passed(output, type, parsed);
                        });

                        const auto result = full_match(input.begin(), input.end(), g);
                        BOOST_TEST(result);
                        BOOST_CHECK(
                            output ==
                            "OB, "
                            "MB, S:\"hoge\", N:42, ME, "
                            "MB, S:\"fuga\", AB, N:42, N:42, N:42, AE, ME, "
                            "OE, ");
                    }
                }

                BOOST_AUTO_TEST_CASE(on_value)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const std::string input{ "[\"hoge\", 42, true, false, null]" };

                        grammar_type g{};
                        std::string  output{};
                        g.on_structure_begin().connect(
                            [&output](
                                const std::string&                           type,
                                const std::vector<structure_attribute_type>& structure_attributes) {
                                return structure_begun(output, type, structure_attributes);
                            });
                        g.on_structure_end().connect(
                            [&output](
                                const std::string&                           type,
                                const std::vector<structure_attribute_type>& structure_attributes) {
                                boost::ignore_unused(structure_attributes);

                                return structure_ended(output, type);
                            });
                        g.on_value().connect([&output](const value_type_type type, const std::string& parsed) {
                            return value_passed(output, type, parsed);
                        });

                        const auto result = full_match(input.begin(), input.end(), g);
                        BOOST_TEST(result);
                        BOOST_CHECK(output == "AB, S:\"hoge\", N:42, B:true, B:false, L:null, AE, ");
                    }
                }

                BOOST_AUTO_TEST_CASE(parse)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const std::string input{ "{}" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g);

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "[]" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g);

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g);

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g);

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "[[[]], {}]" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g);

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "[[[]]" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g);

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{
                            "[\n"
                            "    42,\n"
                            "    \"hoge\",\n"
                            "    {\"key\": {\"value-key\": 42}},\n"
                            "    [1, 2, 3, \"foo\", \"bar\"]\n"
                            "]\n"
                        };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g);

                        BOOST_TEST(result);
                    }
                }

                BOOST_AUTO_TEST_CASE(json_text)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const grammar_type g{};

                        BOOST_CHECK(g.json_text().name() == "JSON-text");
                    }
                    {
                        const std::string input{ "{}" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.json_text());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "[]" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.json_text());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.json_text());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.json_text());

                        BOOST_TEST(!result);
                    }
                }

                BOOST_AUTO_TEST_CASE(value)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const grammar_type g{};

                        BOOST_CHECK(g.value().name() == "value");
                    }
                    {
                        const std::string input{ "false" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.value());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "null" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.value());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "true" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.value());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "{}" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.value());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "[]" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.value());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "hoge" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.value());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.value());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "\"hoge\"" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.value());

                        BOOST_TEST(result);
                    }
                }

                BOOST_AUTO_TEST_CASE(object)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const grammar_type g{};

                        BOOST_CHECK(g.object().name() == "object");
                    }
                    {
                        const std::string input{ "{}" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.object());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "{\"hoge\": 42}" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.object());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "{\"hoge\": 42, \"hoge\": 42}" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.object());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "{\"hoge\": 42, \"hoge\": 42, \"hoge\": 42}" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.object());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "{\n  \"hoge\": 42\n,\t\"hoge\": 42}" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.object());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "{\"hoge\": 42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.object());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "{\"hoge\": 42,}" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.object());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "[]" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.object());

                        BOOST_TEST(!result);
                    }
                }

                BOOST_AUTO_TEST_CASE(member)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const grammar_type g{};

                        BOOST_CHECK(g.member().name() == "member");
                    }
                    {
                        const std::string input{ "\"hoge\": 42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.member());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "\"hoge\"\t:\n\n42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.member());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "42: \"hoge\"" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.member());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "\"hoge\": 42: 42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.member());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "\"hoge\":" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.member());

                        BOOST_TEST(!result);
                    }
                }

                BOOST_AUTO_TEST_CASE(array)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const grammar_type g{};

                        BOOST_CHECK(g.array().name() == "array");
                    }
                    {
                        const std::string input{ "[]" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.array());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "[42]" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.array());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "[42, 42]" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.array());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "[42, 42, 42]" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.array());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "[\n  42\n,\t42]" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.array());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "[42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.array());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "[42,]" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.array());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "{}" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.array());

                        BOOST_TEST(!result);
                    }
                }

                BOOST_AUTO_TEST_CASE(number)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const grammar_type g{};

                        BOOST_CHECK(g.number().name() == "number");
                    }
                    {
                        const std::string input{ "42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "0" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "02" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "-42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "-0" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "-02" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "42.42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "42.42.42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "42e+42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "42.42e+42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "42E+42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "42e-42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "42e+42.42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "42e+42e+42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "42f+42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "42e*42" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "42e" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.number());

                        BOOST_TEST(!result);
                    }
                }

                BOOST_AUTO_TEST_CASE(string)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const grammar_type g{};

                        BOOST_CHECK(g.string().name() == "string");
                    }
                    {
                        const std::string input{ "\"hoge\"" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.string());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "\"hoge\"fuga" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.string());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "\"hoge" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.string());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "hoge" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.string());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "\"a\\\"a\"" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.string());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "\"a\"a\"" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.string());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "\"\\n\\u12ABXYZ\"" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.string());

                        BOOST_TEST(result);
                    }
                    {
                        const std::string input{ "\"\\m\\u12ABXYZ\"" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.string());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "\"\\n\\u12PQXYZ\"" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.string());

                        BOOST_TEST(!result);
                    }
                    {
                        const std::string input{ "\"\\n\\u12\"" };

                        const grammar_type g{};
                        const auto         result = full_match(input.begin(), input.end(), g.string());

                        BOOST_TEST(!result);
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

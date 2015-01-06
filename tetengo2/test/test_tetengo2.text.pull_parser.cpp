/*! \file
    \brief Test of class tetengo2::text::pull_parser.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <boost/predef.h>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/variant.hpp>

#include <tetengo2.h>

#include "test_tetengo2.type_list.h"


namespace
{
    // types

    using common_type_list_type = test_tetengo2::type_list::common;

    using size_type = common_type_list_type::size_type;

    using string_type = common_type_list_type::string_type;

    using io_string_type = common_type_list_type::io_string_type;

    using input_stream_iterator_type = boost::spirit::multi_pass<std::istreambuf_iterator<io_string_type::value_type>>;

    using grammar_type = tetengo2::text::grammar::json<input_stream_iterator_type>;

    using push_parser_type = tetengo2::text::push_parser<input_stream_iterator_type, grammar_type, int, double>;

    using pull_parser_type =
        tetengo2::text::pull_parser<input_stream_iterator_type, grammar_type, int, double, size_type>;

}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(text)
BOOST_AUTO_TEST_SUITE(pull_parser)
BOOST_AUTO_TEST_SUITE(structure)
    // test cases

    BOOST_AUTO_TEST_CASE(kind)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_CHECK(pull_parser_type::structure_begin_type::kind() == pull_parser_type::structure_kind_type::begin);
        BOOST_CHECK(pull_parser_type::structure_end_type::kind() == pull_parser_type::structure_kind_type::end);
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            pull_parser_type::attribute_map_type map{ std::make_pair(string_type{ TETENGO2_TEXT("key") }, 42) };
            const pull_parser_type::structure_begin_type structure{
                string_type{ TETENGO2_TEXT("hoge") }, std::move(map)
            };
        }
        {
            pull_parser_type::attribute_map_type map{ std::make_pair(string_type{ TETENGO2_TEXT("key") }, 42) };
            const pull_parser_type::structure_end_type structure{
                string_type{ TETENGO2_TEXT("hoge") }, std::move(map)
            };
        }
    }

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        {
            pull_parser_type::attribute_map_type map{ std::make_pair(string_type{ TETENGO2_TEXT("key") }, 42) };
            const pull_parser_type::structure_begin_type structure{
                string_type{ TETENGO2_TEXT("hoge") }, std::move(map)
            };

            BOOST_CHECK(structure.name() == string_type{ TETENGO2_TEXT("hoge") });
        }
        {
            pull_parser_type::attribute_map_type map{ std::make_pair(string_type{ TETENGO2_TEXT("key") }, 42) };
            const pull_parser_type::structure_end_type structure{
                string_type{ TETENGO2_TEXT("hoge") }, std::move(map)
            };

            BOOST_CHECK(structure.name() == string_type{ TETENGO2_TEXT("hoge") });
        }
    }

    BOOST_AUTO_TEST_CASE(attribute_map)
    {
        BOOST_TEST_PASSPOINT();

        {
            pull_parser_type::attribute_map_type map{ std::make_pair(string_type{ TETENGO2_TEXT("key") }, 42) };
            const pull_parser_type::structure_end_type structure{
                string_type{ TETENGO2_TEXT("hoge") }, std::move(map)
            };

            BOOST_REQUIRE_EQUAL(structure.attribute_map().size(), 1U);
            const auto found = structure.attribute_map().find(string_type{ TETENGO2_TEXT("key") });
            BOOST_REQUIRE(found != structure.attribute_map().end());
            BOOST_CHECK(
                *found == pull_parser_type::attribute_map_type::value_type(string_type{ TETENGO2_TEXT("key") }, 42)
            );
        }
        {
            pull_parser_type::attribute_map_type map{ std::make_pair(string_type{ TETENGO2_TEXT("key") }, 42) };
            const pull_parser_type::structure_end_type structure{
                string_type{ TETENGO2_TEXT("hoge") }, std::move(map)
            };

            BOOST_REQUIRE_EQUAL(structure.attribute_map().size(), 1U);
            const auto found = structure.attribute_map().find(string_type{ TETENGO2_TEXT("key") });
            BOOST_REQUIRE(found != structure.attribute_map().end());
            BOOST_CHECK(
                *found == pull_parser_type::attribute_map_type::value_type(string_type{ TETENGO2_TEXT("key") }, 42)
            );
        }
    }


BOOST_AUTO_TEST_SUITE_END()
    // test cases

#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream json_text{};
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{ json_text } },
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{} },
                    tetengo2::stdalt::make_unique<grammar_type>()
                );

            const pull_parser_type pull_parser{ std::move(p_push_parser), 3 };
        }
        {
            std::istringstream json_text{};
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{ json_text } },
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{} },
                    tetengo2::stdalt::make_unique<grammar_type>()
                );

            BOOST_CHECK_THROW(
                ([&]() { const pull_parser_type pull_parser{ std::move(p_push_parser), 0 }; }()), std::invalid_argument
            );
        }
    }

    BOOST_AUTO_TEST_CASE(has_next)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream json_text{};
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{ json_text } },
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{} },
                    tetengo2::stdalt::make_unique<grammar_type>()
                );

            const pull_parser_type pull_parser{ std::move(p_push_parser), 3 };

            BOOST_CHECK(!pull_parser.has_next());
        }
        {
            std::istringstream json_text{
                "{}"
            };
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{ json_text } },
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{} },
                    tetengo2::stdalt::make_unique<grammar_type>()
                );

            const pull_parser_type pull_parser{ std::move(p_push_parser), 3 };

            BOOST_CHECK(pull_parser.has_next());
        }
    }

    BOOST_AUTO_TEST_CASE(peek)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream json_text{};
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{ json_text } },
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{} },
                    tetengo2::stdalt::make_unique<grammar_type>()
                );

            pull_parser_type pull_parser{ std::move(p_push_parser), 3 };

            BOOST_CHECK_THROW(pull_parser.peek(), std::logic_error);
        }
        {
            std::istringstream json_text{
                "{}"
            };
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{ json_text } },
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{} },
                    tetengo2::stdalt::make_unique<grammar_type>()
                );

            pull_parser_type pull_parser{ std::move(p_push_parser), 3 };

            {
                BOOST_CHECK(pull_parser.has_next());
                const auto& element = pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 0);
                const auto structure = boost::get<pull_parser_type::structure_begin_type>(element);
                BOOST_CHECK(structure.name() == "object");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const auto& element = pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 1);
                const auto structure = boost::get<pull_parser_type::structure_end_type>(element);
                BOOST_CHECK(structure.name() == "object");
                pull_parser.next();
            }
            BOOST_CHECK(!pull_parser.has_next());
        }
        {
            std::istringstream json_text{
                "{\n"
                "    \"hoge\": 42,\n"
                "    \"fuga\": [42, 42, 42]\n"
                "}\n"
            };
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{ json_text } },
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{} },
                    tetengo2::stdalt::make_unique<grammar_type>()
                );

            pull_parser_type pull_parser{ std::move(p_push_parser), 3 };

            {
                BOOST_CHECK(pull_parser.has_next());
                const auto& element = pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 0);
                const auto structure = boost::get<pull_parser_type::structure_begin_type>(element);
                BOOST_CHECK(structure.name() == "object");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const auto& element = pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 0);
                const auto structure = boost::get<pull_parser_type::structure_begin_type>(element);
                BOOST_CHECK(structure.name() == "member");
                const auto attribute = structure.attribute_map().find("name");
                BOOST_CHECK(attribute != structure.attribute_map().end());
                BOOST_CHECK_EQUAL(attribute->second.which(), 4);
                const auto attribute_value = boost::get<std::string>(attribute->second);
                BOOST_CHECK(attribute_value == "hoge");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const auto& element = pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 2);
                const auto value = boost::get<int>(boost::get<pull_parser_type::value_type>(element));
                BOOST_CHECK_EQUAL(value, 42);
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const auto& element = pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 1);
                const auto structure = boost::get<pull_parser_type::structure_end_type>(element);
                BOOST_CHECK(structure.name() == "member");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const auto& element = pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 0);
                const auto structure = boost::get<pull_parser_type::structure_begin_type>(element);
                BOOST_CHECK(structure.name() == "member");
                const auto attribute = structure.attribute_map().find("name");
                BOOST_CHECK(attribute != structure.attribute_map().end());
                BOOST_CHECK_EQUAL(attribute->second.which(), 4);
                const auto attribute_value = boost::get<std::string>(attribute->second);
                BOOST_CHECK(attribute_value == "fuga");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const auto& element = pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 0);
                const auto structure = boost::get<pull_parser_type::structure_begin_type>(element);
                BOOST_CHECK(structure.name() == "array");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const auto& element = pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 2);
                const auto value = boost::get<int>(boost::get<pull_parser_type::value_type>(element));
                BOOST_CHECK_EQUAL(value, 42);
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const auto& element = pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 2);
                const auto value = boost::get<int>(boost::get<pull_parser_type::value_type>(element));
                BOOST_CHECK_EQUAL(value, 42);
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const auto& element = pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 2);
                const auto value = boost::get<int>(boost::get<pull_parser_type::value_type>(element));
                BOOST_CHECK_EQUAL(value, 42);
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const auto& element = pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 1);
                const auto structure = boost::get<pull_parser_type::structure_end_type>(element);
                BOOST_CHECK(structure.name() == "array");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const auto& element = pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 1);
                const auto structure = boost::get<pull_parser_type::structure_end_type>(element);
                BOOST_CHECK(structure.name() == "member");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const auto& element = pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 1);
                const auto structure = boost::get<pull_parser_type::structure_end_type>(element);
                BOOST_CHECK(structure.name() == "object");
                pull_parser.next();
            }
            BOOST_CHECK(!pull_parser.has_next());
        }
    }

    BOOST_AUTO_TEST_CASE(next)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream json_text{};
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{ json_text } },
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{} },
                    tetengo2::stdalt::make_unique<grammar_type>()
                );

            pull_parser_type pull_parser{ std::move(p_push_parser), 3 };

            BOOST_CHECK_THROW(pull_parser.next(), std::logic_error);
        }
        {
            std::istringstream json_text{
                "{}"
            };
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{ json_text } },
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{} },
                    tetengo2::stdalt::make_unique<grammar_type>()
                );

            pull_parser_type pull_parser{ std::move(p_push_parser), 3 };

            pull_parser.next();
            pull_parser.next();
            BOOST_CHECK(!pull_parser.has_next());
        }
    }

    BOOST_AUTO_TEST_CASE(skip_next)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream json_text{};
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{ json_text } },
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{} },
                    tetengo2::stdalt::make_unique<grammar_type>()
                );

            pull_parser_type pull_parser{ std::move(p_push_parser), 3 };

            BOOST_CHECK_THROW(pull_parser.skip_next(), std::logic_error);
        }
        {
            std::istringstream json_text{
                "[42]"
            };
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{ json_text } },
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{} },
                    tetengo2::stdalt::make_unique<grammar_type>()
                );

            pull_parser_type pull_parser{ std::move(p_push_parser), 3 };

            pull_parser.next();
            pull_parser.skip_next();
            const auto& element = pull_parser.peek();
            BOOST_CHECK_EQUAL(element.which(), 1);
            const auto structure = boost::get<pull_parser_type::structure_end_type>(element);
            BOOST_CHECK(structure.name() == "array");
        }
        {
            std::istringstream json_text{
                "[42]"
            };
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{ json_text } },
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{} },
                    tetengo2::stdalt::make_unique<grammar_type>()
                );

            pull_parser_type pull_parser{ std::move(p_push_parser), 3 };

            pull_parser.next();
            pull_parser.next();
            pull_parser.skip_next();
            BOOST_CHECK(!pull_parser.has_next());
        }
        {
            std::istringstream json_text{
                "[42]"
            };
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{ json_text } },
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{} },
                    tetengo2::stdalt::make_unique<grammar_type>()
                );

            pull_parser_type pull_parser{ std::move(p_push_parser), 3 };

            pull_parser.skip_next();
            BOOST_CHECK(!pull_parser.has_next());
        }
        {
            std::istringstream json_text{
                "[12, [34, 56], 78]"
            };
            auto p_push_parser =
                tetengo2::stdalt::make_unique<push_parser_type>(
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{ json_text } },
                    input_stream_iterator_type{ std::istreambuf_iterator<char>{} },
                    tetengo2::stdalt::make_unique<grammar_type>()
                );

            pull_parser_type pull_parser{ std::move(p_push_parser), 3 };

            pull_parser.next();
            pull_parser.next();
            pull_parser.skip_next();
            const auto& element = pull_parser.peek();
            BOOST_CHECK_EQUAL(element.which(), 2);
            const auto value = boost::get<int>(boost::get<pull_parser_type::value_type>(element));
            BOOST_CHECK_EQUAL(value, 78);
        }
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

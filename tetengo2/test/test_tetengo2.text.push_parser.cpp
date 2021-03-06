/*! \file
    \brief Test of class tetengo2::text::push_parser.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text/grammar/json.h>
#include <tetengo2/text/push_parser.h>
#include <tetengo2/type_list.h>


namespace {
    // types

    using integer_type = tetengo2::type_list::integer_type;

    using float_type = tetengo2::type_list::float_type;

    using input_stream_iterator_type =
        tetengo2::iterator::observable_forward_iterator<boost::spirit::multi_pass<std::istreambuf_iterator<char>>>;

    using grammar_type = tetengo2::text::grammar::json<input_stream_iterator_type>;

    using push_parser_type = tetengo2::text::push_parser<input_stream_iterator_type>;

    using attribute_map_type = push_parser_type::attribute_map_type;

    using parsed_structure_type = std::pair<std::string, tetengo2::stdalt::optional<push_parser_type::value_type>>;


    // functions

    bool structure_observer0(
        TETENGO2_STDALT_MAYBE_UNUSED const std::string& structure,
        TETENGO2_STDALT_MAYBE_UNUSED const attribute_map_type& attribute_map)
    {
        return true;
    }

    bool structure_observer1(
        const std::string&                 structure,
        TETENGO2_STDALT_MAYBE_UNUSED const attribute_map_type& attribute_map,
        std::vector<parsed_structure_type>&                    parsed_structures)
    {
        parsed_structures.emplace_back(structure, TETENGO2_STDALT_NULLOPT);
        return true;
    }

    bool value_observer0(TETENGO2_STDALT_MAYBE_UNUSED const push_parser_type::value_type& value)
    {
        return true;
    }

    bool
    value_observer1(const push_parser_type::value_type& value, std::vector<parsed_structure_type>& parsed_structures)
    {
        parsed_structures.emplace_back("value", tetengo2::stdalt::make_optional(push_parser_type::value_type{ value }));
        return true;
    }
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(text)
        BOOST_AUTO_TEST_SUITE(push_parser)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                {
                    std::istringstream input{};
                    const auto         first = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input }));
                    const auto last = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{}));
                    const push_parser_type parser{ first, last, std::make_unique<grammar_type>() };
                }
                {
                    std::istringstream input{ "{}" };
                    const auto         first = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input }));
                    const auto last = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{}));
                    const push_parser_type parser{ first, last, std::make_unique<grammar_type>() };
                }
            }

            BOOST_AUTO_TEST_CASE(on_structure_begin)
            {
                BOOST_TEST_PASSPOINT();

                {
                    std::istringstream input{ "{}" };
                    const auto         first = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input }));
                    const auto last = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{}));
                    push_parser_type parser{ first, last, std::make_unique<grammar_type>() };

                    parser.on_structure_begin().connect(structure_observer0);
                }
                {
                    std::istringstream input{ "{}" };
                    const auto         first = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input }));
                    const auto last = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{}));
                    const push_parser_type parser{ first, last, std::make_unique<grammar_type>() };

                    parser.on_structure_begin();
                }
            }

            BOOST_AUTO_TEST_CASE(on_structure_end)
            {
                BOOST_TEST_PASSPOINT();

                {
                    std::istringstream input{ "{}" };
                    const auto         first = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input }));
                    const auto last = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{}));
                    push_parser_type parser{ first, last, std::make_unique<grammar_type>() };

                    parser.on_structure_end().connect(structure_observer0);
                }
                {
                    std::istringstream input{ "{}" };
                    const auto         first = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input }));
                    const auto last = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{}));
                    const push_parser_type parser{ first, last, std::make_unique<grammar_type>() };

                    parser.on_structure_end();
                }
            }

            BOOST_AUTO_TEST_CASE(on_value)
            {
                BOOST_TEST_PASSPOINT();

                {
                    std::istringstream input{ "{}" };
                    const auto         first = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input }));
                    const auto last = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{}));
                    push_parser_type parser{ first, last, std::make_unique<grammar_type>() };

                    parser.on_value().connect(value_observer0);
                }
                {
                    std::istringstream input{ "{}" };
                    const auto         first = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input }));
                    const auto last = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{}));
                    const push_parser_type parser{ first, last, std::make_unique<grammar_type>() };

                    parser.on_value();
                }
            }

            BOOST_AUTO_TEST_CASE(parse)
            {
                BOOST_TEST_PASSPOINT();

                {
                    std::vector<parsed_structure_type> parsed{};

                    std::istringstream input{};
                    const auto         first = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input }));
                    const auto last = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{}));
                    push_parser_type parser{ first, last, std::make_unique<grammar_type>() };
                    parser.on_structure_begin().connect(
                        [&parsed](const std::string& structure, const attribute_map_type& attribute_map) {
                            return structure_observer1(structure, attribute_map, parsed);
                        });
                    parser.on_structure_end().connect(
                        [&parsed](const std::string& structure, const attribute_map_type& attribute_map) {
                            return structure_observer1(structure, attribute_map, parsed);
                        });
                    parser.on_value().connect([&parsed](const push_parser_type::value_type& value) {
                        return value_observer1(value, parsed);
                    });

                    BOOST_TEST(!parser.parse());
                }
                {
                    std::vector<parsed_structure_type> parsed{};

                    std::istringstream input{ "[]" };
                    const auto         first = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input }));
                    const auto last = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{}));
                    push_parser_type parser{ first, last, std::make_unique<grammar_type>() };
                    parser.on_structure_begin().connect(
                        [&parsed](const std::string& structure, const attribute_map_type& attribute_map) {
                            return structure_observer1(structure, attribute_map, parsed);
                        });
                    parser.on_structure_end().connect(
                        [&parsed](const std::string& structure, const attribute_map_type& attribute_map) {
                            return structure_observer1(structure, attribute_map, parsed);
                        });
                    parser.on_value().connect([&parsed](const push_parser_type::value_type& value) {
                        return value_observer1(value, parsed);
                    });

                    BOOST_TEST_REQUIRE(parser.parse());
                    BOOST_TEST_REQUIRE(parsed.size() == 2U);

                    BOOST_CHECK(parsed[0].first == "array");

                    BOOST_CHECK(parsed[1].first == "array");
                }
                {
                    std::vector<parsed_structure_type> parsed{};

                    std::istringstream input{
                        "["
                        "    false,"
                        "    null,"
                        "    true,"
                        "    \"hoge\\tfuga\""
                        "]"
                    };
                    const auto first = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input }));
                    const auto last = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{}));
                    push_parser_type parser{ first, last, std::make_unique<grammar_type>() };
                    parser.on_structure_begin().connect(
                        [&parsed](const std::string& structure, const attribute_map_type& attribute_map) {
                            return structure_observer1(structure, attribute_map, parsed);
                        });
                    parser.on_structure_end().connect(
                        [&parsed](const std::string& structure, const attribute_map_type& attribute_map) {
                            return structure_observer1(structure, attribute_map, parsed);
                        });
                    parser.on_value().connect([&parsed](const push_parser_type::value_type& value) {
                        return value_observer1(value, parsed);
                    });

                    BOOST_TEST(parser.parse());
                    BOOST_TEST_REQUIRE(parsed.size() == 6U);

                    BOOST_CHECK(parsed[0].first == "array");

                    BOOST_CHECK(parsed[1].first == "value");
                    BOOST_TEST(tetengo2::stdalt::has_value(parsed[1].second));
                    BOOST_TEST(tetengo2::stdalt::index(*parsed[1].second) == 0U);
                    BOOST_TEST(!tetengo2::stdalt::get<bool>(*parsed[1].second));

                    BOOST_CHECK(parsed[2].first == "value");
                    BOOST_TEST(tetengo2::stdalt::has_value(parsed[2].second));
                    BOOST_TEST(tetengo2::stdalt::index(*parsed[2].second) == 1U);
                    BOOST_TEST(!tetengo2::stdalt::get<void*>(*parsed[2].second));

                    BOOST_CHECK(parsed[3].first == "value");
                    BOOST_TEST(tetengo2::stdalt::has_value(parsed[3].second));
                    BOOST_TEST(tetengo2::stdalt::index(*parsed[3].second) == 0U);
                    BOOST_TEST(tetengo2::stdalt::get<bool>(*parsed[3].second));

                    BOOST_CHECK(parsed[4].first == "value");
                    BOOST_TEST(tetengo2::stdalt::has_value(parsed[4].second));
                    BOOST_TEST(tetengo2::stdalt::index(*parsed[4].second) == 4U);
                    BOOST_CHECK(tetengo2::stdalt::get<std::string>(*parsed[4].second) == "hoge\tfuga");

                    BOOST_CHECK(parsed[5].first == "array");
                }
                {
                    std::vector<parsed_structure_type> parsed{};

                    std::istringstream input{
                        "["
                        "    42,"
                        "    -42,"
                        "    42.42,"
                        "    42e+2,"
                        "    4200e-2,"
                        "    42.42e+2"
                        "]"
                    };
                    const auto first = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input }));
                    const auto last = tetengo2::iterator::make_observable_forward_iterator(
                        boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{}));
                    push_parser_type parser{ first, last, std::make_unique<grammar_type>() };
                    parser.on_structure_begin().connect(
                        [&parsed](const std::string& structure, const attribute_map_type& attribute_map) {
                            return structure_observer1(structure, attribute_map, parsed);
                        });
                    parser.on_structure_end().connect(
                        [&parsed](const std::string& structure, const attribute_map_type& attribute_map) {
                            return structure_observer1(structure, attribute_map, parsed);
                        });
                    parser.on_value().connect([&parsed](const push_parser_type::value_type& value) {
                        return value_observer1(value, parsed);
                    });

                    BOOST_TEST(parser.parse());
                    BOOST_TEST_REQUIRE(parsed.size() == 8U);

                    BOOST_CHECK(parsed[0].first == "array");

                    BOOST_CHECK(parsed[1].first == "value");
                    BOOST_TEST(tetengo2::stdalt::has_value(parsed[1].second));
                    BOOST_TEST(tetengo2::stdalt::index(*parsed[1].second) == 2U);
                    BOOST_TEST(tetengo2::stdalt::get<integer_type>(*parsed[1].second) == 42);

                    BOOST_CHECK(parsed[2].first == "value");
                    BOOST_TEST(tetengo2::stdalt::has_value(parsed[2].second));
                    BOOST_TEST(tetengo2::stdalt::index(*parsed[2].second) == 2U);
                    BOOST_TEST(tetengo2::stdalt::get<integer_type>(*parsed[2].second) == -42);

                    BOOST_CHECK(parsed[3].first == "value");
                    BOOST_TEST(tetengo2::stdalt::has_value(parsed[3].second));
                    BOOST_TEST(tetengo2::stdalt::index(*parsed[3].second) == 3U);
                    BOOST_TEST(
                        tetengo2::stdalt::get<float_type>(*parsed[3].second) == 42.42,
                        boost::test_tools::tolerance(0.001));

                    BOOST_CHECK(parsed[4].first == "value");
                    BOOST_TEST(tetengo2::stdalt::has_value(parsed[4].second));
                    BOOST_TEST(tetengo2::stdalt::index(*parsed[4].second) == 3U);
                    BOOST_TEST(
                        tetengo2::stdalt::get<float_type>(*parsed[4].second) == 4200.0,
                        boost::test_tools::tolerance(0.001));

                    BOOST_CHECK(parsed[5].first == "value");
                    BOOST_TEST(tetengo2::stdalt::has_value(parsed[5].second));
                    BOOST_TEST(tetengo2::stdalt::index(*parsed[5].second) == 3U);
                    BOOST_TEST(
                        tetengo2::stdalt::get<float_type>(*parsed[5].second) == 42.0,
                        boost::test_tools::tolerance(0.001));

                    BOOST_CHECK(parsed[6].first == "value");
                    BOOST_TEST(tetengo2::stdalt::has_value(parsed[6].second));
                    BOOST_TEST(tetengo2::stdalt::index(*parsed[6].second) == 3U);
                    BOOST_TEST(
                        tetengo2::stdalt::get<float_type>(*parsed[6].second) == 4242.0,
                        boost::test_tools::tolerance(0.001));

                    BOOST_CHECK(parsed[7].first == "array");
                }
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

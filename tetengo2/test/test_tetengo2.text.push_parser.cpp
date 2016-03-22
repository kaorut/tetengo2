/*! \file
    \brief Test of class tetengo2::text::push_parser.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/optional.hpp>
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

    using io_string_type = common_type_list_type::io_string_type;

    using input_stream_iterator_type =
        tetengo2::observable_forward_iterator<
            boost::spirit::multi_pass<std::istreambuf_iterator<io_string_type::value_type>>
        >;

    using grammar_type = tetengo2::text::grammar::json<input_stream_iterator_type>;

    using push_parser_type = tetengo2::text::push_parser<input_stream_iterator_type, grammar_type, int, double>;

    using attribute_map_type = push_parser_type::attribute_map_type;

    using parsed_structure_type = std::pair<std::string, boost::optional<push_parser_type::value_type>>;


    // functions

#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(5, 3, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 4, 0)) \
)
    bool structure_observer0(const std::string& structure, const attribute_map_type& attribute_map)
    {
        boost::ignore_unused(structure, attribute_map);

        return true;
    }

    bool structure_observer1(
        const std::string&                  structure,
        const attribute_map_type&           attribute_map,
        std::vector<parsed_structure_type>& parsed_structures
    )
    {
        boost::ignore_unused(attribute_map);

        parsed_structures.emplace_back(structure, boost::none);
        return true;
    }

    bool value_observer0(const push_parser_type::value_type& value)
    {
        boost::ignore_unused(value);

        return true;
    }

    bool value_observer1(
        const push_parser_type::value_type& value,
        std::vector<parsed_structure_type>& parsed_structures
    )
    {
        parsed_structures.emplace_back("value", boost::make_optional(value));
        return true;
    }
#endif


}


#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(5, 3, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 4, 0)) \
)
BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(text)
BOOST_AUTO_TEST_SUITE(push_parser)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream input{};
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input })
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{})
                );
            const push_parser_type parser{ first, last, tetengo2::stdalt::make_unique<grammar_type>() };
        }
        {
            std::istringstream input{ "{}" };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input })
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{})
                );
            const push_parser_type parser{ first, last, tetengo2::stdalt::make_unique<grammar_type>() };
        }
    }

    BOOST_AUTO_TEST_CASE(on_structure_begin)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream input{ "{}" };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input })
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{})
                );
            push_parser_type parser{ first, last, tetengo2::stdalt::make_unique<grammar_type>() };

            parser.on_structure_begin().connect(structure_observer0);
        }
        {
            std::istringstream input{ "{}" };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input })
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{})
                );
            const push_parser_type parser{ first, last, tetengo2::stdalt::make_unique<grammar_type>() };

            parser.on_structure_begin();
        }
    }

    BOOST_AUTO_TEST_CASE(on_structure_end)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream input{ "{}" };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input })
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{})
                );
            push_parser_type parser{ first, last, tetengo2::stdalt::make_unique<grammar_type>() };

            parser.on_structure_end().connect(structure_observer0);
        }
        {
            std::istringstream input{ "{}" };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input })
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{})
                );
            const push_parser_type parser{ first, last, tetengo2::stdalt::make_unique<grammar_type>() };

            parser.on_structure_end();
        }
    }

    BOOST_AUTO_TEST_CASE(on_value)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream input{ "{}" };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input })
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{})
                );
            push_parser_type parser{ first, last, tetengo2::stdalt::make_unique<grammar_type>() };

            parser.on_value().connect(value_observer0);
        }
        {
            std::istringstream input{ "{}" };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input })
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{})
                );
            const push_parser_type parser{ first, last, tetengo2::stdalt::make_unique<grammar_type>() };

            parser.on_value();
        }
    }

    BOOST_AUTO_TEST_CASE(parse)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::vector<parsed_structure_type> parsed{};

            std::istringstream input{};
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input })
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{})
                );
            push_parser_type parser{ first, last, tetengo2::stdalt::make_unique<grammar_type>() };
            parser.on_structure_begin().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    return structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_structure_end().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    return structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_value().connect(
                [&parsed](const push_parser_type::value_type& value) { return value_observer1(value, parsed); }
            );

            BOOST_TEST(!parser.parse());
        }
        {
            std::vector<parsed_structure_type> parsed{};

            std::istringstream input{ "[]" };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input })
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{})
                );
            push_parser_type parser{ first, last, tetengo2::stdalt::make_unique<grammar_type>() };
            parser.on_structure_begin().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    return structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_structure_end().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    return structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_value().connect(
                [&parsed](const push_parser_type::value_type& value) { return value_observer1(value, parsed); }
            );

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
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input })
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{})
                );
            push_parser_type parser{ first, last, tetengo2::stdalt::make_unique<grammar_type>() };
            parser.on_structure_begin().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    return structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_structure_end().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    return structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_value().connect(
                [&parsed](const push_parser_type::value_type& value) { return value_observer1(value, parsed); }
            );

            BOOST_TEST(parser.parse());
            BOOST_TEST_REQUIRE(parsed.size() == 6U);

            BOOST_CHECK(parsed[0].first == "array");

            BOOST_CHECK(parsed[1].first == "value");
            BOOST_TEST(parsed[1].second.is_initialized());
            BOOST_TEST(parsed[1].second->which() == 0);
            BOOST_TEST(!boost::get<bool>(*parsed[1].second));

            BOOST_CHECK(parsed[2].first == "value");
            BOOST_TEST(parsed[2].second.is_initialized());
            BOOST_TEST(parsed[2].second->which() == 1);
            BOOST_TEST(!boost::get<void*>(*parsed[2].second));

            BOOST_CHECK(parsed[3].first == "value");
            BOOST_TEST(parsed[3].second.is_initialized());
            BOOST_TEST(parsed[3].second->which() == 0);
            BOOST_TEST(boost::get<bool>(*parsed[3].second));

            BOOST_CHECK(parsed[4].first == "value");
            BOOST_TEST(parsed[4].second.is_initialized());
            BOOST_TEST(parsed[4].second->which() == 4);
            BOOST_CHECK(boost::get<std::string>(*parsed[4].second) == "hoge\tfuga");

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
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input })
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{})
                );
            push_parser_type parser{ first, last, tetengo2::stdalt::make_unique<grammar_type>() };
            parser.on_structure_begin().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    return structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_structure_end().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    return structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_value().connect(
                [&parsed](const push_parser_type::value_type& value) { return value_observer1(value, parsed); }
            );

            BOOST_TEST(parser.parse());
            BOOST_TEST_REQUIRE(parsed.size() == 8U);

            BOOST_CHECK(parsed[0].first == "array");

            BOOST_CHECK(parsed[1].first == "value");
            BOOST_TEST(parsed[1].second.is_initialized());
            BOOST_TEST(parsed[1].second->which() == 2);
            BOOST_TEST(boost::get<int>(*parsed[1].second) == 42);

            BOOST_CHECK(parsed[2].first == "value");
            BOOST_TEST(parsed[2].second.is_initialized());
            BOOST_TEST(parsed[2].second->which() == 2);
            BOOST_TEST(boost::get<int>(*parsed[2].second) == -42);

            BOOST_CHECK(parsed[3].first == "value");
            BOOST_TEST(parsed[3].second.is_initialized());
            BOOST_TEST(parsed[3].second->which() == 3);
            BOOST_TEST(boost::get<double>(*parsed[3].second) == 42.42, boost::test_tools::tolerance(0.001));

            BOOST_CHECK(parsed[4].first == "value");
            BOOST_TEST(parsed[4].second.is_initialized());
            BOOST_TEST(parsed[4].second->which() == 3);
            BOOST_TEST(boost::get<double>(*parsed[4].second) == 4200.0, boost::test_tools::tolerance(0.001));

            BOOST_CHECK(parsed[5].first == "value");
            BOOST_TEST(parsed[5].second.is_initialized());
            BOOST_TEST(parsed[5].second->which() == 3);
            BOOST_TEST(boost::get<double>(*parsed[5].second) == 42.0, boost::test_tools::tolerance(0.001));

            BOOST_CHECK(parsed[6].first == "value");
            BOOST_TEST(parsed[6].second.is_initialized());
            BOOST_TEST(parsed[6].second->which() == 3);
            BOOST_TEST(boost::get<double>(*parsed[6].second) == 4242.0, boost::test_tools::tolerance(0.001));

            BOOST_CHECK(parsed[7].first == "array");
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif

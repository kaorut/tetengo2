/*! \file
    \brief Test of class tetengo2::text::push_parser.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/variant.hpp>

#include "tetengo2.stdalt.h"
#include "tetengo2.utility.h"

#include "test_tetengo2.type_list.h"


namespace
{
    // types

    using input_stream_iterator_type =
        boost::mpl::at<test_tetengo2::text_type_list, test_tetengo2::type::text::input_stream_iterator>::type;

    using grammar_type = boost::mpl::at<test_tetengo2::text_type_list, test_tetengo2::type::text::grammar>::type;

    using push_parser_type =
        boost::mpl::at<test_tetengo2::text_type_list, test_tetengo2::type::text::push_parser>::type;

    using attribute_map_type = push_parser_type::attribute_map_type;

    using parsed_structure_type = std::pair<std::string, boost::optional<push_parser_type::value_type>>;


    // functions

    void structure_observer0(const std::string& structure, const attribute_map_type& attribute_map)
    {
        tetengo2::suppress_unused_variable_warning(structure, attribute_map);
    }

    void structure_observer1(
        const std::string&                  structure,
        const attribute_map_type&           attribute_map,
        std::vector<parsed_structure_type>& parsed_structures
    )
    {
        tetengo2::suppress_unused_variable_warning(attribute_map);

        parsed_structures.emplace_back(structure, boost::none);
    }

    void value_observer0(const push_parser_type::value_type& value)
    {
        tetengo2::suppress_unused_variable_warning(value);
    }

    void value_observer1(
        const push_parser_type::value_type& value,
        std::vector<parsed_structure_type>& parsed_structures
    )
    {
        parsed_structures.emplace_back("value", boost::make_optional(value));
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
            std::istringstream input;
            push_parser_type parser(
                input_stream_iterator_type(std::istreambuf_iterator<char>(input)),
                input_stream_iterator_type(std::istreambuf_iterator<char>()),
                tetengo2::stdalt::make_unique<grammar_type>()
            );
        }
        {
            std::istringstream input("{}");
            push_parser_type parser(
                input_stream_iterator_type(std::istreambuf_iterator<char>(input)),
                input_stream_iterator_type(std::istreambuf_iterator<char>()),
                tetengo2::stdalt::make_unique<grammar_type>()
            );
        }
    }

    BOOST_AUTO_TEST_CASE(on_structure_begin)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream input("{}");
            push_parser_type parser(
                input_stream_iterator_type(std::istreambuf_iterator<char>(input)),
                input_stream_iterator_type(std::istreambuf_iterator<char>()),
                tetengo2::stdalt::make_unique<grammar_type>()
            );

            parser.on_structure_begin().connect(structure_observer0);
        }
        {
            std::istringstream input("{}");
            const push_parser_type parser(
                input_stream_iterator_type(std::istreambuf_iterator<char>(input)),
                input_stream_iterator_type(std::istreambuf_iterator<char>()),
                tetengo2::stdalt::make_unique<grammar_type>()
            );

            parser.on_structure_begin();
        }
    }

    BOOST_AUTO_TEST_CASE(on_structure_end)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream input("{}");
            push_parser_type parser(
                input_stream_iterator_type(std::istreambuf_iterator<char>(input)),
                input_stream_iterator_type(std::istreambuf_iterator<char>()),
                tetengo2::stdalt::make_unique<grammar_type>()
            );

            parser.on_structure_end().connect(structure_observer0);
        }
        {
            std::istringstream input("{}");
            const push_parser_type parser(
                input_stream_iterator_type(std::istreambuf_iterator<char>(input)),
                input_stream_iterator_type(std::istreambuf_iterator<char>()),
                tetengo2::stdalt::make_unique<grammar_type>()
            );

            parser.on_structure_end();
        }
    }

    BOOST_AUTO_TEST_CASE(on_value)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream input("{}");
            push_parser_type parser(
                input_stream_iterator_type(std::istreambuf_iterator<char>(input)),
                input_stream_iterator_type(std::istreambuf_iterator<char>()),
                tetengo2::stdalt::make_unique<grammar_type>()
            );

            parser.on_value().connect(value_observer0);
        }
        {
            std::istringstream input("{}");
            const push_parser_type parser(
                input_stream_iterator_type(std::istreambuf_iterator<char>(input)),
                input_stream_iterator_type(std::istreambuf_iterator<char>()),
                tetengo2::stdalt::make_unique<grammar_type>()
            );

            parser.on_value();
        }
    }

    BOOST_AUTO_TEST_CASE(parse)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::vector<parsed_structure_type> parsed;

            std::istringstream input;
            push_parser_type parser(
                input_stream_iterator_type(std::istreambuf_iterator<char>(input)),
                input_stream_iterator_type(std::istreambuf_iterator<char>()),
                tetengo2::stdalt::make_unique<grammar_type>()
            );
            parser.on_structure_begin().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_structure_end().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_value().connect(
                [&parsed](const push_parser_type::value_type& value) { value_observer1(value, parsed); }
            );

            BOOST_CHECK(!parser.parse());
        }
        {
            std::vector<parsed_structure_type> parsed;

            std::istringstream input("[]");
            push_parser_type parser(
                input_stream_iterator_type(std::istreambuf_iterator<char>(input)),
                input_stream_iterator_type(std::istreambuf_iterator<char>()),
                tetengo2::stdalt::make_unique<grammar_type>()
            );
            parser.on_structure_begin().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_structure_end().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_value().connect(
                [&parsed](const push_parser_type::value_type& value) { value_observer1(value, parsed); }
            );

            BOOST_CHECK(parser.parse());
            BOOST_REQUIRE_EQUAL(parsed.size(), 2U);

            BOOST_CHECK(parsed[0].first == "array");

            BOOST_CHECK(parsed[1].first == "array");
        }
        {
            std::vector<parsed_structure_type> parsed;

            std::istringstream input(
                "["
                "    false,"
                "    null,"
                "    true,"
                "    \"hoge\\tfuga\""
                "]"
            );
            push_parser_type parser(
                input_stream_iterator_type(std::istreambuf_iterator<char>(input)),
                input_stream_iterator_type(std::istreambuf_iterator<char>()),
                tetengo2::stdalt::make_unique<grammar_type>()
            );
            parser.on_structure_begin().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_structure_end().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_value().connect(
                [&parsed](const push_parser_type::value_type& value) { value_observer1(value, parsed); }
            );

            BOOST_CHECK(parser.parse());
            BOOST_REQUIRE_EQUAL(parsed.size(), 6U);

            BOOST_CHECK(parsed[0].first == "array");

            BOOST_CHECK(parsed[1].first == "value");
            BOOST_CHECK(parsed[1].second);
            BOOST_CHECK_EQUAL(parsed[1].second->which(), 0);
            BOOST_CHECK(!boost::get<bool>(*parsed[1].second));

            BOOST_CHECK(parsed[2].first == "value");
            BOOST_CHECK(parsed[2].second);
            BOOST_CHECK_EQUAL(parsed[2].second->which(), 1);
            BOOST_CHECK(!boost::get<void*>(*parsed[2].second));

            BOOST_CHECK(parsed[3].first == "value");
            BOOST_CHECK(parsed[3].second);
            BOOST_CHECK_EQUAL(parsed[3].second->which(), 0);
            BOOST_CHECK(boost::get<bool>(*parsed[3].second));

            BOOST_CHECK(parsed[4].first == "value");
            BOOST_CHECK(parsed[4].second);
            BOOST_CHECK_EQUAL(parsed[4].second->which(), 4);
            BOOST_CHECK(boost::get<std::string>(*parsed[4].second) == "hoge\tfuga");

            BOOST_CHECK(parsed[5].first == "array");
        }
        {
            std::vector<parsed_structure_type> parsed;

            std::istringstream input(
                "["
                "    42,"
                "    -42,"
                "    42.42,"
                "    42e+2,"
                "    4200e-2,"
                "    42.42e+2"
                "]"
            );
            push_parser_type parser(
                input_stream_iterator_type(std::istreambuf_iterator<char>(input)),
                input_stream_iterator_type(std::istreambuf_iterator<char>()),
                tetengo2::stdalt::make_unique<grammar_type>()
            );
            parser.on_structure_begin().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_structure_end().connect(
                [&parsed](const std::string& structure, const attribute_map_type& attribute_map)
                {
                    structure_observer1(structure, attribute_map, parsed);
                }      
            );
            parser.on_value().connect(
                [&parsed](const push_parser_type::value_type& value) { value_observer1(value, parsed); }
            );

            BOOST_CHECK(parser.parse());
            BOOST_REQUIRE_EQUAL(parsed.size(), 8U);

            BOOST_CHECK(parsed[0].first == "array");

            BOOST_CHECK(parsed[1].first == "value");
            BOOST_CHECK(parsed[1].second);
            BOOST_CHECK_EQUAL(parsed[1].second->which(), 2);
            BOOST_CHECK_EQUAL(boost::get<int>(*parsed[1].second), 42);

            BOOST_CHECK(parsed[2].first == "value");
            BOOST_CHECK(parsed[2].second);
            BOOST_CHECK_EQUAL(parsed[2].second->which(), 2);
            BOOST_CHECK_EQUAL(boost::get<int>(*parsed[2].second), -42);

            BOOST_CHECK(parsed[3].first == "value");
            BOOST_CHECK(parsed[3].second);
            BOOST_CHECK_EQUAL(parsed[3].second->which(), 3);
            BOOST_CHECK_CLOSE(boost::get<double>(*parsed[3].second), 42.42, 0.001);

            BOOST_CHECK(parsed[4].first == "value");
            BOOST_CHECK(parsed[4].second);
            BOOST_CHECK_EQUAL(parsed[4].second->which(), 3);
            BOOST_CHECK_CLOSE(boost::get<double>(*parsed[4].second), 4200.0, 0.001);

            BOOST_CHECK(parsed[5].first == "value");
            BOOST_CHECK(parsed[5].second);
            BOOST_CHECK_EQUAL(parsed[5].second->which(), 3);
            BOOST_CHECK_CLOSE(boost::get<double>(*parsed[5].second), 42.0, 0.001);

            BOOST_CHECK(parsed[6].first == "value");
            BOOST_CHECK(parsed[6].second);
            BOOST_CHECK_EQUAL(parsed[6].second->which(), 3);
            BOOST_CHECK_CLOSE(boost::get<double>(*parsed[6].second), 4242.0, 0.001);

            BOOST_CHECK(parsed[7].first == "array");
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

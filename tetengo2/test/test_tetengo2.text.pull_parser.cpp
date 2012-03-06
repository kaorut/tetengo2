/*! \file
    \brief Test of class tetengo2::text::pull_parser.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if __CYGWIN__ && __GNUC__ == 4 && __GNUC_MINOR__ == 5 && __GNUC_PATCHLEVEL__ == 3
#   warning "This file does not compile with g++ 4.5.3 on Cygwin."
#else

//#include <cstddef>
//#include <memory>
//#include <stdexcept>
//#include <string>
//#include <utility>

#include <boost/test/unit_test.hpp>
//#include <boost/variant.hpp>

#include "tetengo2.text.grammar.json.h"
#include "tetengo2.text.push_parser.h"
#include "tetengo2.unique.h"

#include "tetengo2.text.pull_parser.h"


namespace
{
    // types

    typedef std::string::const_iterator iterator;

    typedef tetengo2::text::grammar::json<iterator> grammar_type;

    typedef
        tetengo2::text::push_parser<iterator, grammar_type, int, double>
        push_parser_type;

    typedef
        tetengo2::text::pull_parser<push_parser_type, std::size_t>
        pull_parser_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(text)
BOOST_AUTO_TEST_SUITE(pull_parser)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string json_text;
            std::unique_ptr<push_parser_type> p_push_parser(
                tetengo2::make_unique<push_parser_type>(
                    json_text.begin(),
                    json_text.end(),
                    tetengo2::make_unique<grammar_type>()
                )
            );

            const pull_parser_type pull_parser(std::move(p_push_parser), 3);
        }
        {
            const std::string json_text;
            std::unique_ptr<push_parser_type> p_push_parser(
                tetengo2::make_unique<push_parser_type>(
                    json_text.begin(),
                    json_text.end(),
                    tetengo2::make_unique<grammar_type>()
                )
            );

            BOOST_CHECK_THROW(
                const pull_parser_type pull_parser(
                    std::move(p_push_parser), 0
                ),
                std::invalid_argument
            );
        }
    }

    BOOST_AUTO_TEST_CASE(has_next)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string json_text;
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
            const std::string json_text(
                "{}"
            );
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

    BOOST_AUTO_TEST_CASE(peek)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string json_text;
            std::unique_ptr<push_parser_type> p_push_parser(
                tetengo2::make_unique<push_parser_type>(
                    json_text.begin(),
                    json_text.end(),
                    tetengo2::make_unique<grammar_type>()
                )
            );

            pull_parser_type pull_parser(std::move(p_push_parser), 3);

            BOOST_CHECK_THROW(pull_parser.peek(), std::logic_error);
        }
        {
            const std::string json_text(
                "{}"
            );
            std::unique_ptr<push_parser_type> p_push_parser(
                tetengo2::make_unique<push_parser_type>(
                    json_text.begin(),
                    json_text.end(),
                    tetengo2::make_unique<grammar_type>()
                )
            );

            pull_parser_type pull_parser(std::move(p_push_parser), 3);

            {
                BOOST_CHECK(pull_parser.has_next());
                const pull_parser_type::element_type& element =
                    pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 0);
                const pull_parser_type::structure_begin_type structure =
                    boost::get<pull_parser_type::structure_begin_type>(
                        element
                    );
                BOOST_CHECK(structure.name() == "object");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const pull_parser_type::element_type& element =
                    pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 1);
                const pull_parser_type::structure_end_type structure =
                    boost::get<pull_parser_type::structure_end_type>(element);
                BOOST_CHECK(structure.name() == "object");
                pull_parser.next();
            }
            BOOST_CHECK(!pull_parser.has_next());
        }
        {
            const std::string json_text(
                "{\n"
                "    \"hoge\": 42,\n"
                "    \"fuga\": [42, 42, 42]\n"
                "}\n"
            );
            std::unique_ptr<push_parser_type> p_push_parser(
                tetengo2::make_unique<push_parser_type>(
                    json_text.begin(),
                    json_text.end(),
                    tetengo2::make_unique<grammar_type>()
                )
            );

            pull_parser_type pull_parser(std::move(p_push_parser), 3);

            {
                BOOST_CHECK(pull_parser.has_next());
                const pull_parser_type::element_type& element =
                    pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 0);
                const pull_parser_type::structure_begin_type structure =
                    boost::get<pull_parser_type::structure_begin_type>(
                        element
                    );
                BOOST_CHECK(structure.name() == "object");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const pull_parser_type::element_type& element =
                    pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 0);
                const pull_parser_type::structure_begin_type structure =
                    boost::get<pull_parser_type::structure_begin_type>(
                        element
                    );
                BOOST_CHECK(structure.name() == "member");
                const pull_parser_type::attribute_map_type::const_iterator
                attribute = structure.attribute_map().find("name");
                BOOST_CHECK(attribute != structure.attribute_map().end());
                BOOST_CHECK_EQUAL(attribute->second.which(), 4);
                const std::string attribute_value =
                    boost::get<std::string>(attribute->second);
                BOOST_CHECK(attribute_value == "hoge");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const pull_parser_type::element_type& element =
                    pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 2);
                const int value =
                    boost::get<int>(
                        boost::get<pull_parser_type::value_type>(element)
                    );
                BOOST_CHECK_EQUAL(value, 42);
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const pull_parser_type::element_type& element =
                    pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 1);
                const pull_parser_type::structure_end_type structure =
                    boost::get<pull_parser_type::structure_end_type>(
                        element
                    );
                BOOST_CHECK(structure.name() == "member");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const pull_parser_type::element_type& element =
                    pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 0);
                const pull_parser_type::structure_begin_type structure =
                    boost::get<pull_parser_type::structure_begin_type>(
                        element
                    );
                BOOST_CHECK(structure.name() == "member");
                const pull_parser_type::attribute_map_type::const_iterator
                attribute = structure.attribute_map().find("name");
                BOOST_CHECK(attribute != structure.attribute_map().end());
                BOOST_CHECK_EQUAL(attribute->second.which(), 4);
                const std::string attribute_value =
                    boost::get<std::string>(attribute->second);
                BOOST_CHECK(attribute_value == "fuga");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const pull_parser_type::element_type& element =
                    pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 0);
                const pull_parser_type::structure_begin_type structure =
                    boost::get<pull_parser_type::structure_begin_type>(
                        element
                    );
                BOOST_CHECK(structure.name() == "array");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const pull_parser_type::element_type& element =
                    pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 2);
                const int value =
                    boost::get<int>(
                        boost::get<pull_parser_type::value_type>(element)
                    );
                BOOST_CHECK_EQUAL(value, 42);
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const pull_parser_type::element_type& element =
                    pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 2);
                const int value =
                    boost::get<int>(
                        boost::get<pull_parser_type::value_type>(element)
                    );
                BOOST_CHECK_EQUAL(value, 42);
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const pull_parser_type::element_type& element =
                    pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 2);
                const int value =
                    boost::get<int>(
                        boost::get<pull_parser_type::value_type>(element)
                    );
                BOOST_CHECK_EQUAL(value, 42);
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const pull_parser_type::element_type& element =
                    pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 1);
                const pull_parser_type::structure_end_type structure =
                    boost::get<pull_parser_type::structure_end_type>(element);
                BOOST_CHECK(structure.name() == "array");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const pull_parser_type::element_type& element =
                    pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 1);
                const pull_parser_type::structure_end_type structure =
                    boost::get<pull_parser_type::structure_end_type>(element);
                BOOST_CHECK(structure.name() == "member");
                pull_parser.next();
            }
            {
                BOOST_CHECK(pull_parser.has_next());
                const pull_parser_type::element_type& element =
                    pull_parser.peek();
                BOOST_CHECK_EQUAL(element.which(), 1);
                const pull_parser_type::structure_end_type structure =
                    boost::get<pull_parser_type::structure_end_type>(element);
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
            const std::string json_text;
            std::unique_ptr<push_parser_type> p_push_parser(
                tetengo2::make_unique<push_parser_type>(
                    json_text.begin(),
                    json_text.end(),
                    tetengo2::make_unique<grammar_type>()
                )
            );

            pull_parser_type pull_parser(std::move(p_push_parser), 3);

            BOOST_CHECK_THROW(pull_parser.next(), std::logic_error);
        }
        {
            const std::string json_text(
                "{}"
            );
            std::unique_ptr<push_parser_type> p_push_parser(
                tetengo2::make_unique<push_parser_type>(
                    json_text.begin(),
                    json_text.end(),
                    tetengo2::make_unique<grammar_type>()
                )
            );

            pull_parser_type pull_parser(std::move(p_push_parser), 3);

            pull_parser.next();
            pull_parser.next();
            BOOST_CHECK(!pull_parser.has_next());
        }
    }

    BOOST_AUTO_TEST_CASE(skip_next)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::string json_text;
            std::unique_ptr<push_parser_type> p_push_parser(
                tetengo2::make_unique<push_parser_type>(
                    json_text.begin(),
                    json_text.end(),
                    tetengo2::make_unique<grammar_type>()
                )
            );

            pull_parser_type pull_parser(std::move(p_push_parser), 3);

            BOOST_CHECK_THROW(pull_parser.skip_next(), std::logic_error);
        }
        {
            const std::string json_text(
                "[42]"
            );
            std::unique_ptr<push_parser_type> p_push_parser(
                tetengo2::make_unique<push_parser_type>(
                    json_text.begin(),
                    json_text.end(),
                    tetengo2::make_unique<grammar_type>()
                )
            );

            pull_parser_type pull_parser(std::move(p_push_parser), 3);

            pull_parser.next();
            pull_parser.skip_next();
            const pull_parser_type::element_type& element =
                pull_parser.peek();
            BOOST_CHECK_EQUAL(element.which(), 1);
            const pull_parser_type::structure_end_type structure =
                boost::get<pull_parser_type::structure_end_type>(element);
            BOOST_CHECK(structure.name() == "array");
        }
        {
            const std::string json_text(
                "[42]"
            );
            std::unique_ptr<push_parser_type> p_push_parser(
                tetengo2::make_unique<push_parser_type>(
                    json_text.begin(),
                    json_text.end(),
                    tetengo2::make_unique<grammar_type>()
                )
            );

            pull_parser_type pull_parser(std::move(p_push_parser), 3);

            pull_parser.next();
            pull_parser.next();
            pull_parser.skip_next();
            BOOST_CHECK(!pull_parser.has_next());
        }
        {
            const std::string json_text(
                "[42]"
            );
            std::unique_ptr<push_parser_type> p_push_parser(
                tetengo2::make_unique<push_parser_type>(
                    json_text.begin(),
                    json_text.end(),
                    tetengo2::make_unique<grammar_type>()
                )
            );

            pull_parser_type pull_parser(std::move(p_push_parser), 3);

            pull_parser.skip_next();
            BOOST_CHECK(!pull_parser.has_next());
        }
        {
            const std::string json_text(
                "[12, [34, 56], 78]"
            );
            std::unique_ptr<push_parser_type> p_push_parser(
                tetengo2::make_unique<push_parser_type>(
                    json_text.begin(),
                    json_text.end(),
                    tetengo2::make_unique<grammar_type>()
                )
            );

            pull_parser_type pull_parser(std::move(p_push_parser), 3);

            pull_parser.next();
            pull_parser.next();
            pull_parser.skip_next();
            const pull_parser_type::element_type& element =
                pull_parser.peek();
            BOOST_CHECK_EQUAL(element.which(), 2);
            const int value =
                boost::get<int>(
                    boost::get<pull_parser_type::value_type>(element)
                );
            BOOST_CHECK_EQUAL(value, 78);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

#endif

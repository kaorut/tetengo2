/*! \file
    \brief Test of class tetengo2::message::message_catalog_parser.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if __CYGWIN__ && __GNUC__ == 4 && __GNUC_MINOR__ == 5 && __GNUC_PATCHLEVEL__ == 3
#   warning "This file does not compile with g++ 4.5.3 on Cygwin."
#else

//#include <iterator>
//#include <memory>
#include <sstream>
//#include <stdexcept>
//#include <string>
//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.text.h"
#include "tetengo2.unique.h"

#include "test_tetengo2.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_tetengo2::text_type_list,
            test_tetengo2::type::text::input_stream_iterator
        >::type
        input_stream_iterator_type;

    typedef
        boost::mpl::at<
            test_tetengo2::text_type_list,
            test_tetengo2::type::text::grammar
        >::type
        grammar_type;

    typedef
        boost::mpl::at<
            test_tetengo2::text_type_list,
            test_tetengo2::type::text::push_parser
        >::type
        push_parser_type;

    typedef
        boost::mpl::at<
            test_tetengo2::text_type_list,
            test_tetengo2::type::text::pull_parser
        >::type
        pull_parser_type;

    typedef
        boost::mpl::at<
            test_tetengo2::type_list, test_tetengo2::type::string
        >::type
        string_type;

    typedef
        boost::mpl::at<
            test_tetengo2::message_type_list,
            test_tetengo2::type::message::message_catalog_parser
        >::type
        message_catalog_parser_type;

    typedef message_catalog_parser_type::entry_type entry_type;


    // data

    const std::string catalog0(
        ""
    );

    const std::string catalog1(
        "{\n"
        "    \"header\":\n"
        "    {\n"
        "        \"Key1\": \"Value1\"\n"
        "    }\n"
        "}\n"
    );

    const std::string catalog2(
        "{\n"
        "    \"body\":\n"
        "    {\n"
        "    }\n"
        "}\n"
    );

    const std::string catalog3(
        "{\n"
        "    \"body\":\n"
        "    {\n"
        "        \"Key1\": \"Value1\"\n"
        "    }\n"
        "}\n"
    );

    const std::string catalog4(
        "{\n"
        "    \"header\":\n"
        "    {\n"
        "        \"Key1\": \"Value1\",\n"
        "        \"Key2\": [12, 34, 56]\n"
        "    },\n"
        "    \"body\":\n"
        "    {\n"
        "        \"Key1\": \"Value1\",\n"
        "        \"Key2\": \"Value2\"\n"
        "    }\n"
        "}\n"
    );


    // functions

    std::unique_ptr<pull_parser_type> create_pull_parser(
        std::istringstream& input
    )
    {
        std::unique_ptr<grammar_type> p_grammar =
            tetengo2::make_unique<grammar_type>();

        std::unique_ptr<push_parser_type> p_push_parser =
            tetengo2::make_unique<push_parser_type>(
                input_stream_iterator_type(
                    std::istreambuf_iterator<char>(input)
                ),
                input_stream_iterator_type(std::istreambuf_iterator<char>()),
                std::move(p_grammar)
            );

        return tetengo2::make_unique<pull_parser_type>(
            std::move(p_push_parser), 3
        );
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(message_catalog_parser)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::istringstream input_stream(catalog0);
        const std::unique_ptr<message_catalog_parser_type> p_parser =
            tetengo2::make_unique<message_catalog_parser_type>(
                create_pull_parser(input_stream)
            );
    }

    BOOST_AUTO_TEST_CASE(has_next)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream input_stream(catalog0);
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream)
                );

            BOOST_CHECK(!p_parser->has_next());
        }
        {
            std::istringstream input_stream(catalog1);
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream)
                );

            BOOST_CHECK(!p_parser->has_next());
        }
        {
            std::istringstream input_stream(catalog2);
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream)
                );

            BOOST_CHECK(!p_parser->has_next());
        }
        {
            std::istringstream input_stream(catalog3);
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream)
                );

            BOOST_CHECK(p_parser->has_next());
        }
        {
            std::istringstream input_stream(catalog4);
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream)
                );

            BOOST_CHECK(p_parser->has_next());
        }
    }

    BOOST_AUTO_TEST_CASE(peek)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream input_stream(catalog0);
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream)
                );

            BOOST_CHECK_THROW(p_parser->peek(), std::logic_error);
        }
        {
            std::istringstream input_stream(catalog1);
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream)
                );

            BOOST_CHECK_THROW(p_parser->peek(), std::logic_error);
        }
        {
            std::istringstream input_stream(catalog2);
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream)
                );

            BOOST_CHECK_THROW(p_parser->peek(), std::logic_error);
        }
        {
            std::istringstream input_stream(catalog3);
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream)
                );

            const entry_type& entry = p_parser->peek();
            BOOST_CHECK(entry.first == string_type(TETENGO2_TEXT("Key1")));
            BOOST_CHECK(entry.second == string_type(TETENGO2_TEXT("Value1")));
        }
        {
            std::istringstream input_stream(catalog4);
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream)
                );

            const entry_type& entry = p_parser->peek();
            BOOST_CHECK(entry.first == string_type(TETENGO2_TEXT("Key1")));
            BOOST_CHECK(entry.second == string_type(TETENGO2_TEXT("Value1")));
        }
    }

    BOOST_AUTO_TEST_CASE(next)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream input_stream(catalog0);
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream)
                );

            BOOST_CHECK_THROW(p_parser->next(), std::logic_error);
        }
        {
            std::istringstream input_stream(catalog1);
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream)
                );

            BOOST_CHECK_THROW(p_parser->next(), std::logic_error);
        }
        {
            std::istringstream input_stream(catalog2);
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream)
                );

            BOOST_CHECK_THROW(p_parser->next(), std::logic_error);
        }
        {
            std::istringstream input_stream(catalog3);
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream)
                );

            {
                const entry_type& entry = p_parser->peek();
                BOOST_CHECK(
                    entry.first == string_type(TETENGO2_TEXT("Key1"))
                );
                BOOST_CHECK(
                    entry.second == string_type(TETENGO2_TEXT("Value1"))
                );
                p_parser->next();
            }
            BOOST_CHECK(!p_parser->has_next());
        }
        {
            std::istringstream input_stream(catalog4);
            const std::unique_ptr<message_catalog_parser_type> p_parser =
                tetengo2::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream)
                );

            {
                const entry_type& entry = p_parser->peek();
                BOOST_CHECK(
                    entry.first == string_type(TETENGO2_TEXT("Key1"))
                );
                BOOST_CHECK(
                    entry.second == string_type(TETENGO2_TEXT("Value1"))
                );
                p_parser->next();
            }
            {
                const entry_type& entry = p_parser->peek();
                BOOST_CHECK(
                    entry.first == string_type(TETENGO2_TEXT("Key2"))
                );
                BOOST_CHECK(
                    entry.second == string_type(TETENGO2_TEXT("Value2"))
                );
                p_parser->next();
            }
            BOOST_CHECK(!p_parser->has_next());
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

#endif

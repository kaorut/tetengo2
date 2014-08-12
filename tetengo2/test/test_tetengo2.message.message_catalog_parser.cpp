/*! \file
    \brief Test of class tetengo2::message::message_catalog_parser.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <iterator>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/predef.h>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include "test_tetengo2.detail_type_list.h"
#include "test_tetengo2.type_list.h"


namespace
{
    // types

    using size_type = boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::size>::type;

    using string_type = boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::string>::type;

    using io_string_type = boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::io_string>::type;

    using input_stream_iterator_type = boost::spirit::multi_pass<std::istreambuf_iterator<io_string_type::value_type>>;

    using grammar_type = tetengo2::text::grammar::json<input_stream_iterator_type>;

    using push_parser_type = tetengo2::text::push_parser<input_stream_iterator_type, grammar_type, int, double>;

    using pull_parser_type = 
        tetengo2::text::pull_parser<input_stream_iterator_type, grammar_type, int, double, size_type>;

    using encoding_details_type =
        boost::mpl::at<test_tetengo2::detail_type_list, test_tetengo2::type::detail::encoding>::type;

    using internal_encoding_type = tetengo2::text::encoding::locale<string_type, encoding_details_type>;

    using message_catalog_encoding_type = tetengo2::text::encoding::locale<io_string_type, encoding_details_type>;

    using message_catalog_encoder_type =
        tetengo2::text::encoder<internal_encoding_type, message_catalog_encoding_type>;

    using message_catalog_parser_type =
        tetengo2::message::message_catalog_parser<
            input_stream_iterator_type, string_type, size_type, message_catalog_encoder_type
        >;

    using entry_type = message_catalog_parser_type::entry_type;


    // data

    const std::string catalog0{
        ""
    };

    const std::string catalog1{
        "{\n"
        "    \"header\":\n"
        "    {\n"
        "        \"Key1\": \"Value1\"\n"
        "    }\n"
        "}\n"
    };

    const std::string catalog2{
        "{\n"
        "    \"body\":\n"
        "    {\n"
        "    }\n"
        "}\n"
    };

    const std::string catalog3{
        "{\n"
        "    \"body\":\n"
        "    {\n"
        "        \"Key1\": \"Value1\"\n"
        "    }\n"
        "}\n"
    };

    const std::string catalog4{
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
    };


    // functions

#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    std::unique_ptr<pull_parser_type> create_pull_parser(std::istringstream& input)
    {
        auto p_grammar = tetengo2::stdalt::make_unique<grammar_type>();

        auto p_push_parser =
            tetengo2::stdalt::make_unique<push_parser_type>(
                input_stream_iterator_type{ std::istreambuf_iterator < char > {input} },
                input_stream_iterator_type{ std::istreambuf_iterator < char > {} },
                std::move(p_grammar)
            );

        return tetengo2::stdalt::make_unique<pull_parser_type>(std::move(p_push_parser), 3);
    }
#endif

}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(message_catalog_parser)
    // test cases

#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::istringstream input_stream{ catalog0 };
        const auto p_parser =
            tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));
    }

    BOOST_AUTO_TEST_CASE(has_next)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream input_stream{ catalog0 };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));

            BOOST_CHECK(!p_parser->has_next());
        }
        {
            std::istringstream input_stream{ catalog1 };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));

            BOOST_CHECK(!p_parser->has_next());
        }
        {
            std::istringstream input_stream{ catalog2 };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));

            BOOST_CHECK(!p_parser->has_next());
        }
        {
            std::istringstream input_stream{ catalog3 };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));

            BOOST_CHECK(p_parser->has_next());
        }
        {
            std::istringstream input_stream{ catalog4 };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));

            BOOST_CHECK(p_parser->has_next());
        }
    }

    BOOST_AUTO_TEST_CASE(peek)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream input_stream{ catalog0 };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));

            BOOST_CHECK_THROW(p_parser->peek(), std::logic_error);
        }
        {
            std::istringstream input_stream{ catalog1 };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));

            BOOST_CHECK_THROW(p_parser->peek(), std::logic_error);
        }
        {
            std::istringstream input_stream{ catalog2 };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));

            BOOST_CHECK_THROW(p_parser->peek(), std::logic_error);
        }
        {
            std::istringstream input_stream{ catalog3 };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));

            const auto& entry = p_parser->peek();
            BOOST_CHECK(entry.first == string_type{ TETENGO2_TEXT("Key1") });
            BOOST_CHECK(entry.second == string_type{ TETENGO2_TEXT("Value1") });
        }
        {
            std::istringstream input_stream{ catalog4 };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));

            const auto& entry = p_parser->peek();
            BOOST_CHECK(entry.first == string_type{ TETENGO2_TEXT("Key1") });
            BOOST_CHECK(entry.second == string_type{ TETENGO2_TEXT("Value1") });
        }
    }

    BOOST_AUTO_TEST_CASE(next)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream input_stream{ catalog0 };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));

            BOOST_CHECK_THROW(p_parser->next(), std::logic_error);
        }
        {
            std::istringstream input_stream{ catalog1 };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));

            BOOST_CHECK_THROW(p_parser->next(), std::logic_error);
        }
        {
            std::istringstream input_stream{ catalog2 };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));

            BOOST_CHECK_THROW(p_parser->next(), std::logic_error);
        }
        {
            std::istringstream input_stream{ catalog3 };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));

            {
                const auto& entry = p_parser->peek();
                BOOST_CHECK(entry.first == string_type{ TETENGO2_TEXT("Key1") });
                BOOST_CHECK(entry.second == string_type{ TETENGO2_TEXT("Value1") });
                p_parser->next();
            }
            BOOST_CHECK(!p_parser->has_next());
        }
        {
            std::istringstream input_stream{ catalog4 };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(create_pull_parser(input_stream));

            {
                const auto& entry = p_parser->peek();
                BOOST_CHECK(entry.first == string_type{ TETENGO2_TEXT("Key1") });
                BOOST_CHECK(entry.second == string_type{ TETENGO2_TEXT("Value1") });
                p_parser->next();
            }
            {
                const auto& entry = p_parser->peek();
                BOOST_CHECK(entry.first == string_type{ TETENGO2_TEXT("Key2") });
                BOOST_CHECK(entry.second == string_type{ TETENGO2_TEXT("Value2") });
                p_parser->next();
            }
            BOOST_CHECK(!p_parser->has_next());
        }
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

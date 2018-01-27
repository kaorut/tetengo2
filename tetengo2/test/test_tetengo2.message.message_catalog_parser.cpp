/*! \file
    \brief Test of class tetengo2::message::message_catalog_parser.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <istream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/preprocessor.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/message/message_catalog_parser.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoding/locale.h>
#include <tetengo2/text/encoding/polymorphic.h>
#include <tetengo2/text/grammar/json.h>
#include <tetengo2/text/push_parser.h>
#include <tetengo2/text/pull_parser.h>


namespace
{
    // types

    using input_stream_iterator_type =
        tetengo2::iterator::observable_forward_iterator<
            boost::spirit::multi_pass<std::istreambuf_iterator<char>>
        >;

    using input_encoding_type = tetengo2::text::encoding::polymorphic<std::string>;

    using grammar_type = tetengo2::text::grammar::json<input_stream_iterator_type>;

    using push_parser_type = tetengo2::text::push_parser<input_stream_iterator_type>;

    using pull_parser_type = tetengo2::text::pull_parser<input_stream_iterator_type>;

    using message_catalog_parser_type = tetengo2::message::message_catalog_parser<input_stream_iterator_type>;

    using string_type = message_catalog_parser_type::string_type;


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

    std::unique_ptr<pull_parser_type> create_pull_parser(std::istream& input)
    {
        auto p_grammar = tetengo2::stdalt::make_unique<grammar_type>();

        const auto first =
            tetengo2::iterator::make_observable_forward_iterator(
                boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{ input })
            );
        const auto last =
            tetengo2::iterator::make_observable_forward_iterator(
                boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>{})
            );
        auto p_push_parser = tetengo2::stdalt::make_unique<push_parser_type>(first, last, std::move(p_grammar));

        return tetengo2::stdalt::make_unique<pull_parser_type>(std::move(p_push_parser), 3);
    }

    input_encoding_type make_input_encoding()
    {
        return tetengo2::text::encoding::make_polymorphic<tetengo2::text::encoding::locale<std::string>>();
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(message_catalog_parser)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog0) };
        const auto p_parser =
            tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                create_pull_parser(input_stream), make_input_encoding()
            );
    }

    BOOST_AUTO_TEST_CASE(has_next)
    {
        BOOST_TEST_PASSPOINT();

        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog0) };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream), make_input_encoding()
                );

            BOOST_TEST(!p_parser->has_next());
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog1) };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream), make_input_encoding()
                );

            BOOST_TEST(!p_parser->has_next());
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog2) };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream), make_input_encoding()
                );

            BOOST_TEST(!p_parser->has_next());
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog3) };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream), make_input_encoding()
                );

            BOOST_TEST(p_parser->has_next());
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog4) };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream), make_input_encoding()
                );

            BOOST_TEST(p_parser->has_next());
        }
    }

    BOOST_AUTO_TEST_CASE(peek)
    {
        BOOST_TEST_PASSPOINT();

        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog0) };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream), make_input_encoding()
                );

            BOOST_CHECK_THROW(p_parser->peek(), std::logic_error);
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog1) };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream), make_input_encoding()
                );

            BOOST_CHECK_THROW(p_parser->peek(), std::logic_error);
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog2) };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream), make_input_encoding()
                );

            BOOST_CHECK_THROW(p_parser->peek(), std::logic_error);
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog3) };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream), make_input_encoding()
                );

            const auto& entry = p_parser->peek();
            BOOST_CHECK(entry.first == string_type{ TETENGO2_TEXT("Key1") });
            BOOST_CHECK(entry.second == string_type{ TETENGO2_TEXT("Value1") });
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog4) };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream), make_input_encoding()
                );

            const auto& entry = p_parser->peek();
            BOOST_CHECK(entry.first == string_type{ TETENGO2_TEXT("Key1") });
            BOOST_CHECK(entry.second == string_type{ TETENGO2_TEXT("Value1") });
        }
    }

    BOOST_AUTO_TEST_CASE(next)
    {
        BOOST_TEST_PASSPOINT();

        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog0) };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream), make_input_encoding()
                );

            BOOST_CHECK_THROW(p_parser->next(), std::logic_error);
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog1) };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream), make_input_encoding()
                );

            BOOST_CHECK_THROW(p_parser->next(), std::logic_error);
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog2) };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream), make_input_encoding()
                );

            BOOST_CHECK_THROW(p_parser->next(), std::logic_error);
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog3) };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream), make_input_encoding()
                );

            {
                const auto& entry = p_parser->peek();
                BOOST_CHECK(entry.first == string_type{ TETENGO2_TEXT("Key1") });
                BOOST_CHECK(entry.second == string_type{ TETENGO2_TEXT("Value1") });
                p_parser->next();
            }
            BOOST_TEST(!p_parser->has_next());
        }
        {
            boost::iostreams::filtering_istream input_stream{ boost::make_iterator_range(catalog4) };
            const auto p_parser =
                tetengo2::stdalt::make_unique<message_catalog_parser_type>(
                    create_pull_parser(input_stream), make_input_encoding()
                );

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
            BOOST_TEST(!p_parser->has_next());
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

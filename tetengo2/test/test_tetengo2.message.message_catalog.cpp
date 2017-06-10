/*! \file
    \brief Test of class tetengo2::message::message_catalog.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <iterator>
#include <locale>
#include <stdexcept>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/predef.h>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/message/message_catalog_parser.h>
#include <tetengo2/message/messages.h>
#include <tetengo2/message/message_catalog.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>

#include "test_tetengo2.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::type_list::common;

    using size_type = common_type_list_type::size_type;

    using string_type = common_type_list_type::string_type;

    using io_string_type = common_type_list_type::io_string_type;

    using input_stream_iterator_type =
        tetengo2::iterator::observable_forward_iterator<
            boost::spirit::multi_pass<std::istreambuf_iterator<io_string_type::value_type>>
        >;

    using internal_encoding_type = tetengo2::text::encoding::locale<string_type>;

    using message_catalog_encoding_type = tetengo2::text::encoding::locale<io_string_type>;

    using message_catalog_encoder_type =
        tetengo2::text::encoder<internal_encoding_type, message_catalog_encoding_type>;

    using message_catalog_parser_type =
        tetengo2::message::message_catalog_parser<
            input_stream_iterator_type, string_type, size_type, message_catalog_encoder_type
        >;

    using locale_name_encoding_type = tetengo2::text::encoding::locale<io_string_type>;

    using locale_name_encoder_type = tetengo2::text::encoder<internal_encoding_type, locale_name_encoding_type>;

    using messages_type =
        tetengo2::message::messages<
            input_stream_iterator_type, string_type, size_type, message_catalog_encoder_type, locale_name_encoder_type
        >;

    using message_catalog_type =
        tetengo2::message::message_catalog<
            input_stream_iterator_type, string_type, size_type, message_catalog_encoder_type, locale_name_encoder_type
        >;

    struct set_global_locale
    {
        const std::locale m_initial_locale;

        explicit set_global_locale(const std::locale& locale)
        :
        m_initial_locale(
            std::locale::global(
                std::locale{
                    locale,
                    tetengo2::stdalt::make_unique<messages_type>(
                        boost::filesystem::path{ "messages.test" }, locale
                    ).release()
                }
            )
        )
        {}

        ~set_global_locale()
        noexcept
        {
            std::locale::global(m_initial_locale);
        }

    };


    // functions

    bool locale_supported()
    {
        try
        {
            std::locale locale{ "" };
            return true;
        }
        catch (const std::runtime_error&)
        {
            return false;
        }
    }

    std::locale make_locale(const std::string& name)
    {
        try
        {
            return std::locale{ name.c_str() };
        }
        catch (const std::runtime_error&)
        {
            return std::locale::classic();
        }
    }


    // data

#if BOOST_OS_WINDOWS
    const std::locale locale_en = make_locale("English");

    const std::locale locale_ja = make_locale("Japanese_Japan");

    const std::locale locale_zh = make_locale("Chinese");
#else
    const std::locale locale_en = make_locale("en_US");

    const std::locale locale_ja = make_locale("ja_JP.UTF-8");

    const std::locale locale_zh = make_locale("zh_CN");
#endif

}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(message_catalog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        if (locale_supported())
        {
            {
                const set_global_locale global_locale{ locale_en };

                const message_catalog_type message_catalog{};
            }
            {
                const set_global_locale global_locale{ locale_ja };

                const message_catalog_type message_catalog{};
            }
            {
                const set_global_locale global_locale{ locale_zh };

                const message_catalog_type message_catalog{};
            }
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }

    BOOST_AUTO_TEST_CASE(get)
    {
        BOOST_TEST_PASSPOINT();

        if (locale_supported())
        {
            {
                const set_global_locale global_locale{ locale_en };

                const message_catalog_type message_catalog{};

                BOOST_CHECK(
                    message_catalog.get(TETENGO2_TEXT("Language")) == string_type{ TETENGO2_TEXT("English") }
                );
                BOOST_CHECK(
                    message_catalog.get(TETENGO2_TEXT("Name:Space:Hello")) == string_type{ TETENGO2_TEXT("Hi") }
                );
                BOOST_CHECK(
                    message_catalog.get(TETENGO2_TEXT("Name:Space:ByeBye")) == string_type{ TETENGO2_TEXT("ByeBye") }
                );
                BOOST_CHECK(
                    message_catalog.get(TETENGO2_TEXT("Name:Space:Colon:")) == string_type{ TETENGO2_TEXT("Colon:") }
                );
                BOOST_CHECK(
                    message_catalog.get(TETENGO2_TEXT("Name:Space:Esc\\:ape")) ==
                    string_type{ TETENGO2_TEXT("Esc:ape") }
                );
            }
            {
                const set_global_locale global_locale{ locale_ja };

                const message_catalog_type message_catalog{};

                BOOST_CHECK(
                    message_catalog.get(TETENGO2_TEXT("Language")) == string_type{ TETENGO2_TEXT("Japanese") }
                );
                BOOST_CHECK(
                    message_catalog.get(TETENGO2_TEXT("Name:Space:Hello")) ==
                    string_type{ TETENGO2_TEXT("Konnichiwa") }
                );
                BOOST_CHECK(
                    message_catalog.get(TETENGO2_TEXT("Name:Space:ByeBye")) == string_type{ TETENGO2_TEXT("ByeBye") }
                );
                BOOST_CHECK(
                    message_catalog.get(TETENGO2_TEXT("Name:Space:Colon:")) == string_type{ TETENGO2_TEXT("Colon:") }
                );
                BOOST_CHECK(
                    message_catalog.get(TETENGO2_TEXT("Name:Space:Esc\\:ape")) ==
                    string_type{ TETENGO2_TEXT("Esc:ape") }
                );
            }
            {
                const set_global_locale global_locale{ locale_zh };

                const message_catalog_type message_catalog{};

                BOOST_CHECK(
                    message_catalog.get(TETENGO2_TEXT("Language")) == string_type{ TETENGO2_TEXT("Language") }
                );
                BOOST_CHECK(
                    message_catalog.get(TETENGO2_TEXT("Name:Space:Hello")) == string_type{ TETENGO2_TEXT("Hello") }
                );
                BOOST_CHECK(
                    message_catalog.get(TETENGO2_TEXT("Name:Space:ByeBye")) == string_type{ TETENGO2_TEXT("ByeBye") }
                );
                BOOST_CHECK(
                    message_catalog.get(TETENGO2_TEXT("Name:Space:Colon:")) == string_type{ TETENGO2_TEXT("Colon:") }
                );
                BOOST_CHECK(
                    message_catalog.get(TETENGO2_TEXT("Name:Space:Esc\\:ape")) ==
                    string_type{ TETENGO2_TEXT("Esc:ape") }
                );
            }
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

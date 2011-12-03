/*! \file
    \brief Test of class tetengo2::message::messages.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <ios>
#include <istream>
//#include <locale>
//#include <stdexcept>
//#include <string>

//#include <boost/filesystem.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/scope_exit.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.message.message_catalog_parser_j.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"
#include "tetengo2.text.grammar.json.h"
#include "tetengo2.text.pull_parser.h"
#include "tetengo2.text.push_parser.h"
#include "tetengo2.unique.h"

#include "tetengo2.message.messages.h"


namespace
{
    // types

    typedef
        boost::spirit::multi_pass<std::istreambuf_iterator<char>>
        iterator_type;

    typedef tetengo2::text::grammar::json<iterator_type> grammar_type;

    typedef
        tetengo2::text::push_parser<iterator_type, grammar_type, int, double>
        push_parser_type;

    typedef
        tetengo2::text::pull_parser<push_parser_type, std::size_t>
        pull_parser_type;

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::text::encoding::locale<std::string, encoding_details_type>
        internal_encoding_type;

    typedef
        tetengo2::text::encoding::locale<std::string, encoding_details_type>
        message_catalog_encoding_type;

    typedef
        tetengo2::text::encoder<
            internal_encoding_type, message_catalog_encoding_type
        >
        message_catalog_encoder_type;

    typedef
        tetengo2::text::encoding::locale<std::string, encoding_details_type>
        locale_name_encoding_type;

    typedef
        tetengo2::text::encoder<
            internal_encoding_type, locale_name_encoding_type
        >
        locale_name_encoder_type;

    typedef
        tetengo2::message::message_catalog_parser_j<
            pull_parser_type, std::string, message_catalog_encoder_type
        >
        message_catalog_parser_type;

    typedef
        tetengo2::message::messages<
            boost::filesystem::path,
            message_catalog_parser_type,
            locale_name_encoder_type
        >
        messages_type;

    struct set_global_locale
    {
        const std::locale m_initial_locale;

        explicit set_global_locale(const std::locale& locale)
        :
        m_initial_locale(
            std::locale::global(
                std::locale(
                    locale,
                    tetengo2::make_unique<messages_type>(
                        boost::filesystem::path("messages.test"), locale
                    ).release()
                )
            )
        )
        {}

        ~set_global_locale()
        {
            std::locale::global(m_initial_locale);
        }

    };


    // functions

    bool locale_supported()
    {
        try
        {
            std::locale locale("");
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
            return std::locale(name.c_str());
        }
        catch (const std::runtime_error&)
        {
            return std::locale::classic();
        }
    }


    // data

#if defined(_WIN32)
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
BOOST_AUTO_TEST_SUITE(messages)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        if (locale_supported())
        {
            const messages_type messages(
                boost::filesystem::path("messages.test"), std::locale()
            );

            BOOST_CHECK_THROW(
                messages_type(boost::filesystem::path(""), std::locale()),
                std::ios_base::failure
            );

            BOOST_CHECK_THROW(
                messages_type(
                    boost::filesystem::path("messages.test") / "English.txt",
                    std::locale()
                ),
                std::ios_base::failure
            );
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }

    BOOST_AUTO_TEST_CASE(do_open)
    {
        BOOST_TEST_PASSPOINT();

        if (locale_supported())
        {
            {
                const set_global_locale global_locale(locale_en);
                const std::messages<char>& messages =
                    std::use_facet<std::messages<char>>(std::locale());
                BOOST_CHECK(dynamic_cast<const messages_type*>(&messages));

                const std::messages_base::catalog catalog_id =
                    messages.open("", std::locale());
                BOOST_SCOPE_EXIT((&messages)(catalog_id))
                {
                    messages.close(catalog_id);
                } BOOST_SCOPE_EXIT_END;

                BOOST_CHECK_GE(catalog_id, 0);

                BOOST_CHECK_THROW(
                    messages.open("", std::locale()), std::runtime_error
                );
            }
            {
                const set_global_locale global_locale(locale_ja);
                const std::messages<char>& messages =
                    std::use_facet<std::messages<char>>(std::locale());
                BOOST_CHECK(dynamic_cast<const messages_type*>(&messages));

                const std::messages_base::catalog catalog_id =
                    messages.open("", std::locale());
                BOOST_SCOPE_EXIT((&messages)(catalog_id))
                {
                    messages.close(catalog_id);
                } BOOST_SCOPE_EXIT_END;

                BOOST_CHECK_GE(catalog_id, 0);

                BOOST_CHECK_THROW(
                    messages.open("", std::locale()), std::runtime_error
                );
            }
            {
                const set_global_locale global_locale(locale_zh);
                const std::messages<char>& messages =
                    std::use_facet<std::messages<char>>(std::locale());
                BOOST_CHECK(dynamic_cast<const messages_type*>(&messages));

                const std::messages_base::catalog catalog_id =
                    messages.open("", std::locale());
                BOOST_CHECK_LT(catalog_id, 0);
            }
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }

    BOOST_AUTO_TEST_CASE(do_get)
    {
        BOOST_TEST_PASSPOINT();

        if (locale_supported())
        {
            {
                const set_global_locale global_locale(locale_en);
                const std::messages<char>& messages =
                    std::use_facet<std::messages<char>>(std::locale());
                BOOST_CHECK(dynamic_cast<const messages_type*>(&messages));

                BOOST_CHECK_THROW(
                    messages.get(0, 0, 0, "Language"), std::runtime_error
                );

                BOOST_CHECK(
                    messages.get(-1, 0, 0, "Language") == "Language"
                );

                const std::messages_base::catalog catalog_id =
                    messages.open("", std::locale());
                BOOST_SCOPE_EXIT((&messages)(catalog_id))
                {
                    messages.close(catalog_id);
                } BOOST_SCOPE_EXIT_END;

                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, "Language") == "English"
                );
                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, "Name:Space:Hello") ==
                    "Hi"
                );
                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, "Name:Space:ByeBye") ==
                    "ByeBye"
                );
            }
            {
                const set_global_locale global_locale(locale_ja);
                const std::messages<char>& messages =
                    std::use_facet<std::messages<char>>(std::locale());
                BOOST_CHECK(dynamic_cast<const messages_type*>(&messages));

                BOOST_CHECK_THROW(
                    messages.get(0, 0, 0, "Language"), std::runtime_error
                );

                BOOST_CHECK(
                    messages.get(-1, 0, 0, "Language") == "Language"
                );

                const std::messages_base::catalog catalog_id =
                    messages.open("", std::locale());
                BOOST_SCOPE_EXIT((&messages)(catalog_id))
                {
                    messages.close(catalog_id);
                } BOOST_SCOPE_EXIT_END;

                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, "Language") == "Japanese"
                );
                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, "Name:Space:Hello") ==
                    "Konnichiwa"
                );
                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, "Name:Space:ByeBye") ==
                    "ByeBye"
                );
            }
            {
                const set_global_locale global_locale(locale_zh);
                const std::messages<char>& messages =
                    std::use_facet<std::messages<char>>(std::locale());
                BOOST_CHECK(dynamic_cast<const messages_type*>(&messages));

                const std::messages_base::catalog catalog_id =
                    messages.open("", std::locale());

                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, "Language") == "Language"
                );
                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, "Name:Space:Hello") ==
                    "Hello"
                );
                BOOST_CHECK(
                    messages.get(catalog_id, 0, 0, "Name:Space:ByeBye") ==
                    "ByeBye"
                );
            }
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }

    BOOST_AUTO_TEST_CASE(do_close)
    {
        BOOST_TEST_PASSPOINT();

        if (locale_supported())
        {
            {
                const set_global_locale global_locale(locale_en);
                const std::messages<char>& messages =
                    std::use_facet<std::messages<char>>(std::locale());
                BOOST_CHECK(dynamic_cast<const messages_type*>(&messages));

                BOOST_CHECK_THROW(messages.close(0), std::runtime_error);

                BOOST_CHECK_NO_THROW(messages.close(-1));

                const std::messages_base::catalog catalog_id =
                    messages.open("", std::locale());
                BOOST_SCOPE_EXIT((&messages)(catalog_id))
                {
                    messages.close(catalog_id);

                    BOOST_CHECK_THROW(
                        messages.close(catalog_id), std::runtime_error
                    );
                } BOOST_SCOPE_EXIT_END;
            }
            {
                const set_global_locale global_locale(locale_ja);
                const std::messages<char>& messages =
                    std::use_facet<std::messages<char>>(std::locale());
                BOOST_CHECK(dynamic_cast<const messages_type*>(&messages));

                BOOST_CHECK_THROW(messages.close(0), std::runtime_error);

                BOOST_CHECK_NO_THROW(messages.close(-1));

                const std::messages_base::catalog catalog_id =
                    messages.open("", std::locale());
                BOOST_SCOPE_EXIT((&messages)(catalog_id))
                {
                    messages.close(catalog_id);

                    BOOST_CHECK_THROW(
                        messages.close(catalog_id), std::runtime_error
                    );
                } BOOST_SCOPE_EXIT_END;
            }
            {
                const set_global_locale global_locale(locale_zh);
                const std::messages<char>& messages =
                    std::use_facet<std::messages<char>>(std::locale());
                BOOST_CHECK(dynamic_cast<const messages_type*>(&messages));

                const std::messages_base::catalog catalog_id =
                    messages.open("", std::locale());
                BOOST_CHECK_NO_THROW(messages.close(catalog_id));
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

/*! \file
    \brief Test of class tetengo2::message_catalog.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <istream>
//#include <locale>
//#include <stdexcept>
//#include <string>

//#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.message_catalog_parser.h"
#include "tetengo2.messages.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"
#include "tetengo2.unique.h"

#include "tetengo2.message_catalog.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::encoding::locale<std::string, encoding_details_type>
        internal_encoding_type;

    typedef
        tetengo2::encoding::locale<std::string, encoding_details_type>
        message_catalog_encoding_type;

    typedef
        tetengo2::text::encoder<
            internal_encoding_type, message_catalog_encoding_type
        >
        message_catalog_encoder_type;

    typedef
        tetengo2::encoding::locale<std::string, encoding_details_type>
        locale_name_encoding_type;

    typedef
        tetengo2::text::encoder<
            internal_encoding_type, locale_name_encoding_type
        >
        locale_name_encoder_type;

    typedef
        tetengo2::message_catalog_parser<
            std::istream, std::string, message_catalog_encoder_type
        >
        message_catalog_parser_type;

    typedef
        tetengo2::messages<
            boost::filesystem::path,
            message_catalog_parser_type,
            locale_name_encoder_type
        >
        messages_type;

    typedef tetengo2::message_catalog<messages_type> message_catalog_type;

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
BOOST_AUTO_TEST_SUITE(message_catalog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        if (locale_supported())
        {
            {
                const set_global_locale global_locale(locale_en);

                const message_catalog_type message_catalog;
            }
            {
                const set_global_locale global_locale(locale_ja);

                const message_catalog_type message_catalog;
            }
            {
                const set_global_locale global_locale(locale_zh);

                const message_catalog_type message_catalog;
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
                const set_global_locale global_locale(locale_en);

                const message_catalog_type message_catalog;

                BOOST_CHECK(message_catalog.get("Language") == "English");
                BOOST_CHECK(
                    message_catalog.get("Name:Space:Hello") == "Hi"
                );
                BOOST_CHECK(
                    message_catalog.get("Name:Space:ByeBye") == "ByeBye"
                );
            }
            {
                const set_global_locale global_locale(locale_ja);

                const message_catalog_type message_catalog;

                BOOST_CHECK(message_catalog.get("Language") == "Japanese");
                BOOST_CHECK(
                    message_catalog.get("Name:Space:Hello") == "Konnichiwa"
                );
                BOOST_CHECK(
                    message_catalog.get("Name:Space:ByeBye") == "ByeBye"
                );
            }
            {
                const set_global_locale global_locale(locale_zh);

                const message_catalog_type message_catalog;

                BOOST_CHECK(message_catalog.get("Language") == "Language");
                BOOST_CHECK(
                    message_catalog.get("Name:Space:Hello") == "Hello"
                );
                BOOST_CHECK(
                    message_catalog.get("Name:Space:ByeBye") == "ByeBye"
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

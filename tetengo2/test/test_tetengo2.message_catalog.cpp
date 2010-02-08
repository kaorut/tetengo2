/*! \file
    \brief Test of class tetengo2::message_catalog.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <istream>
//#include <locale>
//#include <stdexcept>
//#include <string>

//#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "stub_tetengo2.encode.h"
#include "tetengo2.message_catalog_parser.h"
#include "tetengo2.messages.h"

#include "tetengo2.message_catalog.h"


namespace
{
    // types

    typedef
        tetengo2::message_catalog_parser<
            std::istream, std::string, stub_tetengo2::encode
        >
        message_catalog_parser_type;

    typedef
        tetengo2::messages<
            boost::filesystem::path,
            message_catalog_parser_type,
            stub_tetengo2::encode
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
                    new messages_type(
                        boost::filesystem::path("messages.test"), locale
                    )
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
            }
            {
                const set_global_locale global_locale(locale_ja);

                const message_catalog_type message_catalog;

                BOOST_CHECK(message_catalog.get("Language") == "Japanese");
            }
            {
                const set_global_locale global_locale(locale_zh);

                const message_catalog_type message_catalog;

                BOOST_CHECK(message_catalog.get("Language") == "Language");
            }
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

/*! \file
    \brief Test of class tetengo2::message_catalog.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if defined(_MSC_VER)

#include <istream>
//#include <locale>
//#include <string>

//#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.message_catalog_parser.h"
#include "tetengo2.messages.h"
#include "tetengo2.win32.encode.h"

#include "tetengo2.message_catalog.h"


namespace
{
    // types

    typedef
        tetengo2::message_catalog_parser<
            std::istream, std::wstring, tetengo2::win32::encode
        >
        message_catalog_parser_type;

    typedef
        tetengo2::messages<
            boost::filesystem::wpath,
            message_catalog_parser_type,
            tetengo2::win32::encode
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
                        boost::filesystem::wpath(L"messages.test"), locale
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


    // data

#if defined(_WIN32)
    const std::locale locale_en("English");

    const std::locale locale_ja("Japanese_Japan");

    const std::locale locale_zh("Chinese");
#else
    const std::locale locale_en("en");

    const std::locale locale_ja("ja_JP");

    const std::locale locale_zh("zh");
#endif

}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(message_catalog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

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

    BOOST_AUTO_TEST_CASE(get)
    {
        BOOST_TEST_PASSPOINT();

        {
            const set_global_locale global_locale(locale_en);

            const message_catalog_type message_catalog;

            BOOST_CHECK(message_catalog.get(L"Language") == L"English");
        }
        {
            const set_global_locale global_locale(locale_ja);

            const message_catalog_type message_catalog;

            BOOST_CHECK(message_catalog.get(L"Language") == L"Japanese");
        }
        {
            const set_global_locale global_locale(locale_zh);

            const message_catalog_type message_catalog;

            BOOST_CHECK(message_catalog.get(L"Language") == L"Language");
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

#endif

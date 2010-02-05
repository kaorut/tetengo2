/*! \file
    \brief Test of class tetengo2::messages.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

//#include <cstddef>
//#include <ios>
#include <istream>
//#include <locale>
//#include <stdexcept>
//#include <string>

//#include <boost/filesystem.hpp>
#include <boost/scope_exit.hpp>
#include <boost/test/unit_test.hpp>

#include "stub_tetengo2.encode.h"
#include "tetengo2.message_catalog_parser.h"

#include "tetengo2.messages.h"


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


    // data

#if defined(_WIN32)
    const std::locale locale_en("English");

    const std::locale locale_ja("Japanese_Japan");

    const std::locale locale_zh("Chinese");
#elif defined(__CYGWIN__)
    const std::locale locale_en("C");

    const std::locale locale_ja("C");

    const std::locale locale_zh("C");
#else
    const std::locale locale_en("en");

    const std::locale locale_ja("ja_JP");

    const std::locale locale_zh("zh");
#endif


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(messages)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

#if defined(__CYGWIN__)
        BOOST_WARN_MESSAGE(false, "g++ on Cygwin support no locale.");
#else
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
#endif
}

    BOOST_AUTO_TEST_CASE(do_open)
    {
        BOOST_TEST_PASSPOINT();

#if defined(__CYGWIN__)
        BOOST_WARN_MESSAGE(false, "g++ on Cygwin support no locale.");
#else
        {
            const set_global_locale global_locale(locale_en);
            const std::messages<char>& messages =
                std::use_facet<std::messages<char> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

            const std::messages_base::catalog catalog_id =
                messages.open("", std::locale());
            BOOST_SCOPE_EXIT((&messages)(catalog_id))
            {
                messages.close(catalog_id);
            } BOOST_SCOPE_EXIT_END

            BOOST_CHECK_GE(catalog_id, 0);

            BOOST_CHECK_THROW(
                messages.open("", std::locale()), std::runtime_error
            );
        }
        {
            const set_global_locale global_locale(locale_ja);
            const std::messages<char>& messages =
                std::use_facet<std::messages<char> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

            const std::messages_base::catalog catalog_id =
                messages.open("", std::locale());
            BOOST_SCOPE_EXIT((&messages)(catalog_id))
            {
                messages.close(catalog_id);
            } BOOST_SCOPE_EXIT_END

            BOOST_CHECK_GE(catalog_id, 0);

            BOOST_CHECK_THROW(
                messages.open("", std::locale()), std::runtime_error
            );
        }
        {
            const set_global_locale global_locale(locale_zh);
            const std::messages<char>& messages =
                std::use_facet<std::messages<char> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

            const std::messages_base::catalog catalog_id =
                messages.open("", std::locale());
            BOOST_CHECK_LT(catalog_id, 0);
        }
#endif
    }

    BOOST_AUTO_TEST_CASE(do_get)
    {
        BOOST_TEST_PASSPOINT();

#if defined(__CYGWIN__)
        BOOST_WARN_MESSAGE(false, "g++ on Cygwin support no locale.");
#else
        {
            const set_global_locale global_locale(locale_en);
            const std::messages<char>& messages =
                std::use_facet<std::messages<char> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

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
            } BOOST_SCOPE_EXIT_END

            BOOST_CHECK(
                messages.get(catalog_id, 0, 0, "Language") == "English"
            );
        }
        {
            const set_global_locale global_locale(locale_ja);
            const std::messages<char>& messages =
                std::use_facet<std::messages<char> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

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
            } BOOST_SCOPE_EXIT_END

            BOOST_CHECK(
                messages.get(catalog_id, 0, 0, "Language") == "Japanese"
            );
        }
        {
            const set_global_locale global_locale(locale_zh);
            const std::messages<char>& messages =
                std::use_facet<std::messages<char> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

            const std::messages_base::catalog catalog_id =
                messages.open("", std::locale());

            BOOST_CHECK(
                messages.get(catalog_id, 0, 0, "Language") == "Language"
            );
        }
#endif
    }

    BOOST_AUTO_TEST_CASE(do_close)
    {
        BOOST_TEST_PASSPOINT();

#if defined(__CYGWIN__)
        BOOST_WARN_MESSAGE(false, "g++ on Cygwin support no locale.");
#else
        {
            const set_global_locale global_locale(locale_en);
            const std::messages<char>& messages =
                std::use_facet<std::messages<char> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

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
            } BOOST_SCOPE_EXIT_END
        }
        {
            const set_global_locale global_locale(locale_ja);
            const std::messages<char>& messages =
                std::use_facet<std::messages<char> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

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
            } BOOST_SCOPE_EXIT_END
        }
        {
            const set_global_locale global_locale(locale_zh);
            const std::messages<char>& messages =
                std::use_facet<std::messages<char> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

            const std::messages_base::catalog catalog_id =
                messages.open("", std::locale());
            BOOST_CHECK_NO_THROW(messages.close(catalog_id));
        }
#endif
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

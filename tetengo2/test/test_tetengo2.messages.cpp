/*! \file
    \brief Test of class tetengo2::messages.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <cstddef>
#include <ios>
#include <locale>
#include <stdexcept>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/scope_exit.hpp>

#include "tetengo2.win32.encode.h"

#include "tetengo2.messages.h"

namespace
{
    // types

    typedef
        tetengo2::messages<
            std::wstring, boost::filesystem::wpath, tetengo2::win32::encode
        >
        messages_type;

#if defined(_WIN32)
    const std::locale locale_en("English");

    const std::locale locale_ja("Japanese_Japan");

    const std::locale locale_zh("Chinese");
#else
    const std::locale locale_en("en");

    const std::locale locale_ja("ja_JP");

    const std::locale locale_zh("zh");
#endif

    struct set_global_locale
    {
        const std::locale m_initial_locale;

        set_global_locale(const std::locale& locale)
        :
        m_initial_locale(
            std::locale::global(
                std::locale(
                    locale,
                    new messages_type(
                        boost::filesystem::wpath(L"messages"), locale
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

}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(messages)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_CHECKPOINT("");

        const messages_type messages(
            boost::filesystem::wpath(L"messages"), std::locale()
        );

        BOOST_CHECK_THROW(
            messages_type(boost::filesystem::wpath(L""), std::locale()),
            std::ios_base::failure
        );

        BOOST_CHECK_THROW(
            messages_type(
                boost::filesystem::wpath(L"messages") / L"English.txt",
                std::locale()
            ),
            std::ios_base::failure
        );
    }

    BOOST_AUTO_TEST_CASE(do_open)
    {
        BOOST_CHECKPOINT("");

        {
            const set_global_locale global_locale(locale_en);
            const std::messages<wchar_t>& messages =
                std::use_facet<std::messages<wchar_t> >(std::locale());
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
            const std::messages<wchar_t>& messages =
                std::use_facet<std::messages<wchar_t> >(std::locale());
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
            const std::messages<wchar_t>& messages =
                std::use_facet<std::messages<wchar_t> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

            const std::messages_base::catalog catalog_id =
                messages.open("", std::locale());
            BOOST_CHECK_LT(catalog_id, 0);
        }
    }

    BOOST_AUTO_TEST_CASE(do_get)
    {
        BOOST_CHECKPOINT("");

        {
            const set_global_locale global_locale(locale_en);
            const std::messages<wchar_t>& messages =
                std::use_facet<std::messages<wchar_t> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

            BOOST_CHECK_THROW(
                messages.get(0, 0, 0, L"Language"), std::runtime_error
            );

            BOOST_CHECK(
                messages.get(-1, 0, 0, L"Language") == L"Language"
            );

            const std::messages_base::catalog catalog_id =
                messages.open("", std::locale());
            BOOST_SCOPE_EXIT((&messages)(catalog_id))
            {
                messages.close(catalog_id);
            } BOOST_SCOPE_EXIT_END

            BOOST_CHECK(
                messages.get(catalog_id, 0, 0, L"Language") == L"English"
            );
        }
        {
            const set_global_locale global_locale(locale_ja);
            const std::messages<wchar_t>& messages =
                std::use_facet<std::messages<wchar_t> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

            BOOST_CHECK_THROW(
                messages.get(0, 0, 0, L"Language"), std::runtime_error
            );

            BOOST_CHECK(
                messages.get(-1, 0, 0, L"Language") == L"Language"
            );

            const std::messages_base::catalog catalog_id =
                messages.open("", std::locale());
            BOOST_SCOPE_EXIT((&messages)(catalog_id))
            {
                messages.close(catalog_id);
            } BOOST_SCOPE_EXIT_END

            BOOST_CHECK(
                messages.get(catalog_id, 0, 0, L"Language") == L"Japanese"
            );
        }
        {
            const set_global_locale global_locale(locale_zh);
            const std::messages<wchar_t>& messages =
                std::use_facet<std::messages<wchar_t> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

            const std::messages_base::catalog catalog_id =
                messages.open("", std::locale());

            BOOST_CHECK(
                messages.get(catalog_id, 0, 0, L"Language") == L"Language"
            );
        }
    }

    BOOST_AUTO_TEST_CASE(do_close)
    {
        BOOST_CHECKPOINT("");

        {
            const set_global_locale global_locale(locale_en);
            const std::messages<wchar_t>& messages =
                std::use_facet<std::messages<wchar_t> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

            BOOST_CHECK_THROW(messages.close(0), std::runtime_error);

            BOOST_CHECK_THROW(messages.close(-1), std::runtime_error);

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
            const std::messages<wchar_t>& messages =
                std::use_facet<std::messages<wchar_t> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

            BOOST_CHECK_THROW(messages.close(0), std::runtime_error);

            BOOST_CHECK_THROW(messages.close(-1), std::runtime_error);

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
            const std::messages<wchar_t>& messages =
                std::use_facet<std::messages<wchar_t> >(std::locale());
            BOOST_CHECK(
                dynamic_cast<const messages_type*>(&messages) != NULL
            );

            const std::messages_base::catalog catalog_id =
                messages.open("", std::locale());
            BOOST_CHECK_THROW(messages.close(catalog_id), std::runtime_error);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

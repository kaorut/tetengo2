/*! \file
    \brief Test of class tetengo2::text::encoding::locale.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <locale>
#include <stdexcept>
#include <string>

#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2/text.h>
#include <tetengo2/text/encoding/locale.h>

#include "test_tetengo2.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::type_list::detail_for_test;

    using encoding_details_type = detail_type_list_type::encoding_type;

    using multibyte_encoding_type = tetengo2::text::encoding::locale<std::string>;

    using wide_encoding_type = tetengo2::text::encoding::locale<std::wstring>;


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
#else
    const std::locale locale_en = make_locale("en_US");

    const std::locale locale_ja = make_locale("ja_JP.UTF-8");
#endif


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(text)
BOOST_AUTO_TEST_SUITE(encoding)
BOOST_AUTO_TEST_SUITE(locale)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const multibyte_encoding_type encoding{ encoding_details_type::instance() };
        }
        {
            const wide_encoding_type encoding{ encoding_details_type::instance() };
        }
        {
            const multibyte_encoding_type encoding{ std::locale::classic(), encoding_details_type::instance() };
        }
        {
            const wide_encoding_type encoding{ std::locale::classic(), encoding_details_type::instance() };
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        if (locale_supported())
        {
            {
                const multibyte_encoding_type encoding1{ locale_en, encoding_details_type::instance() };
                const multibyte_encoding_type encoding2{ locale_en, encoding_details_type::instance() };

                BOOST_CHECK(encoding1 == encoding2);
            }
            {
                const multibyte_encoding_type encoding1{ locale_en, encoding_details_type::instance() };
                const multibyte_encoding_type encoding2{ locale_ja, encoding_details_type::instance() };

                BOOST_CHECK(encoding1 != encoding2);
            }
            {
                const wide_encoding_type encoding1{ locale_en, encoding_details_type::instance() };
                const wide_encoding_type encoding2{ locale_en, encoding_details_type::instance() };

                BOOST_CHECK(encoding1 == encoding2);
            }
            {
                const wide_encoding_type encoding1{ locale_en, encoding_details_type::instance() };
                const wide_encoding_type encoding2{ locale_ja, encoding_details_type::instance() };

                BOOST_CHECK(encoding1 != encoding2);
            }
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }

    BOOST_AUTO_TEST_CASE(locale_based_on)
    {
        BOOST_TEST_PASSPOINT();

        if (locale_supported())
        {
            {
                {
                    const multibyte_encoding_type encoding{ locale_en, encoding_details_type::instance() };

                    BOOST_CHECK(encoding.locale_based_on() == locale_en);
                }
                {
                    const multibyte_encoding_type encoding{ locale_ja, encoding_details_type::instance() };

                    BOOST_CHECK(encoding.locale_based_on() == locale_ja);
                }
            }
            {
                {
                    const wide_encoding_type encoding{ locale_en, encoding_details_type::instance() };

                    BOOST_CHECK(encoding.locale_based_on() == locale_en);
                }
                {
                    const wide_encoding_type encoding{ locale_ja, encoding_details_type::instance() };

                    BOOST_CHECK(encoding.locale_based_on() == locale_ja);
                }
            }
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }

    BOOST_AUTO_TEST_CASE(from_pivot)
    {
        BOOST_TEST_PASSPOINT();

        {
            const multibyte_encoding_type::pivot_type pivot{ TETENGO2_TEXT("Tetengo2") };
            const multibyte_encoding_type::string_type string{ TETENGO2_TEXT("Tetengo2") };

            const multibyte_encoding_type encoding{ std::locale::classic(), encoding_details_type::instance() };

            BOOST_CHECK(encoding.from_pivot(pivot) == string);
        }
        {
            const multibyte_encoding_type::pivot_type pivot{};
            const multibyte_encoding_type::string_type string{};

            const multibyte_encoding_type encoding{ std::locale::classic(), encoding_details_type::instance() };

            BOOST_CHECK(encoding.from_pivot(pivot) == string);
        }
        {
            const wide_encoding_type::pivot_type pivot{ TETENGO2_TEXT("Tetengo2") };
            const wide_encoding_type::string_type string{ TETENGO2_TEXT("Tetengo2") };

            const wide_encoding_type encoding{ std::locale::classic(), encoding_details_type::instance() };

            BOOST_CHECK(encoding.from_pivot(pivot) == string);
        }
        {
            const wide_encoding_type::pivot_type pivot{};
            const wide_encoding_type::string_type string{};

            const wide_encoding_type encoding{ std::locale::classic(), encoding_details_type::instance() };

            BOOST_CHECK(encoding.from_pivot(pivot) == string);
        }
    }

    BOOST_AUTO_TEST_CASE(to_pivot)
    {
        BOOST_TEST_PASSPOINT();

        {
            const multibyte_encoding_type::pivot_type pivot{ TETENGO2_TEXT("Tetengo2") };
            const multibyte_encoding_type::string_type string{ TETENGO2_TEXT("Tetengo2") };

            const multibyte_encoding_type encoding{ std::locale::classic(), encoding_details_type::instance() };

            BOOST_CHECK(encoding.to_pivot(string) == pivot);
        }
        {
            const multibyte_encoding_type::pivot_type pivot{};
            const multibyte_encoding_type::string_type string{};

            const multibyte_encoding_type encoding{ std::locale::classic(), encoding_details_type::instance() };

            BOOST_CHECK(encoding.to_pivot(string) == pivot);
        }
        {
            const wide_encoding_type::pivot_type pivot{ TETENGO2_TEXT("Tetengo2") };
            const wide_encoding_type::string_type string{ TETENGO2_TEXT("Tetengo2") };

            const wide_encoding_type encoding{ std::locale::classic(), encoding_details_type::instance() };

            BOOST_CHECK(encoding.to_pivot(string) == pivot);
        }
        {
            const wide_encoding_type::pivot_type pivot{};
            const wide_encoding_type::string_type string{};

            const wide_encoding_type encoding{ std::locale::classic(), encoding_details_type::instance() };

            BOOST_CHECK(encoding.to_pivot(string) == pivot);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

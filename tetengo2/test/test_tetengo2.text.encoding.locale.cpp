/*! \file
    \brief Test of class tetengo2::encoding::locale.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <locale>
//#include <stdexcept>
//#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.text.h"

#include "tetengo2.text.encoding.locale.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::encoding::locale<std::string, encoding_details_type>
        multibyte_encoding_type;

    typedef
        tetengo2::encoding::locale<std::wstring, encoding_details_type>
        wide_encoding_type;


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
#else
    const std::locale locale_en = make_locale("en_US");

    const std::locale locale_ja = make_locale("ja_JP.UTF-8");
#endif


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(encoding)
BOOST_AUTO_TEST_SUITE(locale)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const multibyte_encoding_type encoding;
        }
        {
            const wide_encoding_type encoding;
        }
        {
            const multibyte_encoding_type encoding(std::locale::classic());
        }
        {
            const wide_encoding_type encoding(std::locale::classic());
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        if (locale_supported())
        {
            {
                const multibyte_encoding_type encoding1(locale_en);
                const multibyte_encoding_type encoding2(locale_en);

                BOOST_CHECK(encoding1 == encoding2);
            }
            {
                const multibyte_encoding_type encoding1(locale_en);
                const multibyte_encoding_type encoding2(locale_ja);

                BOOST_CHECK(encoding1 != encoding2);
            }
            {
                const wide_encoding_type encoding1(locale_en);
                const wide_encoding_type encoding2(locale_en);

                BOOST_CHECK(encoding1 == encoding2);
            }
            {
                const wide_encoding_type encoding1(locale_en);
                const wide_encoding_type encoding2(locale_ja);

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
                    const multibyte_encoding_type encoding(locale_en);

                    BOOST_CHECK(encoding.locale_based_on() == locale_en);
                }
                {
                    const multibyte_encoding_type encoding(locale_ja);

                    BOOST_CHECK(encoding.locale_based_on() == locale_ja);
                }
            }
            {
                {
                    const wide_encoding_type encoding(locale_en);

                    BOOST_CHECK(encoding.locale_based_on() == locale_en);
                }
                {
                    const wide_encoding_type encoding(locale_ja);

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
            const multibyte_encoding_type::pivot_type pivot(
                TETENGO2_TEXT("Tetengo2")
            );
            const multibyte_encoding_type::string_type string(
                TETENGO2_TEXT("Tetengo2")
            );

            const multibyte_encoding_type encoding(std::locale::classic());

            BOOST_CHECK(encoding.from_pivot(pivot) == string);
        }
        {
            const wide_encoding_type::pivot_type pivot(
                TETENGO2_TEXT("Tetengo2")
            );
            const wide_encoding_type::string_type string(
                TETENGO2_TEXT("Tetengo2")
            );

            const wide_encoding_type encoding(std::locale::classic());

            BOOST_CHECK(encoding.from_pivot(pivot) == string);
        }
    }

    BOOST_AUTO_TEST_CASE(to_pivot)
    {
        BOOST_TEST_PASSPOINT();

        {
            const multibyte_encoding_type::pivot_type pivot(
                TETENGO2_TEXT("Tetengo2")
            );
            const multibyte_encoding_type::string_type string(
                TETENGO2_TEXT("Tetengo2")
            );

            const multibyte_encoding_type encoding(std::locale::classic());

            BOOST_CHECK(encoding.to_pivot(string) == pivot);
        }
        {
            const wide_encoding_type::pivot_type pivot(
                TETENGO2_TEXT("Tetengo2")
            );
            const wide_encoding_type::string_type string(
                TETENGO2_TEXT("Tetengo2")
            );

            const wide_encoding_type encoding(std::locale::classic());

            BOOST_CHECK(encoding.to_pivot(string) == pivot);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
/*! \file
    \brief Test of class tetengo2::encoding::locale.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <locale>
#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.encoding.locale.h"


namespace
{
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
        const tetengo2::encoding::locale<std::string> encoding(
            std::locale::classic()
        );
    }

    BOOST_AUTO_TEST_CASE(swap)
    {
        if (locale_supported())
        {
            tetengo2::encoding::locale<std::string> encoding1(
                locale_en
            );
            tetengo2::encoding::locale<std::string> encoding2(
                locale_ja
            );

            encoding1.swap(encoding2);

            BOOST_CHECK(encoding1.locale_based_on() == locale_ja);
            BOOST_CHECK(encoding2.locale_based_on() == locale_en);
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        if (locale_supported())
        {
            tetengo2::encoding::locale<std::string> encoding1(
                locale_en
            );
            const tetengo2::encoding::locale<std::string> encoding2(
                locale_ja
            );

            encoding1 = encoding2;

            BOOST_CHECK(encoding1.locale_based_on() == locale_ja);
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }

    BOOST_AUTO_TEST_CASE(locale_based_on)
    {
        if (locale_supported())
        {
            {
                const tetengo2::encoding::locale<std::string> encoding(
                    locale_en
                );

                BOOST_CHECK(encoding.locale_based_on() == locale_en);
            }
            {
                const tetengo2::encoding::locale<std::string> encoding(
                    locale_ja
                );

                BOOST_CHECK(encoding.locale_based_on() == locale_ja);
            }
        }
        else
        {
            BOOST_WARN_MESSAGE(false, "Locale not supported.");
        }
    }

    BOOST_AUTO_TEST_CASE(from_pivot)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(to_pivot)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

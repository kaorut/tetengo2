/*! \file
    \brief Test of class tetengo2::text.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <sstream>
#include <string>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/text.h>


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(text_value_holder)
        // test cases

        BOOST_AUTO_TEST_CASE(construction)
        {
            BOOST_TEST_PASSPOINT();

            TETENGO2_TEXT("hoge");
        }

        BOOST_AUTO_TEST_CASE(operator_multibyte_type)
        {
            BOOST_TEST_PASSPOINT();

            {
                const std::string string{ TETENGO2_TEXT("hoge") };
                BOOST_CHECK(string == "hoge");
            }
            {
                const char character{ TETENGO2_TEXT('H') };
                BOOST_TEST(character == 'H');
            }
        }

        BOOST_AUTO_TEST_CASE(operator_wide_type)
        {
            BOOST_TEST_PASSPOINT();

            {
                const std::wstring string{ TETENGO2_TEXT("hoge") };
                BOOST_CHECK(string == L"hoge");
            }
            {
                const wchar_t character{ TETENGO2_TEXT('H') };
                BOOST_TEST(character == L'H');
            }
        }


    BOOST_AUTO_TEST_SUITE_END()
    // test cases

    BOOST_AUTO_TEST_CASE(make_text_value_holder)
    {
        BOOST_TEST_PASSPOINT();

        {
            tetengo2::make_text_value_holder("hoge", L"fuga");
        }
        {
            tetengo2::make_text_value_holder('H', L'F');
        }
    }


BOOST_AUTO_TEST_SUITE_END()

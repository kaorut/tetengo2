/*! \file
    \brief Test of class tetengo2::gui::drawing::font.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <sstream>
#include <string>

#include <boost/operators.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/text.h>


namespace {
    // types

    using font_type = tetengo2::gui::drawing::font;

    using string_type = font_type::string_type;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(drawing)
            BOOST_AUTO_TEST_SUITE(font)
                // test cases

                BOOST_AUTO_TEST_CASE(dialog_font)
                {
                    BOOST_TEST_PASSPOINT();

                    const auto& font = font_type::dialog_font();

                    BOOST_CHECK(
                        font == font_type(string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, false, false));
                }

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_type font{ string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, false, false };
                }

                BOOST_AUTO_TEST_CASE(operator_equal)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const font_type font1{
                            string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, false, false
                        };
                        const font_type font2{
                            string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, false, false
                        };

                        BOOST_CHECK(font1 == font2);
                    }
                    {
                        const font_type font1{
                            string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, false, false
                        };
                        const font_type font2{
                            string_type{ TETENGO2_TEXT("TetengoFont2") }, 12, false, false, false, false
                        };

                        BOOST_CHECK(font1 != font2);
                    }
                    {
                        const font_type font1{
                            string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, false, false
                        };
                        const font_type font2{
                            string_type{ TETENGO2_TEXT("TetengoFont") }, 42, false, false, false, false
                        };

                        BOOST_CHECK(font1 != font2);
                    }
                    {
                        const font_type font1{
                            string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, false, false
                        };
                        const font_type font2{
                            string_type{ TETENGO2_TEXT("TetengoFont") }, 12, true, false, false, false
                        };

                        BOOST_CHECK(font1 != font2);
                    }
                    {
                        const font_type font1{
                            string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, false, false
                        };
                        const font_type font2{
                            string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, true, false, false
                        };

                        BOOST_CHECK(font1 != font2);
                    }
                    {
                        const font_type font1{
                            string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, false, false
                        };
                        const font_type font2{
                            string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, true, false
                        };

                        BOOST_CHECK(font1 != font2);
                    }
                    {
                        const font_type font1{
                            string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, false, false
                        };
                        const font_type font2{
                            string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, false, true
                        };

                        BOOST_CHECK(font1 != font2);
                    }
                }

                BOOST_AUTO_TEST_CASE(operator_assign)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const font_type font1{
                            string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, false, false
                        };
                        font_type font2{ string_type{ TETENGO2_TEXT("TetengoFont2") }, 12, false, false, false, false };

                        font2 = font1;

                        BOOST_CHECK(font1 == font2);
                    }
                    {
                        font_type font1{ string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, false, false };
                        font_type font2{ string_type{ TETENGO2_TEXT("TetengoFont2") }, 12, false, false, false, false };

                        font2 = std::move(font1);

                        BOOST_CHECK(font2.family() == string_type{ TETENGO2_TEXT("TetengoFont") });
                    }
                }

                BOOST_AUTO_TEST_CASE(family)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_type font{ string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, true, false, true };

                    BOOST_CHECK(font.family() == string_type{ TETENGO2_TEXT("TetengoFont") });
                }

                BOOST_AUTO_TEST_CASE(size)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_type font{ string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, true, false, true };

                    BOOST_TEST(font.size() == 12U);
                }

                BOOST_AUTO_TEST_CASE(bold)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_type font{ string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, true, false, true };

                    BOOST_TEST(!font.bold());
                }

                BOOST_AUTO_TEST_CASE(italic)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_type font{ string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, true, false, true };

                    BOOST_TEST(font.italic());
                }

                BOOST_AUTO_TEST_CASE(underline)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_type font{ string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, true, false, true };

                    BOOST_TEST(!font.underline());
                }

                BOOST_AUTO_TEST_CASE(strikeout)
                {
                    BOOST_TEST_PASSPOINT();

                    const font_type font{ string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, true, false, true };

                    BOOST_TEST(font.strikeout());
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

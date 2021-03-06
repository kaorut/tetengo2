/*! \file
    \brief Test of class tetengo2::text::encoding::ascii.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <sstream>
#include <stdexcept>
#include <string>

#include <boost/predef.h>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/stdalt.h>
#include <tetengo2/text/encoding/ascii.h>
#include <tetengo2/text/encoding/encoding.h>


namespace {
    // types

    using encoding_type = tetengo2::text::encoding::ascii;

    using pivot_type = encoding_type::pivot_type;

#if BOOST_OS_WINDOWS
    using pivot_string_type = std::wstring;
#elif BOOST_OS_LINUX
    using pivot_string_type = std::string;
#else
#error Unsupported platform.
#endif


    // variables

    // "\n 0Aa~[DEL]"
    const unsigned char pivot_ascii[]{ 0x0A, 0x20, 0x30, 0x41, 0x61, 0x7E, 0x7F, 0x00 };

    // "\n 0Aa~[DEL]"
    const unsigned char ascii_ascii[]{ 0x0A, 0x20, 0x30, 0x41, 0x61, 0x7E, 0x7F, 0x00 };

    // Empty characters
    const unsigned char pivot_empty[]{ 0x00 };

    // Empty characters
    const unsigned char ascii_empty[]{ 0x00 };

    // Non-ASCII characters
    const unsigned char pivot_nonascii[]{ 0x80, 0xFF, 0x00 };

    // Non-ASCII characters
    const unsigned char ascii_nonascii[]{ 0x3F, 0x3F, 0x00 };

    // Non-ASCII characters
    const unsigned char nonascii[]{ 0x80, 0xFF, 0x00 };
}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(text)
        BOOST_AUTO_TEST_SUITE(encoding)
            BOOST_AUTO_TEST_SUITE(ascii)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    const encoding_type encoding{};
                }

                BOOST_AUTO_TEST_CASE(name)
                {
                    BOOST_TEST_PASSPOINT();

                    const encoding_type encoding{};

                    BOOST_CHECK(encoding.name() == "ASCII");
                }

                BOOST_AUTO_TEST_CASE(operator_equal)
                {
                    BOOST_TEST_PASSPOINT();

                    const encoding_type encoding1{};
                    const encoding_type encoding2{};

                    BOOST_CHECK(encoding1 == encoding2);
                }

                BOOST_AUTO_TEST_CASE(from_pivot)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const pivot_type  pivot{ pivot_string_type{ pivot_ascii,
                                                                   pivot_ascii + sizeof(pivot_ascii) - 1 } };
                        const std::string string{ ascii_ascii, ascii_ascii + sizeof(ascii_ascii) - 1 };

                        const encoding_type encoding{};
                        const auto          result = encoding.from_pivot(pivot);

                        BOOST_CHECK(result == string);
                    }
                    {
                        const pivot_type  pivot{ pivot_string_type{ pivot_empty,
                                                                   pivot_empty + sizeof(pivot_empty) - 1 } };
                        const std::string string{ ascii_empty, ascii_empty + sizeof(ascii_empty) - 1 };

                        const encoding_type encoding{};
                        const auto          result = encoding.from_pivot(pivot);

                        BOOST_CHECK(result == string);
                    }
                    {
                        const pivot_type  pivot{ pivot_string_type{ pivot_nonascii,
                                                                   pivot_nonascii + sizeof(pivot_nonascii) - 1 } };
                        const std::string string{ ascii_nonascii, ascii_nonascii + sizeof(ascii_nonascii) - 1 };

                        const encoding_type encoding{};
                        const auto          result = encoding.from_pivot(pivot);

                        BOOST_CHECK(result == string);
                    }
                }

                BOOST_AUTO_TEST_CASE(to_pivot)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const pivot_type  pivot{ pivot_string_type{ pivot_ascii,
                                                                   pivot_ascii + sizeof(pivot_ascii) - 1 } };
                        const std::string string{ ascii_ascii, ascii_ascii + sizeof(ascii_ascii) - 1 };

                        const encoding_type encoding{};
                        const auto          result = encoding.to_pivot(string);

                        BOOST_CHECK(result == pivot);
                    }
                    {
                        const pivot_type  pivot{ pivot_string_type{ pivot_empty,
                                                                   pivot_empty + sizeof(pivot_empty) - 1 } };
                        const std::string string{ ascii_empty, ascii_empty + sizeof(ascii_empty) - 1 };

                        const encoding_type encoding{};
                        const auto          result = encoding.to_pivot(string);

                        BOOST_CHECK(result == pivot);
                    }
                    {
                        const std::string string{ nonascii, nonascii + sizeof(nonascii) - 1 };

                        const encoding_type encoding{};
                        BOOST_CHECK_THROW(encoding.to_pivot(string), std::invalid_argument);
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

/*! \file
    \brief Test of class tetengo2::message_catalog_parser.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.win32.encode.h"

#include "tetengo2.message_catalog_parser.h"


namespace
{
    // types

    typedef
        tetengo2::message_catalog_parser<
            std::istream, std::wstring, tetengo2::win32::encode
        >
        message_catalog_parser_type;

    typedef message_catalog_parser_type::entry_type entry_type;


    // data

    const std::string catalog0(
        ""
    );

    const std::string catalog1(
        "Key1=Value1\n"
    );

    const std::string catalog2(
        "Key\\=1=Value1\n"
        "'Key=2'=Value2\n"
        "Key3='Value3\n"
        "Key4=Value\\\"4\\\"\n"
        "Key5'='Value5\n"
    );


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(message_catalog_parser)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_CHECKPOINT("");

        {
            std::istringstream input_stream(catalog0);
            const message_catalog_parser_type parser(input_stream);
        }
        {
            std::istringstream input_stream(catalog1);
            const message_catalog_parser_type parser(input_stream);
        }
    }

    BOOST_AUTO_TEST_CASE(has_next)
    {
        BOOST_CHECKPOINT("");

        {
            std::istringstream input_stream(catalog0);
            const message_catalog_parser_type parser(input_stream);

            BOOST_CHECK(!parser.has_next());
        }
        {
            std::istringstream input_stream(catalog1);
            message_catalog_parser_type parser(input_stream);

            BOOST_CHECK(parser.has_next());

            parser.next();

            BOOST_CHECK(!parser.has_next());
        }
    }

    BOOST_AUTO_TEST_CASE(next)
    {
        BOOST_CHECKPOINT("");

        {
            std::istringstream input_stream(catalog1);
            message_catalog_parser_type parser(input_stream);

            const entry_type entry = parser.next();
            BOOST_CHECK(entry.first == L"Key1");
            BOOST_CHECK(entry.second == L"Value1");

            BOOST_CHECK_THROW(parser.next(), std::runtime_error);
        }
        {
            std::istringstream input_stream(catalog2);
            message_catalog_parser_type parser(input_stream);

            const entry_type entry1 = parser.next();
            BOOST_CHECK(entry1.first == L"Key=1");
            BOOST_CHECK(entry1.second == L"Value1");

            const entry_type entry2 = parser.next();
            BOOST_CHECK(entry2.first == L"Key=2");
            BOOST_CHECK(entry2.second == L"Value2");

            const entry_type entry3 = parser.next();
            BOOST_CHECK(entry3.first == L"Key3");
            BOOST_CHECK(entry3.second == L"Value3");

            const entry_type entry4 = parser.next();
            BOOST_CHECK(entry4.first == L"Key4");
            BOOST_CHECK(entry4.second == L"Value\"4\"");

            BOOST_CHECK_THROW(parser.next(), std::runtime_error);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

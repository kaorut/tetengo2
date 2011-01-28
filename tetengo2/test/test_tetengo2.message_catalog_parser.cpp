/*! \file
    \brief Test of class tetengo2::message_catalog_parser.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <istream>
#include <sstream>
//#include <stdexcept>
//#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.encoder.h"
#include "tetengo2.encoding.locale.h"

#include "tetengo2.message_catalog_parser.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::encoding::locale<std::string, encoding_details_type>
        internal_encoding_type;

    typedef
        tetengo2::encoding::locale<std::string, encoding_details_type>
        message_catalog_encoding_type;

    typedef
        tetengo2::encoder<
            internal_encoding_type, message_catalog_encoding_type
        >
        message_catalog_encoder_type;

    typedef
        tetengo2::message_catalog_parser<
            std::istream, std::string, message_catalog_encoder_type
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
        "#Key6=Value6\n"
        "Key7=#Value7\n"
        "Key\\#8=Value\\#8\n"
        "Key\\t9=Value\\n9\n"
        "Key10=\\\n"
        "Value\\\n"
        "10\n"
    );


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(message_catalog_parser)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

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
        BOOST_TEST_PASSPOINT();

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
        BOOST_TEST_PASSPOINT();

        {
            std::istringstream input_stream(catalog1);
            message_catalog_parser_type parser(input_stream);

            const entry_type entry = parser.next();
            BOOST_CHECK(entry.first == "Key1");
            BOOST_CHECK(entry.second == "Value1");

            BOOST_CHECK_THROW(parser.next(), std::runtime_error);
        }
        {
            std::istringstream input_stream(catalog2);
            message_catalog_parser_type parser(input_stream);

            const entry_type entry1 = parser.next();
            BOOST_CHECK(entry1.first == "Key=1");
            BOOST_CHECK(entry1.second == "Value1");

            const entry_type entry2 = parser.next();
            BOOST_CHECK(entry2.first == "Key=2");
            BOOST_CHECK(entry2.second == "Value2");

            const entry_type entry3 = parser.next();
            BOOST_CHECK(entry3.first == "Key3");
            BOOST_CHECK(entry3.second == "Value3");

            const entry_type entry4 = parser.next();
            BOOST_CHECK(entry4.first == "Key4");
            BOOST_CHECK(entry4.second == "Value\"4\"");

            const entry_type entry7 = parser.next();
            BOOST_CHECK(entry7.first == "Key7");
            BOOST_CHECK(entry7.second == "");

            const entry_type entry8 = parser.next();
            BOOST_CHECK(entry8.first == "Key#8");
            BOOST_CHECK(entry8.second == "Value#8");

            const entry_type entry9 = parser.next();
            BOOST_CHECK(entry9.first == "Key\t9");
            BOOST_CHECK(entry9.second == "Value\n9");

            const entry_type entry10 = parser.next();
            BOOST_CHECK(entry10.first == "Key10");
            BOOST_CHECK(entry10.second == "Value10");

            BOOST_CHECK_THROW(parser.next(), std::runtime_error);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

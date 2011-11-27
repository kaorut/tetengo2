/*! \file
    \brief Test of class tetengo2::message::message_catalog_parser_j.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <istream>
//#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"

#include "tetengo2.message.message_catalog_parser_j.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::text::encoding::locale<std::string, encoding_details_type>
        internal_encoding_type;

    typedef
        tetengo2::text::encoding::locale<std::string, encoding_details_type>
        message_catalog_encoding_type;

    typedef
        tetengo2::text::encoder<
            internal_encoding_type, message_catalog_encoding_type
        >
        message_catalog_encoder_type;

    typedef
        tetengo2::message::message_catalog_parser_j<
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
        " 'Key11' = Value11 \n"
        "\t \tKey12 \t =\t \t\"Value12\" \t "
    );


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(message_catalog_parser_j)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(has_next)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(next)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

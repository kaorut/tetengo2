/*! \file
    \brief Test of class tetengo2::message_catalog_parser.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.win32.encode.h"

#include "tetengo2.message_catalog_parser.h"


namespace
{
    // types

    typedef
        tetengo2::message_catalog_parser<
            std::wstring, tetengo2::win32::encode
        >
        message_catalog_parser_type;


    // data

    const std::string catalog0(
        ""
    );

    const std::string catalog1(
        "Key1=Value1\n"
    );


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(message_catalog_parser)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_CHECKPOINT("");

        {
            const message_catalog_parser_type parser(
                catalog0.begin(), catalog0.end()
            );
        }
        {
            const message_catalog_parser_type parser(
                catalog1.begin(), catalog1.end()
            );
        }
    }

    BOOST_AUTO_TEST_CASE(has_next)
    {
        BOOST_CHECKPOINT("");

        {
            const message_catalog_parser_type parser(
                catalog0.begin(), catalog0.end()
            );

            BOOST_CHECK(!parser.has_next());
        }
        {
            message_catalog_parser_type parser(
                catalog1.begin(), catalog1.end()
            );

            BOOST_CHECK(parser.has_next());

            parser.next();

            BOOST_CHECK(!parser.has_next());
        }
    }

    BOOST_AUTO_TEST_CASE(next)
    {
        BOOST_CHECKPOINT("");

    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

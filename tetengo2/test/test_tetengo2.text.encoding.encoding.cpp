/*! \file
    \brief Test of class tetengo2::text::encoding::encoding.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.encoding.h"

#include "tetengo2.text.encoding.encoding.h"


namespace
{
    // types

    typedef tetengo2::text::encoding::encoding<tetengo2::detail::stub::encoding> encoding_type;

    struct concrete_encoding : public encoding_type
    {
        concrete_encoding()
        {}

    };
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(text)
BOOST_AUTO_TEST_SUITE(encoding)
BOOST_AUTO_TEST_SUITE(encoding)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_encoding encoding;
    } 


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

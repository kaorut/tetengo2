/*! \file
    \brief Test of class tetengo2::text::encoding::cp932.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.text.h"
#include "tetengo2.text.encoding.cp932.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef tetengo2::text::encoding::cp932<encoding_details_type> encoding_type;


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(text)
BOOST_AUTO_TEST_SUITE(encoding)
BOOST_AUTO_TEST_SUITE(cp932)
    // test cases

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        const encoding_type encoding1;
        const encoding_type encoding2;

        BOOST_CHECK(encoding1 == encoding2);
    }

    BOOST_AUTO_TEST_CASE(from_pivot)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::wstring pivot(TETENGO2_TEXT("Tetengo2"));
            const std::string string(TETENGO2_TEXT("Tetengo2"));

            const encoding_type encoding;
            const auto result = encoding.from_pivot(pivot);

            BOOST_CHECK(result == string);
        }
    }

    BOOST_AUTO_TEST_CASE(to_pivot)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::wstring pivot(TETENGO2_TEXT("Tetengo2"));
            const std::string string(TETENGO2_TEXT("Tetengo2"));

            const encoding_type encoding;
            const auto result = encoding.to_pivot(string);

            BOOST_CHECK(result == pivot);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

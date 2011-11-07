/*! \file
    \brief Test of class encoding_type.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.text.h"
#include "tetengo2.text.encoding.utf8.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef tetengo2::encoding::utf8<encoding_details_type> encoding_type;


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(encoding)
BOOST_AUTO_TEST_SUITE(utf8)
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
            const std::string result = encoding.from_pivot(pivot);

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
            const std::wstring result = encoding.to_pivot(string);

            BOOST_CHECK(result == pivot);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

/*! \file
    \brief Test of class tetengo2::text::encoding::encoding.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2/detail/stub/encoding.h>


namespace
{
    // types

    using encoding_details_type =
        boost::mpl::at<test_tetengo2::detail_type_list, test_tetengo2::type::detail::encoding>::type;

    using encoding_type = tetengo2::text::encoding::encoding<encoding_details_type>;

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

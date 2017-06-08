/*! \file
    \brief Test of class tetengo2::text::encoding::encoding.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <string>

#include <boost/core/ignore_unused.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/text/encoding/encoding.h>


namespace
{
    // types

    using encoding_type = tetengo2::text::encoding::encoding<std::string>;

    struct concrete_encoding : public encoding_type
    {
        void call_details()
        const
        {
            details();
        }

    private:
        virtual string_type from_pivot_impl(const pivot_type& pivot)
        const
        {
            boost::ignore_unused(pivot);
            return string_type{};
        }

        virtual pivot_type to_pivot_impl(const string_type& string)
        const
        {
            boost::ignore_unused(string);
            return pivot_type{};
        }

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

        const concrete_encoding encoding{};
    } 

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_encoding encoding{};

        encoding.call_details();
    } 

    BOOST_AUTO_TEST_CASE(from_pivot)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_encoding encoding{};

        encoding.from_pivot(encoding_type::pivot_type{});
    } 

    BOOST_AUTO_TEST_CASE(to_pivot)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_encoding encoding{};

        encoding.to_pivot(encoding_type::string_type{});
    } 


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

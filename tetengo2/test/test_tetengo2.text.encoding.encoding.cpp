/*! \file
    \brief Test of class tetengo2::text::encoding::encoding.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <sstream>
#include <string>

#include <boost/core/ignore_unused.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/text/encoding/encoding.h>


namespace
{
    // types

    using encoding_type = tetengo2::text::encoding::encoding<std::string>;

    class concrete_encoding : public encoding_type
    {
    public:
        void call_details()
        const
        {
            details();
        }

    private:
        virtual const std::string& name_impl()
        const
        {
            static const std::string singleton{ "test_concrete" };
            return singleton;
        }

        virtual string_type from_pivot_impl(pivot_type pivot)
        const
        {
            boost::ignore_unused(pivot);
            return string_type{};
        }

        virtual pivot_type to_pivot_impl(string_type string)
        const
        {
            boost::ignore_unused(string);
            return pivot_type{};
        }

    };

    class another_concrete_encoding : public encoding_type
    {
    private:
        virtual const std::string& name_impl()
        const
        {
            static const std::string singleton{ "test_another" };
            return singleton;
        }

        virtual string_type from_pivot_impl(pivot_type pivot)
        const
        {
            boost::ignore_unused(pivot);
            return string_type{};
        }

        virtual pivot_type to_pivot_impl(string_type string)
        const
        {
            boost::ignore_unused(string);
            return pivot_type{};
        }

    };

    class wide_concrete_encoding : public tetengo2::text::encoding::encoding<std::wstring>
    {
    private:
        virtual const std::string& name_impl()
        const
        {
            static const std::string singleton{ "test_wide" };
            return singleton;
        }

        virtual string_type from_pivot_impl(pivot_type pivot)
        const
        {
            boost::ignore_unused(pivot);
            return string_type{};
        }

        virtual pivot_type to_pivot_impl(string_type string)
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

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_encoding encoding{};

        encoding.name();
    } 

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_encoding encoding1{};
            const concrete_encoding encoding2{};

            BOOST_CHECK(encoding1 == encoding2);
        }
        {
            const concrete_encoding encoding1{};
            const another_concrete_encoding encoding2{};

            BOOST_CHECK(encoding1 != encoding2);
        }
        {
            const concrete_encoding encoding1{};
            const wide_concrete_encoding encoding2{};

            BOOST_CHECK(encoding1 != encoding2);
        }
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

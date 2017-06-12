/*! \file
    \brief Test of class tetengo2::text::encoding::polymorphic.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>
#include <string>

#include <boost/core/ignore_unused.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/text/encoding/encoding.h>
#include <tetengo2/text/encoding/polymorphic.h>


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

    using polymorphic_encoding_type = tetengo2::text::encoding::polymorphic<std::string>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(text)
BOOST_AUTO_TEST_SUITE(encoding)
BOOST_AUTO_TEST_SUITE(polymorphic)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const polymorphic_encoding_type encoding{ std::make_unique<concrete_encoding>() };
    } 

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        const polymorphic_encoding_type encoding{ std::make_unique<concrete_encoding>() };

        BOOST_CHECK(encoding.name() == concrete_encoding{}.name());
    } 

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const polymorphic_encoding_type encoding1{ std::make_unique<concrete_encoding>() };
            const polymorphic_encoding_type encoding2{ std::make_unique<concrete_encoding>() };

            BOOST_CHECK(encoding1 == encoding2);
        }
        {
            const polymorphic_encoding_type encoding1{ std::make_unique<concrete_encoding>() };
            const concrete_encoding encoding2{};

            BOOST_CHECK(encoding1 == encoding2);
        }
        {
            const polymorphic_encoding_type encoding1{ std::make_unique<concrete_encoding>() };
            const polymorphic_encoding_type encoding2{ std::make_unique<another_concrete_encoding>() };

            BOOST_CHECK(encoding1 != encoding2);
        }
        {
            const polymorphic_encoding_type encoding1{ std::make_unique<concrete_encoding>() };
            const another_concrete_encoding encoding2{};

            BOOST_CHECK(encoding1 != encoding2);
        }
    }

    BOOST_AUTO_TEST_CASE(from_pivot)
    {
        BOOST_TEST_PASSPOINT();

        const polymorphic_encoding_type encoding{ std::make_unique<concrete_encoding>() };

        encoding.from_pivot(encoding_type::pivot_type{});
    } 

    BOOST_AUTO_TEST_CASE(to_pivot)
    {
        BOOST_TEST_PASSPOINT();

        const polymorphic_encoding_type encoding{ std::make_unique<concrete_encoding>() };

        encoding.to_pivot(encoding_type::string_type{});
    } 


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

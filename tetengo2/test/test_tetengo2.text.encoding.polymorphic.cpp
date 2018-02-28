/*! \file
    \brief Test of class tetengo2::text::encoding::polymorphic.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <boost/core/ignore_unused.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/stdalt.h>
#include <tetengo2/text/encoding/encoding.h>
#include <tetengo2/text/encoding/polymorphic.h>


namespace {
// types

using encoding_type = tetengo2::text::encoding::encoding<std::string>;

class concrete_encoding : public encoding_type
{
public:
    concrete_encoding() : m_name("test_concrete") {}

    concrete_encoding(std::string name) : m_name(std::move(name)) {}

    void call_details() const
    {
        details();
    }

private:
    std::string m_name;

    virtual const std::string& name_impl() const
    {
        return m_name;
    }

    virtual string_type from_pivot_impl(pivot_type pivot) const
    {
        boost::ignore_unused(pivot);
        return string_type{};
    }

    virtual pivot_type to_pivot_impl(string_type string) const
    {
        boost::ignore_unused(string);
        return pivot_type{};
    }
};

class another_concrete_encoding : public encoding_type
{
private:
    virtual const std::string& name_impl() const
    {
        static const std::string singleton{ "test_another" };
        return singleton;
    }

    virtual string_type from_pivot_impl(pivot_type pivot) const
    {
        boost::ignore_unused(pivot);
        return string_type{};
    }

    virtual pivot_type to_pivot_impl(string_type string) const
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

                    {
                        const polymorphic_encoding_type encoding{};
                    }
                    {
                        const polymorphic_encoding_type encoding{ tetengo2::stdalt::make_unique<concrete_encoding>() };
                    }
                    {
                        BOOST_CHECK_THROW(
                            const polymorphic_encoding_type encoding{ std::unique_ptr<concrete_encoding>{} },
                            std::invalid_argument);
                    }
                }

                BOOST_AUTO_TEST_CASE(name)
                {
                    BOOST_TEST_PASSPOINT();

                    const polymorphic_encoding_type encoding{ tetengo2::stdalt::make_unique<concrete_encoding>() };

                    BOOST_CHECK(encoding.name() == concrete_encoding{}.name());
                }

                BOOST_AUTO_TEST_CASE(operator_equal)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const polymorphic_encoding_type encoding1{ tetengo2::stdalt::make_unique<concrete_encoding>() };
                        const polymorphic_encoding_type encoding2{ tetengo2::stdalt::make_unique<concrete_encoding>() };

                        BOOST_CHECK(encoding1 == encoding2);
                    }
                    {
                        const polymorphic_encoding_type encoding1{ tetengo2::stdalt::make_unique<concrete_encoding>() };
                        const concrete_encoding         encoding2{};

                        BOOST_CHECK(encoding1 == encoding2);
                    }
                    {
                        const polymorphic_encoding_type encoding1{ tetengo2::stdalt::make_unique<concrete_encoding>() };
                        const polymorphic_encoding_type encoding2{
                            tetengo2::stdalt::make_unique<another_concrete_encoding>()
                        };

                        BOOST_CHECK(encoding1 != encoding2);
                    }
                    {
                        const polymorphic_encoding_type encoding1{ tetengo2::stdalt::make_unique<concrete_encoding>() };
                        const another_concrete_encoding encoding2{};

                        BOOST_CHECK(encoding1 != encoding2);
                    }
                }

                BOOST_AUTO_TEST_CASE(from_pivot)
                {
                    BOOST_TEST_PASSPOINT();

                    const polymorphic_encoding_type encoding{ tetengo2::stdalt::make_unique<concrete_encoding>() };

                    encoding.from_pivot(encoding_type::pivot_type{});
                }

                BOOST_AUTO_TEST_CASE(to_pivot)
                {
                    BOOST_TEST_PASSPOINT();

                    const polymorphic_encoding_type encoding{ tetengo2::stdalt::make_unique<concrete_encoding>() };

                    encoding.to_pivot(encoding_type::string_type{});
                }


            BOOST_AUTO_TEST_SUITE_END()


            BOOST_AUTO_TEST_CASE(make_polymorphic)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const polymorphic_encoding_type encoding =
                        tetengo2::text::encoding::make_polymorphic<concrete_encoding>();

                    BOOST_CHECK(encoding.name() == concrete_encoding{}.name());
                }
                {
                    const polymorphic_encoding_type encoding =
                        tetengo2::text::encoding::make_polymorphic<concrete_encoding>("hoge");

                    BOOST_CHECK(encoding.name() == "hoge");
                }
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

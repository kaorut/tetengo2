/*! \file
    \brief Test of class tetengo2::text::encoder.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <sstream>
#include <stdexcept>
#include <string>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/encoding.h>
#include <tetengo2/detail/base/impl_set.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/encoding.h>


namespace {
    // types

    class concrete_encoding : public tetengo2::text::encoding::encoding<std::string>
    {
    private:
        virtual const std::string& name_impl() const
        {
            static const std::string singleton{ "test_concrete" };
            return singleton;
        }

        virtual string_type from_pivot_impl(pivot_type pivot) const
        {
            switch (tetengo2::detail::detail_impl_set().encoding_().pivot_type_())
            {
            case tetengo2::detail::base::encoding::pivot_type_type::std_string:
                if (tetengo2::stdalt::index(pivot) != 0)
                    pivot = std::string{};
                return string_type(
                           tetengo2::stdalt::get<std::string>(pivot).begin(),
                           tetengo2::stdalt::get<std::string>(pivot).end()) +
                       string_type{ TETENGO2_TEXT("+ConcreteFromPivot") };
            case tetengo2::detail::base::encoding::pivot_type_type::std_wstring:
                if (tetengo2::stdalt::index(pivot) != 1)
                    pivot = std::wstring{};
                return string_type(
                           tetengo2::stdalt::get<std::wstring>(pivot).begin(),
                           tetengo2::stdalt::get<std::wstring>(pivot).end()) +
                       string_type{ TETENGO2_TEXT("+ConcreteFromPivot") };
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("Unknown pivot type."));
            }
        }

        virtual pivot_type to_pivot_impl(string_type string) const
        {
            switch (tetengo2::detail::detail_impl_set().encoding_().pivot_type_())
            {
            case tetengo2::detail::base::encoding::pivot_type_type::std_string:
                return std::string(string.begin(), string.end()) + std::string{ TETENGO2_TEXT("+ConcreteToPivot") };
            case tetengo2::detail::base::encoding::pivot_type_type::std_wstring:
                return std::wstring(string.begin(), string.end()) + std::wstring{ TETENGO2_TEXT("+ConcreteToPivot") };
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("Unknown pivot type."));
            }
        }
    };

    class another_concrete_encoding : public tetengo2::text::encoding::encoding<std::string>
    {
    private:
        virtual const std::string& name_impl() const
        {
            static const std::string singleton{ "test_another" };
            return singleton;
        }

        virtual string_type from_pivot_impl(pivot_type pivot) const
        {
            switch (tetengo2::detail::detail_impl_set().encoding_().pivot_type_())
            {
            case tetengo2::detail::base::encoding::pivot_type_type::std_string:
                if (tetengo2::stdalt::index(pivot) != 0)
                    pivot = std::string{};
                return string_type(
                           tetengo2::stdalt::get<std::string>(pivot).begin(),
                           tetengo2::stdalt::get<std::string>(pivot).end()) +
                       string_type{ TETENGO2_TEXT("+AnotherFromPivot") };
            case tetengo2::detail::base::encoding::pivot_type_type::std_wstring:
                if (tetengo2::stdalt::index(pivot) != 1)
                    pivot = std::wstring{};
                return string_type(
                           tetengo2::stdalt::get<std::wstring>(pivot).begin(),
                           tetengo2::stdalt::get<std::wstring>(pivot).end()) +
                       string_type{ TETENGO2_TEXT("+AnotherFromPivot") };
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("Unknown pivot type."));
            }
        }

        virtual pivot_type to_pivot_impl(string_type string) const
        {
            switch (tetengo2::detail::detail_impl_set().encoding_().pivot_type_())
            {
            case tetengo2::detail::base::encoding::pivot_type_type::std_string:
                return std::string(string.begin(), string.end()) + std::string{ TETENGO2_TEXT("+AnotherToPivot") };
            case tetengo2::detail::base::encoding::pivot_type_type::std_wstring:
                return std::wstring(string.begin(), string.end()) + std::wstring{ TETENGO2_TEXT("+AnotherToPivot") };
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("Unknown pivot type."));
            }
        }
    };

    class wide_concrete_encoding : public tetengo2::text::encoding::encoding<std::wstring>
    {
    private:
        virtual const std::string& name_impl() const
        {
            static const std::string singleton{ "test_wide" };
            return singleton;
        }

        virtual string_type from_pivot_impl(pivot_type pivot) const
        {
            switch (tetengo2::detail::detail_impl_set().encoding_().pivot_type_())
            {
            case tetengo2::detail::base::encoding::pivot_type_type::std_string:
                if (tetengo2::stdalt::index(pivot) != 0)
                    pivot = std::string{};
                return string_type(
                           tetengo2::stdalt::get<std::string>(pivot).begin(),
                           tetengo2::stdalt::get<std::string>(pivot).end()) +
                       string_type{ TETENGO2_TEXT("+WideFromPivot") };
            case tetengo2::detail::base::encoding::pivot_type_type::std_wstring:
                if (tetengo2::stdalt::index(pivot) != 1)
                    pivot = std::wstring{};
                return string_type(
                           tetengo2::stdalt::get<std::wstring>(pivot).begin(),
                           tetengo2::stdalt::get<std::wstring>(pivot).end()) +
                       string_type{ TETENGO2_TEXT("+WideFromPivot") };
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("Unknown pivot type."));
            }
        }

        virtual pivot_type to_pivot_impl(string_type string) const
        {
            switch (tetengo2::detail::detail_impl_set().encoding_().pivot_type_())
            {
            case tetengo2::detail::base::encoding::pivot_type_type::std_string:
                return std::string(string.begin(), string.end()) + std::string{ TETENGO2_TEXT("+WideToPivot") };
            case tetengo2::detail::base::encoding::pivot_type_type::std_wstring:
                return std::wstring(string.begin(), string.end()) + std::wstring{ TETENGO2_TEXT("+WideToPivot") };
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("Unknown pivot type."));
            }
        }
    };

    using encoder_type = tetengo2::text::encoder<concrete_encoding, concrete_encoding>;

    using another_encoder_type = tetengo2::text::encoder<concrete_encoding, another_concrete_encoding>;

    using wide_encoder_type = tetengo2::text::encoder<concrete_encoding, wide_concrete_encoding>;
}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(text)
        BOOST_AUTO_TEST_SUITE(encoder)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const encoder_type encoder{};
                }
                {
                    const concrete_encoding encoding1{};
                    const concrete_encoding encoding2{};
                    const encoder_type      encoder{ encoding1, encoding2 };
                }
            }

            BOOST_AUTO_TEST_CASE(internal_encoding)
            {
                BOOST_TEST_PASSPOINT();

                const concrete_encoding         encoding1{};
                const another_concrete_encoding encoding2{};
                const another_encoder_type      encoder{ encoding1, encoding2 };

                BOOST_CHECK(encoder.internal_encoding().name() == encoding1.name());
            }

            BOOST_AUTO_TEST_CASE(external_encoding)
            {
                BOOST_TEST_PASSPOINT();

                const concrete_encoding         encoding1{};
                const another_concrete_encoding encoding2{};
                const another_encoder_type      encoder{ encoding1, encoding2 };

                BOOST_CHECK(encoder.external_encoding().name() == encoding2.name());
            }

            BOOST_AUTO_TEST_CASE(encode)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const std::string internal_string{ TETENGO2_TEXT("Tetengo2") };
                    const std::string external_string{ TETENGO2_TEXT("Tetengo2") };

                    const concrete_encoding encoding1{};
                    const concrete_encoding encoding2{};
                    const encoder_type      encoder{ encoding1, encoding2 };

                    BOOST_CHECK(encoder.encode(internal_string) == std::string{ TETENGO2_TEXT("Tetengo2") });
                }
                {
                    const std::string internal_string{ TETENGO2_TEXT("Tetengo2") };
                    const std::string external_string{ TETENGO2_TEXT("Tetengo2") };

                    const concrete_encoding         encoding1{};
                    const another_concrete_encoding encoding2{};
                    const another_encoder_type      encoder{ encoding1, encoding2 };

                    BOOST_CHECK(
                        encoder.encode(internal_string) ==
                        std::string{ TETENGO2_TEXT("Tetengo2+ConcreteToPivot+AnotherFromPivot") });
                }
                {
                    const std::string  internal_string{ TETENGO2_TEXT("Tetengo2") };
                    const std::wstring external_string{ TETENGO2_TEXT("Tetengo2") };

                    const concrete_encoding      encoding1{};
                    const wide_concrete_encoding encoding2{};
                    const wide_encoder_type      encoder{ encoding1, encoding2 };

                    BOOST_CHECK(
                        encoder.encode(internal_string) ==
                        std::wstring{ TETENGO2_TEXT("Tetengo2+ConcreteToPivot+WideFromPivot") });
                }
            }

            BOOST_AUTO_TEST_CASE(decode)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const std::string internal_string{ TETENGO2_TEXT("Tetengo2") };
                    const std::string external_string{ TETENGO2_TEXT("Tetengo2") };

                    const concrete_encoding encoding1{};
                    const concrete_encoding encoding2{};
                    const encoder_type      encoder{ encoding1, encoding2 };

                    BOOST_CHECK(encoder.decode(external_string) == std::string{ TETENGO2_TEXT("Tetengo2") });
                }
                {
                    const std::string internal_string{ TETENGO2_TEXT("Tetengo2") };
                    const std::string external_string{ TETENGO2_TEXT("Tetengo2") };

                    const concrete_encoding         encoding1{};
                    const another_concrete_encoding encoding2{};
                    const another_encoder_type      encoder{ encoding1, encoding2 };

                    BOOST_CHECK(
                        encoder.decode(external_string) ==
                        std::string{ TETENGO2_TEXT("Tetengo2+AnotherToPivot+ConcreteFromPivot") });
                }
                {
                    const std::string  internal_string{ TETENGO2_TEXT("Tetengo2") };
                    const std::wstring external_string{ TETENGO2_TEXT("Tetengo2") };

                    const concrete_encoding      encoding1{};
                    const wide_concrete_encoding encoding2{};
                    const wide_encoder_type      encoder{ encoding1, encoding2 };

                    BOOST_CHECK(
                        encoder.decode(external_string) ==
                        std::string{ TETENGO2_TEXT("Tetengo2+WideToPivot+ConcreteFromPivot") });
                }
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

/*! \file
    \brief Test of class tetengo2::config::config_base.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <string>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/variant.hpp>

#include <tetengo2/config/config_base.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>


namespace {
    // types

    using config_base_type = tetengo2::config::config_base;

    using string_type = config_base_type::string_type;

    using uint_type = config_base_type::uint_type;

    using value_type = config_base_type::value_type;

    class concrete_config : public config_base_type
    {
    public:
        concrete_config() {}

    private:
        virtual tetengo2::stdalt::optional<value_type> get_impl(const string_type& key) const override
        {
            static const tetengo2::stdalt::optional<value_type> value1{ value_type{
                string_type{ TETENGO2_TEXT("hoge") } } };
            static const tetengo2::stdalt::optional<value_type> value2{ value_type{ 42 } };
            return key == string_type{ TETENGO2_TEXT("foo") } ? value1 : value2;
        }

        virtual void set_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const string_type& key,
            TETENGO2_STDALT_MAYBE_UNUSED value_type value) override
        {}

        virtual void clear_impl() override {}
    };
}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(config)
        BOOST_AUTO_TEST_SUITE(config_base)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                const concrete_config config{};
            }

            BOOST_AUTO_TEST_CASE(get)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const concrete_config config{};

                    const auto value = config.get(string_type{ TETENGO2_TEXT("foo") });
                    BOOST_TEST_REQUIRE(tetengo2::stdalt::has_value(value));
                    BOOST_CHECK(boost::get<string_type>(*value) == string_type{ TETENGO2_TEXT("hoge") });
                }
                {
                    const concrete_config config{};

                    const auto value = config.get(string_type{ TETENGO2_TEXT("bar") });
                    BOOST_TEST_REQUIRE(tetengo2::stdalt::has_value(value));
                    BOOST_TEST(boost::get<uint_type>(*value) == 42U);
                }
            }

            BOOST_AUTO_TEST_CASE(set)
            {
                BOOST_TEST_PASSPOINT();

                {
                    concrete_config config{};

                    config.set(string_type{ TETENGO2_TEXT("foo") }, string_type{ TETENGO2_TEXT("hoge") });
                }
                {
                    concrete_config config{};

                    config.set(string_type{ TETENGO2_TEXT("bar") }, 42);
                }
            }

            BOOST_AUTO_TEST_CASE(clear)
            {
                BOOST_TEST_PASSPOINT();

                {
                    concrete_config config{};

                    config.clear();
                }
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

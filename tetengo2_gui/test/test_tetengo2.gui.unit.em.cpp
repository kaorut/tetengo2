/*! \file
    \brief Test of class tetengo2::gui::unit::basic_em.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <sstream>
#include <utility>

#include <boost/operators.hpp>
#include <boost/preprocessor.hpp>
#include <boost/rational.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/unit/em.h>
#include <tetengo2/type_list.h>


namespace {
    // types

    using difference_rational_type = boost::rational<tetengo2::type_list::difference_type>;

    using unit_type = tetengo2::gui::unit::em;

    using another_unit_type = tetengo2::gui::unit::uem;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(unit)
            BOOST_AUTO_TEST_SUITE(basic_em)
                // test cases

                BOOST_AUTO_TEST_CASE(from)
                {
                    BOOST_TEST_PASSPOINT();

                    const auto unit = unit_type::from(another_unit_type{ 123 });

                    BOOST_TEST(unit.value() == 123);
                }

                BOOST_AUTO_TEST_CASE(from_pixels)
                {
                    BOOST_TEST_PASSPOINT();

                    const auto unit = unit_type::from_pixels(123 * unit_type{ 1 }.to_pixels());

                    BOOST_TEST(unit.value() == 123);
                }

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const unit_type unit{};
                    }
                    {
                        const difference_rational_type value{ 123 };
                        const unit_type                unit{ std::move(value) };
                    }
                    {
                        const unit_type unit{ 123 };
                    }
                }

                BOOST_AUTO_TEST_CASE(operator_equal)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const unit_type unit1{ 123 };

                        BOOST_CHECK(unit1 == difference_rational_type{ 123 });
                    }
                    {
                        const unit_type unit1{ 456 };

                        BOOST_CHECK(unit1 != difference_rational_type{ 123 });
                    }
                }

                BOOST_AUTO_TEST_CASE(operator_less_than)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const unit_type unit1{ 123 };

                        BOOST_CHECK(unit1 < difference_rational_type{ 456 });
                    }
                }

                BOOST_AUTO_TEST_CASE(operator_greater_than)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const unit_type unit1{ 456 };

                        BOOST_CHECK(unit1 > difference_rational_type{ 123 });
                    }
                }

                BOOST_AUTO_TEST_CASE(add)
                {
                    BOOST_TEST_PASSPOINT();

                    unit_type unit1{ 456 };

                    unit1.add(123);

                    BOOST_TEST(unit1.value() == 579);
                }

                BOOST_AUTO_TEST_CASE(subtract)
                {
                    BOOST_TEST_PASSPOINT();

                    unit_type unit1{ 456 };

                    unit1.subtract(123);

                    BOOST_TEST(unit1.value() == 333);
                }

                BOOST_AUTO_TEST_CASE(multiply)
                {
                    BOOST_TEST_PASSPOINT();

                    unit_type unit1{ 456 };

                    unit1.multiply(123);

                    BOOST_TEST(unit1.value() == 56088);
                }

                BOOST_AUTO_TEST_CASE(divide_by)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        unit_type unit1{ 456 };

                        unit1.divide_by(152);

                        BOOST_TEST(unit1.value() == 3);
                    }
                    {
                        const unit_type unit1{ 456 };
                        const unit_type unit2{ 152 };

                        BOOST_TEST(unit1.divide_by(unit2) == 3);
                    }
                }

                BOOST_AUTO_TEST_CASE(value)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const unit_type unit{};

                        BOOST_TEST(unit.value() == 0);
                    }
                    {
                        const unit_type unit{ 123 };

                        BOOST_TEST(unit.value() == 123);
                    }
                }

                BOOST_AUTO_TEST_CASE(to_pixels)
                {
                    BOOST_TEST_PASSPOINT();

                    const unit_type unit{ 123 };

                    BOOST_TEST(unit.to_pixels() == 123 * unit_type{ 1 }.to_pixels());
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

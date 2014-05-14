/*! \file
    \brief Test of class tetengo2::gui::unit::unit.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/swap.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.gui.h>


namespace
{
    // types

    template <typename Value>
    class concrete_unit : public tetengo2::gui::unit::unit<concrete_unit<Value>, Value>
    {
    public:
        // types

        using value_type = Value;


        // static functions

        template <typename PV>
        static concrete_unit from_pixels(const PV value)
        {
            return concrete_unit(value / 7);
        }


        // constructors and destructor

        explicit concrete_unit(const value_type& value)
        :
        m_value(value)
        {}


        // functions

        friend bool operator==(const concrete_unit& one, const value_type& another)
        {
            return one.m_value == another;
        }

        friend bool operator<(const concrete_unit& one, const value_type& another)
        {
            return one.m_value < another;
        }

        friend bool operator>(const concrete_unit& one, const value_type& another)
        {
            return one.m_value > another;
        }

        concrete_unit& add(const value_type& another)
        {
            concrete_unit temp(*this);

            temp.m_value += another;

            boost::swap(temp, *this);
            return *this;
        }

        concrete_unit& subtract(const value_type& another)
        {
            concrete_unit temp(*this);

            temp.m_value -= another;

            boost::swap(temp, *this);
            return *this;
        }

        concrete_unit& multiply(const value_type& another)
        {
            concrete_unit temp(*this);

            temp.m_value *= another;

            boost::swap(temp, *this);
            return *this;
        }

        concrete_unit& divide_by(const value_type& another)
        {
            concrete_unit temp(*this);

            temp.m_value /= another;

            boost::swap(temp, *this);
            return *this;
        }

        value_type divide_by(const concrete_unit& another)
        const
        {
            return value() / another.value();
        }

        const value_type& value()
        const
        {
            return m_value;
        }

        template <typename PV>
        PV to_pixels()
        const
        {
            return m_value * 7;
        }


    private:
        // variables

        value_type m_value;


    };

    using unit_type = concrete_unit<int>;

    using another_unit_type = concrete_unit<unsigned short>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(unit)
BOOST_AUTO_TEST_SUITE(unit)
    // test cases

    BOOST_AUTO_TEST_CASE(from)
    {
        BOOST_TEST_PASSPOINT();

        const another_unit_type another_unit(123);
        const auto unit = unit_type::from(another_unit);

        BOOST_CHECK_EQUAL(unit.value(), 123);
    }

    BOOST_AUTO_TEST_CASE(operator_plus_assign)
    {
        BOOST_TEST_PASSPOINT();

        {
            unit_type unit1(456);
            const unit_type unit2(123);

            unit1 += unit2;

            BOOST_CHECK_EQUAL(unit1.value(), 579);
        }
        {
            unit_type unit1(456);
            const another_unit_type unit2(123);

            unit1 += unit2;

            BOOST_CHECK_EQUAL(unit1.value(), 579);
        }
        {
            unit_type unit1(456);

            unit1 += 123;

            BOOST_CHECK_EQUAL(unit1.value(), 579);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_plus)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1(456);
            const unit_type unit2(123);

            const auto unit3 = unit1 + unit2;

            BOOST_CHECK_EQUAL(unit3.value(), 579);
        }
        {
            const unit_type unit1(456);
            const another_unit_type unit2(123);

            const auto unit3 = unit1 + unit2;

            BOOST_CHECK_EQUAL(unit3.value(), 579);
        }
        {
            const unit_type unit1(456);

            const auto unit3 = unit1 + 123;

            BOOST_CHECK_EQUAL(unit3.value(), 579);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_minus_assign)
    {
        BOOST_TEST_PASSPOINT();

        {
            unit_type unit1(456);
            const unit_type unit2(123);

            unit1 -= unit2;

            BOOST_CHECK_EQUAL(unit1.value(), 333);
        }
        {
            unit_type unit1(456);
            const another_unit_type unit2(123);

            unit1 -= unit2;

            BOOST_CHECK_EQUAL(unit1.value(), 333);
        }
        {
            unit_type unit1(456);

            unit1 -= 123;

            BOOST_CHECK_EQUAL(unit1.value(), 333);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_minus)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1(456);
            const unit_type unit2(123);

            const auto unit3 = unit1 - unit2;

            BOOST_CHECK_EQUAL(unit3.value(), 333);
        }
        {
            const unit_type unit1(456);
            const another_unit_type unit2(123);

            const auto unit3 = unit1 - unit2;

            BOOST_CHECK_EQUAL(unit3.value(), 333);
        }
        {
            const unit_type unit1(456);

            const auto unit3 = unit1 - 123;

            BOOST_CHECK_EQUAL(unit3.value(), 333);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_multiply_assign)
    {
        BOOST_TEST_PASSPOINT();

        {
            unit_type unit1(456);

            unit1 *= 123;

            BOOST_CHECK_EQUAL(unit1.value(), 56088);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_multiply)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1(456);

            const auto unit3 = unit1 * 123;

            BOOST_CHECK_EQUAL(unit3.value(), 56088);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_divide_assign)
    {
        BOOST_TEST_PASSPOINT();

        {
            unit_type unit1(456);

            unit1 /= 123;

            BOOST_CHECK_EQUAL(unit1.value(), 3);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_divide)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1(456);

            const auto unit3 = unit1 / 123;

            BOOST_CHECK_EQUAL(unit3.value(), 3);
        }
        {
            const unit_type unit1(456);
            const unit_type unit2(123);

            const int value = unit1 / unit2;

            BOOST_CHECK_EQUAL(value, 3);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1(123);
            const unit_type unit2(123);

            BOOST_CHECK(unit1 == unit2);
        }
        {
            const unit_type unit1(123);
            const another_unit_type unit2(123);

            BOOST_CHECK(unit1 == unit2);
        }
        {
            const unit_type unit1(123);

            BOOST_CHECK(unit1 == 123);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_not_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1(456);
            const unit_type unit2(123);

            BOOST_CHECK(unit1 != unit2);
        }
        {
            const unit_type unit1(456);
            const another_unit_type unit2(123);

            BOOST_CHECK(unit1 != unit2);
        }
        {
            const unit_type unit1(456);

            BOOST_CHECK(unit1 != 123);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_less_than)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1(123);
            const unit_type unit2(456);

            BOOST_CHECK(unit1 < unit2);
        }
        {
            const unit_type unit1(456);
            const unit_type unit2(123);

            BOOST_CHECK(unit1 > unit2);
        }
        {
            const unit_type unit1(123);
            const another_unit_type unit2(456);

            BOOST_CHECK(unit1 < unit2);
        }
        {
            const unit_type unit1(123);

            BOOST_CHECK(unit1 < 456);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_greater_than)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1(456);
            const another_unit_type unit2(123);

            BOOST_CHECK(unit1 > unit2);
        }
        {
            const unit_type unit1(456);

            BOOST_CHECK(unit1 > 123);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

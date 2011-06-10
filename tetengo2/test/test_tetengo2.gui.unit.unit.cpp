/*! \file
    \brief Test of class tetengo2::gui::unit::unit.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <utility>

#include <boost/swap.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.unit.unit.h"


namespace
{
    // types

    template <typename Value, typename PixelValue>
    class concrete_unit :
        public tetengo2::gui::unit::unit<
            concrete_unit<Value, PixelValue>, Value
        >
    {
    public:
        // types

        typedef Value value_type;

        typedef PixelValue pixel_value_type;


        // static functions

        static concrete_unit from_pixels(const pixel_value_type value)
        {
            return concrete_unit(value / 7);
        }


        // constructors and destructor

        explicit concrete_unit(const value_type& value)
        :
        m_value(value)
        {}

        explicit concrete_unit(value_type&& value)
        :
        m_value(std::forward<value_type>(value))
        {}


        // functions

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

        friend bool operator==(
            const concrete_unit& one,
            const value_type&    another
        )
        {
            return one.m_value == another;
        }

        friend bool operator<(
            const concrete_unit& one,
            const value_type&    another
        )
        {
            return one.m_value < another;
        }

        friend bool operator>(
            const concrete_unit& one,
            const value_type&    another
        )
        {
            return one.m_value > another;
        }

        const value_type& value()
        const
        {
            return m_value;
        }

        pixel_value_type to_pixels()
        const
        {
            return m_value * 7;
        }


    private:
        // variables

        value_type m_value;


    };

    typedef concrete_unit<int, int> unit_type;

    typedef concrete_unit<unsigned short, unsigned short> another_unit_type;


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
        const unit_type unit = unit_type::from(another_unit);

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

            const unit_type unit3 = unit1 + unit2;

            BOOST_CHECK_EQUAL(unit3.value(), 579);
        }
        {
            const unit_type unit1(456);
            const another_unit_type unit2(123);

            const unit_type unit3 = unit1 + unit2;

            BOOST_CHECK_EQUAL(unit3.value(), 579);
        }
        {
            const unit_type unit1(456);

            const unit_type unit3 = unit1 + 123;

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

            const unit_type unit3 = unit1 - unit2;

            BOOST_CHECK_EQUAL(unit3.value(), 333);
        }
        {
            const unit_type unit1(456);
            const another_unit_type unit2(123);

            const unit_type unit3 = unit1 - unit2;

            BOOST_CHECK_EQUAL(unit3.value(), 333);
        }
        {
            const unit_type unit1(456);

            const unit_type unit3 = unit1 - 123;

            BOOST_CHECK_EQUAL(unit3.value(), 333);
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
            const unit_type unit1(456);
            const unit_type unit2(123);

            BOOST_CHECK(unit1 != unit2);
        }
        {
            const unit_type unit1(123);
            const another_unit_type unit2(123);

            BOOST_CHECK(unit1 == unit2);
        }
        {
            const unit_type unit1(456);
            const another_unit_type unit2(123);

            BOOST_CHECK(unit1 != unit2);
        }
        {
            const unit_type unit1(123);

            BOOST_CHECK(unit1 == 123);
        }
        {
            const unit_type unit1(456);

            BOOST_CHECK(unit1 != 123);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_less)
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

    BOOST_AUTO_TEST_CASE(operator_greater)
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

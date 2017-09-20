/*! \file
    \brief The definition of tetengo2::gui::unit::point.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_UNIT_POINT_H)
#define TETENGO2_GUI_UNIT_POINT_H

#include <type_traits>

#include <boost/rational.hpp>
#include <boost/swap.hpp>

#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui { namespace unit
{
    /*!
        \brief The class template for a point unit.

        \tparam Value       A value type.
        \tparam UnitDetails A detail implementation type of a unit.
   */
    template <typename Value, typename UnitDetails>
    class point : public unit<point<Value, UnitDetails>, Value>
    {
    public:
        // types

        //! The value type.
        using value_type = Value;

        //! The unit details type.
        using unit_details_type = UnitDetails;


        // static functions

        /*!
            \brief Returns a unit made from another point unit.

            \tparam V  A value type.

            \param another A value in another point unit.

            \return A point unit.
        */
        template <typename V>
        static point from(const point<V, unit_details_type>& another)
        {
            return point{ cast<value_type>(another.value()) };
        }

        /*!
            \brief Returns a point unit made from a value in pixels.

            \tparam PixelValue A pixel value type.

            \param value A value in pixels.

            \return An point unit.
        */
        template <typename PixelValue>
        static point from_pixels(const PixelValue value)
        {
            return from_pixels_impl(value);
        }


        // constructors and destructor

        /*!
            \brief Creates a point unit.

            \param value A value.
        */
        explicit point(const value_type& value)
        :
        m_value(value)
        {}


        // functions

        /*!
            \brief Checks whether one point unit is equal to another.

            \param one     One point unit.
            \param another Another value in point unit.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const point& one, const value_type& another)
        {
            return one.m_value == another;
        }

        /*!
            \brief Checks whether one point unit is less than another.

            \param one     One point unit.
            \param another Another value in point unit.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        friend bool operator<(const point& one, const value_type& another)
        {
            return one.m_value < another;
        }

        /*!
            \brief Checks whether one point unit is greater than another.

            \param one     One point unit.
            \param another Another value in point unit.

            \retval true  When the one is greater than the other.
            \retval false Otherwise.
        */
        friend bool operator>(const point& one, const value_type& another)
        {
            return one.m_value > another;
        }

        /*!
            \brief Adds another value in point unit.

            \param another Another value in point unit.

            \return This object.
        */
        point& add(const value_type& another)
        {
            point temp{ *this };

            temp.m_value += another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Subtracts another value in point unit.

            \param another Another value in point unit.

            \return This object.
        */
        point& subtract(const value_type& another)
        {
            point temp{ *this };

            temp.m_value -= another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Multiplies another value in point unit.

            \param another Another value in point unit.

            \return This object.
        */
        point& multiply(const value_type& another)
        {
            point temp{ *this };

            temp.m_value *= another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Divides by another value in point unit.

            \param another Another value in point unit.

            \return This object.
        */
        point& divide_by(const value_type& another)
        {
            point temp{ *this };

            temp.m_value /= another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Divides by another point unit.

            \param another Another point unit.

            \return A value.
        */
        value_type divide_by(const point& another)
        const
        {
            return value() / another.value();
        }

        /*!
            \brief Returns the value.

            \return The value.
        */
        const value_type& value()
        const
        {
            return m_value;
        }

        /*!
            \brief Returns the value in pixels.

            \tparam PixelValue A pixel value type.

            \return The value in points.
        */
        template <typename PixelValue>
        PixelValue to_pixels()
        const
        {
            return to_pixels_impl<PixelValue>(m_value);
        }


    private:
        // static functions

        template <typename To, typename From>
        static To cast(
            const From from,
            typename std::enable_if<std::is_convertible<From, To>::value>::type* = nullptr
        )
        {
            return static_cast<To>(from);
        }

        template <typename To, typename FromInteger>
        static To cast(const boost::rational<FromInteger>& from)
        {
            return
                To{
                    static_cast<typename To::int_type>(from.numerator()),
                    static_cast<typename To::int_type>(from.denominator())
                };
        }

        template <typename PixelValue>
        static point from_pixels_impl(
            const PixelValue value,
            typename std::enable_if<std::is_unsigned<PixelValue>::value>::type* = nullptr
        )
        {
            return point{ unit_details_type::instance().to_point(static_cast<type_list::size_type>(value)) };
        }

        template <typename PixelValue>
        static point from_pixels_impl(
            const PixelValue value,
            typename std::enable_if<std::is_signed<PixelValue>::value>::type* = nullptr
        )
        {
            return point{ unit_details_type::instance().to_point(static_cast<type_list::difference_type>(value)) };
        }

        template <typename PixelValue>
        static PixelValue to_pixels_impl(
            const value_type& value,
            typename std::enable_if<std::is_unsigned<PixelValue>::value>::type* = nullptr
        )
        {
            return unit_details_type::instance().point_to_pixel<type_list::size_type>(value);
        }

        template <typename PixelValue>
        static PixelValue to_pixels_impl(
            const value_type& value,
            typename std::enable_if<std::is_signed<PixelValue>::value>::type* = nullptr
        )
        {
            return unit_details_type::instance().point_to_pixel<type_list::difference_type>(value);
        }


        // variables

        value_type m_value;


    };


}}}


#endif

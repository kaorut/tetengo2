/*! \file
    \brief The definition of tetengo2::gui::unit::basic_point.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_UNIT_POINT_H)
#define TETENGO2_GUI_UNIT_POINT_H

#include <type_traits>

#include <boost/rational.hpp>

#include <tetengo2/detail/base/unit.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui { namespace unit
{
    /*!
        \brief The class template for a point unit.

        \tparam Value A value type.
   */
    template <typename Value>
    class basic_point : public unit<basic_point<Value>, Value>
    {
    public:
        // types

        //! The value type.
        using value_type = Value;

        //! The unit details type.
        using unit_details_type = detail::base::unit;


        // static functions

        /*!
            \brief Returns a unit made from another point unit.

            \tparam V  A value type.

            \param another A value in another point unit.

            \return A point unit.
        */
        template <typename V>
        static basic_point from(const basic_point<V>& another)
        {
            return basic_point{ cast<value_type>(another.value()), another.details() };
        }

        /*!
            \brief Returns a point unit made from a value in pixels.

            \tparam PixelValue A pixel value type.

            \param value        A value in pixels.
            \param unit_details Unit details.

            \return A point unit.
        */
        template <typename PixelValue>
        static basic_point from_pixels(const PixelValue value, const unit_details_type& unit_details)
        {
            return from_pixels_impl(static_cast<typename value_type::int_type>(value), unit_details);
        }


        // constructors and destructor

        /*!
            \brief Creates a point unit.

            \param value        A value.
            \param unit_details Unit details.
        */
        basic_point(value_type value, const unit_details_type& unit_details);


        // functions

        /*!
            \brief Checks whether one point unit is equal to another.

            \tparam V1 A value #1 type.
            \tparam V2 A value #2 type.

            \param one     One point unit.
            \param another Another value in point unit.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        template <typename V1, typename V2>
        friend bool operator==(const basic_point<V1>& one, const V2& another);

        /*!
            \brief Checks whether one point unit is less than another.

            \tparam V1 A value #1 type.
            \tparam V2 A value #2 type.

            \param one     One point unit.
            \param another Another value in point unit.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        template <typename V1, typename V2>
        friend bool operator<(const basic_point<V1>& one, const V2& another);

        /*!
            \brief Checks whether one point unit is greater than another.

            \tparam V1 A value #1 type.
            \tparam V2 A value #2 type.

            \param one     One point unit.
            \param another Another value in point unit.

            \retval true  When the one is greater than the other.
            \retval false Otherwise.
        */
        template <typename V1, typename V2>
        friend bool operator>(const basic_point<V1>& one, const V2& another);

        /*!
            \brief Adds another value in point unit.

            \param another Another value in point unit.

            \return This object.
        */
        basic_point& add(const value_type& another);

        /*!
            \brief Subtracts another value in point unit.

            \param another Another value in point unit.

            \return This object.
        */
        basic_point& subtract(const value_type& another);

        /*!
            \brief Multiplies another value in point unit.

            \param another Another value in point unit.

            \return This object.
        */
        basic_point& multiply(const value_type& another);

        /*!
            \brief Divides by another value in point unit.

            \param another Another value in point unit.

            \return This object.
        */
        basic_point& divide_by(const value_type& another);

        /*!
            \brief Divides by another point unit.

            \param another Another point unit.

            \return A value.
        */
        value_type divide_by(const basic_point& another)
        const;

        /*!
            \brief Returns the value.

            \return The value.
        */
        const value_type& value()
        const;

        /*!
            \brief Returns the value in pixels.

            \tparam PixelValue A pixel value type.

            \return The value in pixels.
        */
        template <typename PixelValue>
        PixelValue to_pixels()
        const
        {
            return static_cast<PixelValue>(to_pixels_impl(m_value, *m_p_details));
        }

        /*!
            \brief Returns the unit details.

            \return The unit details.
        */
        const unit_details_type& details()
        const;


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

        static basic_point from_pixels_impl(
            const typename value_type::int_type value,
            const unit_details_type&            unit_details
        );

        static typename value_type::int_type to_pixels_impl(
            const value_type&        value,
            const unit_details_type& unit_details
        );


        // variables

        value_type m_value;

        const unit_details_type* m_p_details;


    };


    //! The signed point type.
    using point = basic_point<boost::rational<type_list::difference_type>>;

    //! The unsigned point type.
    using upoint = basic_point<boost::rational<type_list::size_type>>;


}}}


#endif

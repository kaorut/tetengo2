/*! \file
    \brief The definition of tetengo2::gui::unit::basic_point.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_UNIT_POINT_H)
#define TETENGO2_GUI_UNIT_POINT_H

#include <type_traits>

#include <boost/predef.h>
#include <boost/rational.hpp>

#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/type_list.h>

namespace tetengo2::detail {
    namespace stub {
        class unit;
    }
#if BOOST_OS_WINDOWS
    namespace windows {
        class unit;
    }
#endif
}


namespace tetengo2::gui::unit {
    /*!
        \brief The class template for a point unit.

        \tparam IntValue    A integer value type.
        \tparam UnitDetails A unit details type.
   */
    template <typename IntValue, typename UnitDetails>
    class basic_point : public unit<basic_point<IntValue, UnitDetails>, IntValue>
    {
    public:
        // types

        //! The integer value type.
        using int_value_type = IntValue;

        //! The value type.
        using value_type = boost::rational<int_value_type>;

        //! The unit details type.
        using unit_details_type = UnitDetails;


        // static functions

        /*!
            \brief Returns a unit made from another point unit.

            \tparam IV A integer value type.

            \param another A value in another point unit.

            \return A point unit.
        */
        template <typename IV>
        static basic_point from(const basic_point<IV, unit_details_type>& another)
        {
            return basic_point{ cast<value_type>(another.value()) };
        }

        /*!
            \brief Returns a point unit made from a value in pixels.

            \param int_value A value in pixels.

            \return A point unit.
        */
        static basic_point from_pixels(int_value_type int_value);


        // constructors and destructor

        /*!
            \brief Creates a point unit with zero.
        */
        basic_point();

        /*!
            \brief Creates a point unit.

            \param value A value.
        */
        explicit basic_point(value_type value);


        // functions

        /*!
            \brief Checks whether one point unit is equal to another.

            \tparam IV  An integer value type.
            \tparam UD  A unit details_type.

            \param one     One point unit.
            \param another Another value in point unit.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        template <typename IV, typename UD>
        friend bool operator==(const basic_point<IV, UD>& one, const typename basic_point<IV, UD>::value_type& another);

        /*!
            \brief Checks whether one point unit is less than another.

            \tparam IV  An integer value type.
            \tparam UD  A unit details_type.

            \param one     One point unit.
            \param another Another value in point unit.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        template <typename IV, typename UD>
        friend bool operator<(const basic_point<IV, UD>& one, const typename basic_point<IV, UD>::value_type& another);

        /*!
            \brief Checks whether one point unit is greater than another.

            \tparam IV  An integer value type.
            \tparam UD  A unit details_type.

            \param one     One point unit.
            \param another Another value in point unit.

            \retval true  When the one is greater than the other.
            \retval false Otherwise.
        */
        template <typename IV, typename UD>
        friend bool operator>(const basic_point<IV, UD>& one, const typename basic_point<IV, UD>::value_type& another);

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
        value_type divide_by(const basic_point& another) const;

        /*!
            \brief Returns the value.

            \return The value.
        */
        const value_type& value() const;

        /*!
            \brief Returns the value in pixels.

            \return The value in pixels.
        */
        int_value_type to_pixels() const;


    private:
        // static functions

        template <typename To, typename From>
        static To cast(const From from, typename std::enable_if<std::is_convertible<From, To>::value>::type* = nullptr)
        {
            return static_cast<To>(from);
        }

        template <typename To, typename FromInteger>
        static To cast(const boost::rational<FromInteger>& from)
        {
            return To{ static_cast<typename To::int_type>(from.numerator()),
                       static_cast<typename To::int_type>(from.denominator()) };
        }


        // variables

        value_type m_value;
    };


#if BOOST_OS_WINDOWS
    //! The signed point type.
    using point = basic_point<type_list::difference_type, detail::windows::unit>;

    //! The unsigned point type.
    using upoint = basic_point<type_list::size_type, detail::windows::unit>;
#elif BOOST_OS_LINUX
    //! The signed point type.
    using point = basic_point<type_list::difference_type, detail::stub::unit>;

    //! The unsigned point type.
    using upoint = basic_point<type_list::size_type, detail::stub::unit>;
#else
#error Unsupported platform.
#endif
}


#endif

/*! \file
    \brief The definition of tetengo2::gui::unit::basic_pixel.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_UNIT_PIXEL_H)
#define TETENGO2_GUI_UNIT_PIXEL_H

#include <type_traits>

#include <boost/rational.hpp>

#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::unit {
    /*!
        \brief The class template for a pixel unit.

        \tparam IntValue A integer value type.
   */
    template <typename IntValue>
    class basic_pixel : public unit<basic_pixel<IntValue>, IntValue>
    {
    public:
        // types

        //! The integer value type.
        using int_value_type = IntValue;

        //! The value type.
        using value_type = boost::rational<int_value_type>;


        // static functions

        /*!
            \brief Returns a unit made from another pixel unit.

            \tparam IV  A integer value type.

            \param another A value in another pixel unit.

            \return A pixel unit.
        */
        template <typename IV>
        static basic_pixel from(const basic_pixel<IV>& another)
        {
            return basic_pixel{ cast<value_type>(another.value()) };
        }

        /*!
            \brief Returns a pixel unit made from a value in pixels.

            \param int_value A value in pixels.

            \return A pixel unit.
        */
        static basic_pixel from_pixels(int_value_type int_value);


        // constructors and destructor

        /*!
            \brief Creates a pixel unit with zero.
        */
        basic_pixel();

        /*!
            \brief Creates a pixel unit.

            \param value A value in pixels.
        */
        explicit basic_pixel(value_type value);


        // functions

        /*!
            \brief Checks whether one  pixel unit is equal to another.

            \tparam IV An integer value type.

            \param one     One pixel unit.
            \param another Another value in pixel unit.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        template <typename IV>
        friend bool operator==(const basic_pixel<IV>& one, const typename basic_pixel<IV>::value_type& another);

        /*!
            \brief Checks whether one pixel unit is less than another.

            \tparam IV An integer value type.

            \param one     One pixel unit.
            \param another Another value in pixel unit.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        template <typename IV>
        friend bool operator<(const basic_pixel<IV>& one, const typename basic_pixel<IV>::value_type& another);

        /*!
            \brief Checks whether one pixel unit is greater than another.

            \tparam IV An integer value type.

            \param one     One pixel unit.
            \param another Another value in pixel unit.

            \retval true  When the one is greater than the other.
            \retval false Otherwise.
        */
        template <typename IV>
        friend bool operator>(const basic_pixel<IV>& one, const typename basic_pixel<IV>::value_type& another);

        /*!
            \brief Adds another value in pixel unit.

            \param another Another value in pixel unit.

            \return This object.
        */
        basic_pixel& add(const value_type& another);

        /*!
            \brief Subtracts another value in pixel unit.

            \param another Another value in pixel unit.

            \return This object.
        */
        basic_pixel& subtract(const value_type& another);

        /*!
            \brief Multiplies another value in pixel unit.

            \param another Another value in pixel unit.

            \return This object.
        */
        basic_pixel& multiply(const value_type& another);

        /*!
            \brief Divides by another value in pixel unit.

            \param another Another value in pixel unit.

            \return This object.
        */
        basic_pixel& divide_by(const value_type& another);

        /*!
            \brief Divides by another pixel unit.

            \param another Another pixel unit.

            \return A value.
        */
        value_type divide_by(const basic_pixel& another) const;

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


    //! The signed pixel type.
    using pixel = basic_pixel<type_list::difference_type>;

    //! The unsigned pixel type.
    using upixel = basic_pixel<type_list::size_type>;
}

#endif

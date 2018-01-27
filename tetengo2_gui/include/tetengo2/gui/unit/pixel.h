/*! \file
    \brief The definition of tetengo2::gui::unit::basic_pixel.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_UNIT_PIXEL_H)
#define TETENGO2_GUI_UNIT_PIXEL_H

#include <boost/rational.hpp> // IWYU pragma: keep

#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui { namespace unit
{
    /*!
        \brief The class template for a pixel unit.

        \tparam Value A value type.
   */
    template <typename Value>
    class basic_pixel : public unit<basic_pixel<Value>, Value>
    {
    public:
        // types

        //! The value type.
        using value_type = Value;


        // static functions

        /*!
            \brief Returns a pixel unit made from a value in pixels.

            \tparam PixelValue A basic_pixel value type.

            \param value A value in pixels.

            \return A pixel unit.
        */
        template <typename PixelValue>
        static basic_pixel from_pixels(const PixelValue value)
        {
            return basic_pixel{ value_type{ value } };
        }


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

            \tparam V A value type.

            \param one     One pixel unit.
            \param another Another value in pixel unit.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        template <typename V>
        friend bool operator==(const basic_pixel<V>& one, const V& another);

        /*!
            \brief Checks whether one pixel unit is less than another.

            \tparam V A value type.

            \param one     One pixel unit.
            \param another Another value in pixel unit.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        template <typename V>
        friend bool operator<(const basic_pixel<V>& one, const V& another);

        /*!
            \brief Checks whether one pixel unit is greater than another.

            \tparam V A value type.

            \param one     One pixel unit.
            \param another Another value in pixel unit.

            \retval true  When the one is greater than the other.
            \retval false Otherwise.
        */
        template <typename V>
        friend bool operator>(const basic_pixel<V>& one, const V& another);

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
        value_type divide_by(const basic_pixel& another)
        const;

        /*!
            \brief Returns the value.

            \return The value.
        */
        const value_type& value()
        const;

        /*!
            \brief Returns the value in pixels.

            \tparam PixelValue A basic_pixel value type.

            \return The value in pixels.
        */
        template <typename PixelValue>
        PixelValue to_pixels()
        const
        {
            return static_cast<PixelValue>(to_pixels_impl(m_value));
        }


    private:
        // static functions

        static typename value_type::int_type to_pixels_impl(const value_type& value);


        // variables

        value_type m_value;


    };


    //! The signed pixel type.
    using pixel = basic_pixel<boost::rational<type_list::difference_type>>;

    //! The unsigned pixel type.
    using upixel = basic_pixel<boost::rational<type_list::size_type>>;


}}}

#endif

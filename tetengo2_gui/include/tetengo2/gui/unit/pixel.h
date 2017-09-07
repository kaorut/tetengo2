/*! \file
    \brief The definition of tetengo2::gui::unit::pixel.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_UNIT_PIXEL_H)
#define TETENGO2_GUI_UNIT_PIXEL_H

#include <type_traits>

#include <boost/rational.hpp>
#include <boost/swap.hpp>

#include <tetengo2/gui/unit/unit.h>


namespace tetengo2 { namespace gui { namespace unit
{
    /*!
        \brief The class template for a pixel unit.

        \tparam Value A value type.
   */
    template <typename Value>
    class pixel : public unit<pixel<Value>, Value>
    {
    public:
        // types

        //! The value type.
        using value_type = Value;


        // static functions

        /*!
            \brief Returns a pixel unit made from a value in pixels.

            \tparam PixelValue A pixel value type.

            \param value A value in pixels.

            \return A pixel unit.
        */
        template <typename PixelValue>
        static pixel from_pixels(const PixelValue value)
        {
            return pixel{ static_cast<value_type>(value) };
        }


        // constructors and destructor

        /*!
            \brief Creates a pixel unit.

            \param value A value.
        */
        explicit pixel(const value_type& value)
        :
        m_value(value)
        {}


        // functions

        /*!
            \brief Checks whether one  pixel unit is equal to another.

            \param one     One pixel unit.
            \param another Another value in pixel unit.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const pixel& one, const value_type& another)
        {
            return one.m_value == another;
        }

        /*!
            \brief Checks whether one pixel unit is less than another.

            \param one     One pixel unit.
            \param another Another value in pixel unit.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        friend bool operator<(const pixel& one, const value_type& another)
        {
            return one.m_value < another;
        }

        /*!
            \brief Checks whether one pixel unit is greater than another.

            \param one     One pixel unit.
            \param another Another value in pixel unit.

            \retval true  When the one is greater than the other.
            \retval false Otherwise.
        */
        friend bool operator>(const pixel& one, const value_type& another)
        {
            return one.m_value > another;
        }

        /*!
            \brief Adds another value in pixel unit.

            \param another Another value in pixel unit.

            \return This object.
        */
        pixel& add(const value_type& another)
        {
            pixel temp{ *this };

            temp.m_value += another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Subtracts another value in pixel unit.

            \param another Another value in pixel unit.

            \return This object.
        */
        pixel& subtract(const value_type& another)
        {
            pixel temp{ *this };

            temp.m_value -= another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Multiplies another value in pixel unit.

            \param another Another value in pixel unit.

            \return This object.
        */
        pixel& multiply(const value_type& another)
        {
            pixel temp{ *this };

            temp.m_value *= another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Divides by another value in pixel unit.

            \param another Another value in pixel unit.

            \return This object.
        */
        pixel& divide_by(const value_type& another)
        {
            pixel temp{ *this };

            temp.m_value /= another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Divides by another pixel unit.

            \param another Another pixel unit.

            \return A value.
        */
        value_type divide_by(const pixel& another)
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

            \return The value in pixels.
        */
        template <typename PixelValue>
        PixelValue to_pixels()
        const
        {
            return to_pixels_impl<PixelValue>(m_value);
        }


    private:
        // static functions

        template <typename PixelValue, typename Integer>
        static PixelValue to_pixels_impl(
            const Integer                                                    value,
            typename std::enable_if<std::is_integral<Integer>::value>::type* = nullptr
        )
        {
            return static_cast<PixelValue>(value);
        }

        template <typename PixelValue, typename Integer>
        static PixelValue to_pixels_impl(const boost::rational<Integer>& value)
        {
            return boost::rational_cast<PixelValue>(value);
        }


        // variables

        value_type m_value;


    };


}}}

#endif

/*! \file
    \brief The definition of tetengo2::gui::unit::pixel.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_UNIT_PIXEL_H)
#define TETENGO2_GUI_UNIT_PIXEL_H

//#include <utility>

#include <boost/operators.hpp>
#include <boost/swap.hpp>

#include "tetengo2.operators.h"


namespace tetengo2 { namespace gui { namespace unit
{
    /*!
        \brief The class template for a pixel unit.

        \tparam Value      A value type.
        \tparam PixelValue A pixel value type.
   */
    template <typename Value, typename PixelValue>
    class pixel :
        private boost::totally_ordered<pixel<Value, PixelValue>>,
        private boost::totally_ordered<pixel<Value, PixelValue>, Value>,
        private tetengo2::additive<pixel<Value, PixelValue>>,
        private tetengo2::additive<pixel<Value, PixelValue>, Value>
    {
    public:
        // types

        //! The value type.
        typedef Value value_type;

        //! The pixel value type.
        typedef PixelValue pixel_value_type;


        // static functions

        /*!
            \brief Returns a pixel unit made from a value in pixels.

            \param value A value in pixels.

            \return A pixel unit.
        */
        static pixel from_pixels(const pixel_value_type value)
        {
            return pixel(value_type(value));
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

        /*!
            \brief Creates a pixel unit.

            \param value A value.
        */
        explicit pixel(value_type&& value)
        :
        m_value(std::forward<value_type>(value))
        {}


        // functions

        /*!
            \brief Adds another pixel unit.

            \param another Another pixel unit.

            \return This object.
        */
        pixel& operator+=(const pixel& another)
        {
            pixel temp(*this);

            temp.m_value += another.m_value;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Adds another value in pixel unit.

            \param another Another value in pixel unit.

            \return This object.
        */
        pixel& operator+=(const value_type& another)
        {
            pixel temp(*this);

            temp.m_value += another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Subtracts another pixel unit.

            \param another Another pixel unit.

            \return This object.
        */
        pixel& operator-=(const pixel& another)
        {
            pixel temp(*this);

            temp.m_value -= another.m_value;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Subtracts another value in pixel unit.

            \param another Another value in pixel unit.

            \return This object.
        */
        pixel& operator-=(const value_type& another)
        {
            pixel temp(*this);

            temp.m_value -= another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Checks whether one pixel unit is equal to another.

            \param one     One pixel unit.
            \param another Another pixel unit.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const pixel& one, const pixel& another)
        {
            return one.m_value == another.m_value;
        }

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
            \param another Another pixel unit.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        friend bool operator<(const pixel& one, const pixel& another)
        {
            return one.m_value < another.m_value;
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

            \return The value in pixels.
        */
        pixel_value_type to_pixels()
        const
        {
            return static_cast<pixel_value_type>(m_value);
        }


    private:
        // variables

        value_type m_value;


    };


}}}

#endif

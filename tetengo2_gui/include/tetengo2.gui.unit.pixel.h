/*! \file
    \brief The definition of tetengo2::gui::unit::pixel.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_UNIT_PIXEL_H)
#define TETENGO2_GUI_UNIT_PIXEL_H

//#include <utility>

#include <boost/swap.hpp>

#include "tetengo2.gui.unit.unit.h"


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
        typedef Value value_type;


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
            \brief Adds another value in pixel unit.

            \param another Another value in pixel unit.

            \return This object.
        */
        pixel& add(const value_type& another)
        {
            pixel temp(*this);

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
            pixel temp(*this);

            temp.m_value -= another;

            boost::swap(temp, *this);
            return *this;
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

            \tparam PixelValue A pixel value type.

            \return The value in pixels.
        */
        template <typename PixelValue>
        PixelValue to_pixels()
        const
        {
            return static_cast<PixelValue>(m_value);
        }


    private:
        // variables

        value_type m_value;


    };


}}}

#endif

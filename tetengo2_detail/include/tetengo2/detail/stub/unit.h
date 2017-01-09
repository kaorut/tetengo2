/*! \file
    \brief The definition of tetengo2::detail::stub::unit.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_UNIT_H)
#define TETENGO2_DETAIL_STUB_UNIT_H

#include <type_traits>

#include <boost/core/noncopyable.hpp>
#include <boost/rational.hpp>


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a unit.
    */
    class unit : private boost::noncopyable
    {
    public:
        // static functions

        /*!
            \brief Translates a value in pixels into a value in ems.

            \tparam Value      A value type.
            \tparam PixelValue A pixel value type.

            \param pixel_value A value in pixels.

            \return The value in ems.
        */
        template <typename Value, typename PixelValue>
        static Value pixels_to_em(const PixelValue pixel_value)
        {
            return to_value<Value, PixelValue>(pixel_value, 12);
        }

        /*!
            \brief Translates a value in ems into a value in pixels.

            \tparam PixelValue A pixel value type.
            \tparam Value      A value type.

            \param value A value in ems.

            \return The value in pixels.
        */
        template <typename PixelValue, typename Value>
        static PixelValue em_to_pixels(const Value& value)
        {
            return to_pixel_value<PixelValue, Value>(value * 12, 1);
        }

        /*!
            \brief Translates a value in pixels into a value in points.

            \tparam Value      A value type.
            \tparam PixelValue A pixel value type.

            \param pixel_value A value in pixels.

            \return The value in points.
        */
        template <typename Value, typename PixelValue>
        static Value pixels_to_points(const PixelValue pixel_value)
        {
            return to_value<Value, PixelValue>(pixel_value * 3, 4);
        }

        /*!
            \brief Translates a value in points into a value in pixels.

            \tparam PixelValue A pixel value type.
            \tparam Value      A value type.

            \param value A value in points.

            \return The value in pixels.
        */
        template <typename PixelValue, typename Value>
        static PixelValue points_to_pixels(const Value& value)
        {
            return to_pixel_value<PixelValue, Value>(value * 4, 3);
        }


    private:
        // static functions

        template <typename Value, typename PixelValue>
        static Value to_value(
            const PixelValue numerator,
            const PixelValue denominator,
            typename std::enable_if<
                std::is_convertible<boost::rational<typename Value::int_type>, Value>::value
            >::type* = nullptr
        )
        {
            return boost::rational<typename Value::int_type>(numerator, denominator);
        }

        template <typename Value, typename PixelValue>
        static Value to_value(
            const PixelValue numerator,
            const PixelValue denominator,
            typename std::enable_if<std::is_arithmetic<Value>::value>::type* = nullptr
        )
        {
            return numerator / denominator;
        }

        template <typename PixelValue, typename Value>
        static PixelValue to_pixel_value(
            const Value& numerator,
            const Value& denominator,
            typename std::enable_if<
                std::is_convertible<boost::rational<typename Value::int_type>, Value>::value
            >::type* = nullptr
        )
        {
            return boost::rational_cast<PixelValue>(numerator / denominator);
        }

        template <typename PixelValue, typename Value>
        static PixelValue to_pixel_value(
            const Value numerator,
            const Value denominator,
            typename std::enable_if<std::is_arithmetic<Value>::value>::type* = nullptr
        )
        {
            return static_cast<PixelValue>(numerator / denominator);
        }


        // forbidden operations

        unit()
        = delete;


    };


}}}


#endif

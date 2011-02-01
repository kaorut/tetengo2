/*! \file
    \brief The definition of tetengo2::detail::windows::unit.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_UNIT_H)
#define TETENGO2_DETAIL_WINDOWS_UNIT_H

#include <cstddef>
#include <type_traits>

#include <boost/rational.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.gui.drawing.win32.detail.font.h"


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of a unit.
    */
    class unit
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
            const ::LOGFONTW& message_font =
                tetengo2::gui::drawing::win32::detail::get_message_font();
            return to_value<Value, PixelValue>(pixel_value, -message_font.lfHeight);
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
            const ::LOGFONTW& message_font =
                tetengo2::gui::drawing::win32::detail::get_message_font();
            return to_pixel_value<PixelValue, Value>(value * -message_font.lfHeight);
        }


    private:
        // static functions

        template <typename Value, typename PixelValue>
        static Value to_value(
            const PixelValue numerator,
            const PixelValue denominator,
            typename std::enable_if<
                std::is_convertible<
                    boost::rational<typename Value::int_type>, Value
                >::value
            >::type* = NULL
        )
        {
            return boost::rational<typename Value::int_type>(
                numerator, denominator
            );
        }

        template <typename Value, typename PixelValue>
        static Value to_value(
            const PixelValue numerator,
            const PixelValue denominator,
            typename std::enable_if<std::is_arithmetic<Value>::value>::type* =
                NULL
        )
        {
            return numerator / denominator;
        }

        template <typename PixelValue, typename Value>
        static PixelValue to_pixel_value(
            const Value& value,
            typename std::enable_if<
                std::is_convertible<
                    boost::rational<typename Value::int_type>, Value
                >::value
            >::type* = NULL
        )
        {
            return boost::rational_cast<PixelValue>(value);
        }

        template <typename PixelValue, typename Value>
        static PixelValue to_pixel_value(
            const Value value,
            typename std::enable_if<std::is_arithmetic<Value>::value>::type* =
                NULL
        )
        {
            return static_cast<PixelValue>(value);
        }


        // forbidden operations

        unit();


   };


}}}


#endif

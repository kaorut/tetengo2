/*! \file
    \brief The definition of tetengo2::detail::windows::unit.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_UNIT_H)
#define TETENGO2_DETAIL_WINDOWS_UNIT_H

#include <cassert>
#include <system_error>
#include <type_traits>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/rational.hpp>
#include <boost/scope_exit.hpp>
#include <boost/throw_exception.hpp>

//#pragma warning (push)
//#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
//#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/detail/windows/font.h>


namespace tetengo2 { namespace detail { namespace windows
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
            const auto& message_font = get_message_font();
            return to_value<Value, PixelValue>(pixel_value, static_cast<PixelValue>(-message_font.lfHeight));
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
            const auto& message_font = get_message_font();
            return to_pixel_value<PixelValue, Value>(value * -message_font.lfHeight, 1);
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
            return to_value<Value, PixelValue>(pixel_value * 72, dpi().second);
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
            return to_pixel_value<PixelValue, Value>(value * dpi().second, 72);
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
            return boost::rational<typename Value::int_type>(
                static_cast<typename Value::int_type>(numerator), static_cast<typename Value::int_type>(denominator)
            );
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

        static const std::pair<int, int>& dpi()
        {
            static const auto singleton = get_dpi();
            return singleton;
        }

        static std::pair<int, int> get_dpi()
        {
            const auto device_context = ::GetDC(nullptr);
            if (!device_context)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{
                        std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                        "Can't get the desktop device context."
                    }
                ));
            }
            BOOST_SCOPE_EXIT((device_context))
            {
                ::ReleaseDC(nullptr, device_context);
            } BOOST_SCOPE_EXIT_END;

            const auto dpi_x = ::GetDeviceCaps(device_context, LOGPIXELSX);
            assert(dpi_x != 0);
            const auto dpi_y = ::GetDeviceCaps(device_context, LOGPIXELSY);
            assert(dpi_y != 0);
            return std::make_pair(dpi_x, dpi_y);
        }


        // forbidden operations

        unit()
        = delete;


   };


}}}


#endif

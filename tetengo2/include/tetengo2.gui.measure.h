/*! \file
    \brief The definition of tetengo2::gui::measure.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MEASURE_H)
#define TETENGO2_GUI_MEASURE_H

#include <cstddef>
#include <type_traits>
#include <utility>


namespace tetengo2 { namespace gui
{
    /*!
        \brief Converts a value in a certain unit to pixels.

        \tparam PixelValue A pixel value type.
        \tparam Unit       A unit type.

        \param value A value in a certain unit.

        \return The converted value in pixels.
    */
    template <typename PixelValue, typename Unit>
    PixelValue to_pixels(
        const Unit& value,
        typename std::enable_if<
            !std::is_arithmetic<Unit>::value
        >::type* = NULL
    )
    {
        return static_cast<PixelValue>(value.to_pixels());
    }

    /*!
        \brief Converts a value in pixels to a certain unit.

        \tparam Unit       A unit type.
        \tparam PixelValue A pixel value type.

        \param value A value in pixels.

        \return The converted value in a certain unit.
    */
    template <typename Unit, typename PixelValue>
    Unit to_unit(
        const PixelValue value,
        typename std::enable_if<
            !std::is_arithmetic<Unit>::value
        >::type* = NULL
    )
    {
        return Unit::from_pixels(
            static_cast<typename Unit::pixel_value_type>(value)
        );
    }

#if !defined(DOCUMENTATION)
    template <typename PixelValue, typename Unit>
    PixelValue to_pixels(
        const Unit& value,
        typename std::enable_if<std::is_arithmetic<Unit>::value>::type* = NULL
    )
    {
        return static_cast<PixelValue>(value);
    }

    template <typename Unit, typename PixelValue>
    Unit to_unit(
        const PixelValue value,
        typename std::enable_if<std::is_arithmetic<Unit>::value>::type* = NULL
    )
    {
        return static_cast<Unit>(value);
    }
#endif

    /*!
        \brief Returns the left.

        \tparam T A type.

        \param position A position.

        \return The left.
    */
    template <typename T>
    T left(const std::pair<T, T>& position)
    {
        return position.first;
    }

    /*!
        \brief Returns the top.

        \tparam T A type.

        \param position A position.

        \return The top.
    */
    template <typename T>
    T top(const std::pair<T, T>& position)
    {
        return position.second;
    }

    /*!
        \brief Returns the width.

        \tparam T A type.

        \param dimension A dimension.

        \return The width.
    */
    template <typename T>
    T width(const std::pair<T, T>& dimension)
    {
        return dimension.first;
    }

    /*!
        \brief Returns the height.

        \tparam T A type.

        \param dimension A dimension.

        \return The height.
    */
    template <typename T>
    T height(const std::pair<T, T>& dimension)
    {
        return dimension.second;
    }


}}


#endif

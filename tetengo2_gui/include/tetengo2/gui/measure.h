/*! \file
    \brief The definition of measurement utilities for tetengo2::gui.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MEASURE_H)
#define TETENGO2_GUI_MEASURE_H

#include <cmath>
#include <type_traits>

#include <boost/rational.hpp>


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
    PixelValue to_pixels(const Unit& value, typename std::enable_if<!std::is_arithmetic<Unit>::value>::type* = nullptr)
    {
        return value.template to_pixels<PixelValue>();
    }

    /*!
        \brief Converts a value in pixels to a certain unit.

        \tparam Unit       A unit type.
        \tparam PixelValue A pixel value type.

        \param value A value in pixels.

        \return The converted value in a certain unit.
    */
    template <typename Unit, typename PixelValue>
    Unit to_unit(const PixelValue value, typename std::enable_if<!std::is_arithmetic<Unit>::value>::type* = nullptr)
    {
        return Unit::from_pixels(value);
    }

    /*!
        \brief Returns the ceiling integer.

        \tparam Integer A integer type.
        \tparam Unit    A unit type.

        \param value A value in a certain unit.

        \return The ceiling integer.
    */
    template <typename Integer, typename Unit>
    Integer ceil(const Unit& value, typename std::enable_if<!std::is_arithmetic<Unit>::value>::type* = nullptr)
    {
        return static_cast<Integer>(std::ceil(boost::rational_cast<double, Integer>(value.value())));
    }

    /*!
        \brief Returns the floor integer.

        \tparam Integer A integer type.
        \tparam Unit    A unit type.

        \param value A value in a certain unit.

        \return The floor integer.
    */
    template <typename Integer, typename Unit>
    Integer floor(const Unit& value, typename std::enable_if<!std::is_arithmetic<Unit>::value>::type* = nullptr)
    {
        return static_cast<Integer>(std::floor(boost::rational_cast<double>(value.value())));
    }

#if !defined(DOCUMENTATION)
    template <typename PixelValue, typename Unit>
    PixelValue to_pixels(const Unit& value, typename std::enable_if<std::is_arithmetic<Unit>::value>::type* = nullptr)
    {
        return static_cast<PixelValue>(value);
    }

    template <typename Unit, typename PixelValue>
    Unit to_unit(const PixelValue value, typename std::enable_if<std::is_arithmetic<Unit>::value>::type* = nullptr)
    {
        return static_cast<Unit>(value);
    }

    template <typename Integer, typename Unit>
    Integer ceil(const Unit& value, typename std::enable_if<std::is_arithmetic<Unit>::value>::type* = nullptr)
    {
        return static_cast<Integer>(std::ceil(static_cast<double>(value)));
    }

    template <typename Integer, typename Unit>
    Integer floor(const Unit& value, typename std::enable_if<std::is_arithmetic<Unit>::value>::type* = nullptr)
    {
        return static_cast<Integer>(std::floor(static_cast<double>(value)));
    }
#endif


}}


#endif

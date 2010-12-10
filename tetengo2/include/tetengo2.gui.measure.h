/*! \file
    \brief The definition of tetengo2::gui::measure.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MEASURE_H)
#define TETENGO2_GUI_MEASURE_H

#include <type_traits>


namespace tetengo2 { namespace gui
{
    /*!
        \brief Converts a value in a certain unit to pixels.

        \tparam Unit A unit type.

        \param value A value.

        \return The converted value in pixels.
    */
    template <typename Unit>
    typename Unit::pixel_value_type to_pixels(
        const Unit& value,
        typename std::enable_if<
            !std::is_arithmetic<Unit>::value
        >::type* = NULL
    )
    {
        return value.to_pixels();
    }

#if !defined(DOCUMENTATION)
    template <typename Unit>
    Unit to_pixels(
        const Unit& value,
        typename std::enable_if<
            std::is_arithmetic<Unit>::value
        >::type* = NULL
    )
    {
        return value;
    }
#endif


}}


#endif

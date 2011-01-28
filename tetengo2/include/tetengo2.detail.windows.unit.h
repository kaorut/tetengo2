/*! \file
    \brief The definition of tetengo2::detail::windows::unit.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_UNIT_H)
#define TETENGO2_DETAIL_WINDOWS_UNIT_H

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.gui.drawing.win32.detail.font.h"


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of a unit.

        \tparam Pivot A pivot type.
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
            return static_cast<Value>(pixel_value);
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
            return static_cast<PixelValue>(value);
        }



    private:
        // forbidden operations

        unit();


   };


}}}


#endif

/*! \file
    \brief The definition of tetengo2::detail::stub::unit.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_UNIT_H)
#define TETENGO2_DETAIL_STUB_UNIT_H

#include <boost/noncopyable.hpp>


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
            return static_cast<Value>(pixel_value / 12);
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
            return static_cast<PixelValue>(value * 12);
        }


    private:
        // forbidden operations

        unit();


    };


}}}


#endif

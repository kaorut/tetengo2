/*! \file
    \brief The definition of tetengo2::detail::stub::unit.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_UNIT_H)
#define TETENGO2_DETAIL_STUB_UNIT_H


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a unit.
    */
    class unit
    {
    public:
        // static functions

        template <typename Value, typename PixelValue>
        static Value pixels_to_em(const PixelValue pixel_value)
        {
            return static_cast<Value>(pixel_value);
        }

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

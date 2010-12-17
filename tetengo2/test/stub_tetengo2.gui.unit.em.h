/*! \file
    \brief The definition of tetengo2::gui::unit::em.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_UNIT_EM_H)
#define STUBTETENGO2_GUI_UNIT_EM_H

//#include <utility>

#include <boost/operators.hpp>
#include <boost/swap.hpp>

#include "tetengo2.operators.h"


namespace stub_tetengo2 { namespace gui { namespace unit
{
    template <typename Value, typename PixelValue>
    class em :
        private boost::totally_ordered<em<Value, PixelValue>>,
        private tetengo2::additive<em<Value, PixelValue>>
    {
    public:
        // types

        typedef Value value_type;

        typedef PixelValue pixel_value_type;


        // static functions

        static em from_pixels(const pixel_value_type value)
        {
            return em(value_type(value));
        }


        // constructors and destructor

        explicit em(const value_type& value)
        :
        m_value(value)
        {}

        explicit em(value_type&& value)
        :
        m_value(std::forward<value_type>(value))
        {}


        // functions

        em& operator+=(const em& another)
        {
            em temp(*this);

            temp.m_value += another.m_value;
            
            boost::swap(temp, *this);
            return *this;
        }

        em& operator-=(const em& another)
        {
            em temp(*this);

            temp.m_value -= another.m_value;
            
            boost::swap(temp, *this);
            return *this;
        }

        friend bool operator==(const em& one, const em& another)
        {
            return one.m_value == another.m_value;
        }

        friend bool operator<(const em& one, const em& another)
        {
            return one.m_value < another.m_value;
        }

        const value_type& value()
        const
        {
            return m_value;
        }

        pixel_value_type to_pixels()
        const
        {
            return static_cast<pixel_value_type>(m_value);
        }


    private:
        // variables

        value_type m_value;


    };


}}}

#endif

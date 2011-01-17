/*! \file
    \brief The definition of stub_tetengo2::gui::drawing::color.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_DRAWING_COLOR_H)
#define STUBTETENGO2_GUI_DRAWING_COLOR_H

#include <limits>

#include <boost/operators.hpp>


namespace stub_tetengo2 { namespace gui { namespace drawing
{
    template <typename Value>
    class color : private boost::equality_comparable<color<Value>>
    {
    public:
        // types

        typedef Value value_type;


        // constructors and destructor

        color(
            const value_type red,
            const value_type green,
            const value_type blue,
            const value_type alpha = std::numeric_limits<value_type>::max()
        )
        :
        m_red(red),
        m_green(green),
        m_blue(blue),
        m_alpha(alpha)
        {}


        // functions

        friend bool operator==(const color& one, const color& another)
        {
            return one.m_red == another.m_red &&
                   one.m_green == another.m_green &&
                   one.m_blue == another.m_blue &&
                   one.m_alpha == another.m_alpha;
        }

        value_type red()
        const
        {
            return m_red;
        }

        value_type green()
        const
        {
            return m_green;
        }

        value_type blue()
        const
        {
            return m_blue;
        }

        value_type alpha()
        const
        {
            return m_alpha;
        }


    private:
        // variables

        value_type m_red;

        value_type m_green;

        value_type m_blue;

        value_type m_alpha;


    };


}}}


#endif

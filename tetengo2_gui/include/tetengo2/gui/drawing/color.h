/*! \file
    \brief The definition of tetengo2::gui::drawing::color.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_COLOR_H)
#define TETENGO2_GUI_DRAWING_COLOR_H

#include <limits>

#include <boost/operators.hpp>


namespace tetengo2 { namespace gui { namespace drawing
{
    /*!
        \brief The class template for a basic color.

        \tparam Value A value type.
    */
    template <typename Value>
    class basic_color : private boost::equality_comparable<basic_color<Value>>
    {
    public:
        // types

        //! The value type.
        using value_type = Value;


        // constructors and destructor

        /*!
            \brief Creates a basic color.

            \param red   A red value.
            \param green A green value.
            \param blue  A blue value.
            \param alpha An alpha channel value.
        */
        basic_color(
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

        /*!
            \brief Checks whether one basic color is equal to another.

            \param one     One color.
            \param another Another basic color.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const basic_color& one, const basic_color& another)
        {
            return
                one.m_red == another.m_red &&
                one.m_green == another.m_green &&
                one.m_blue == another.m_blue &&
                one.m_alpha == another.m_alpha;
        }

        /*!
            \brief Returns the red value.

            \return The red value.
        */
        value_type red()
        const
        {
            return m_red;
        }

        /*!
            \brief Returns the green value.

            \return The green value.
        */
        value_type green()
        const
        {
            return m_green;
        }

        /*!
            \brief Returns the blue value.

            \return The blue value.
        */
        value_type blue()
        const
        {
            return m_blue;
        }

        /*!
            \brief Returns the alpha channel value.

            \return The alpha channel value.
        */
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


    //! The type for a color.
    using color = basic_color<unsigned char>;


}}}


#endif

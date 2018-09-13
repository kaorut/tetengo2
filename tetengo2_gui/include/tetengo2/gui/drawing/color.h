/*! \file
    \brief The definition of tetengo2::gui::drawing::color.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_COLOR_H)
#define TETENGO2_GUI_DRAWING_COLOR_H

#include <limits>

#include <boost/operators.hpp>


namespace tetengo2::gui::drawing {
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
            const value_type alpha = std::numeric_limits<value_type>::max());


        // functions

        /*!
            \brief Checks whether one basic color is equal to another.

            \tparam V A value type.

            \param one     One color.
            \param another Another basic color.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        template <typename V>
        friend bool operator==(const basic_color<V>& one, const basic_color<V>& another);

        /*!
            \brief Returns the red value.

            \return The red value.
        */
        value_type red() const;

        /*!
            \brief Returns the green value.

            \return The green value.
        */
        value_type green() const;

        /*!
            \brief Returns the blue value.

            \return The blue value.
        */
        value_type blue() const;

        /*!
            \brief Returns the alpha channel value.

            \return The alpha channel value.
        */
        value_type alpha() const;

        /*!
            \brief Mixes a color.

            \param another Another color.
            \param weight  The weight of another color. It must be between 0.0 and 1.0.

            \return The mixed color.

            \throw std::invalid_argument When weight is less than 0.0 or greater than 1.0.
        */
        basic_color mix(const basic_color& another, const double weight) const;


    private:
        // variables

        value_type m_red;

        value_type m_green;

        value_type m_blue;

        value_type m_alpha;
    };


    //! The type for a color.
    using color = basic_color<unsigned char>;
}


#endif

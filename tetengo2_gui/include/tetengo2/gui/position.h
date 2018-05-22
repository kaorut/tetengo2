/*! \file
    \brief The definition of tetengo2::gui::basic_position.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_POSITION_H)
#define TETENGO2_GUI_POSITION_H

#include <boost/operators.hpp>

#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/gui/unit/point.h>


namespace tetengo2::gui {
    /*!
        \brief The class for a position.

        \tparam Unit A unit type.
    */
    template <typename Unit>
    class basic_position : private boost::equality_comparable<basic_position<Unit>>
    {
    public:
        // types

        //! The unit type.
        using unit_type = Unit;


        // constructors and destructor

        /*!
            \brief Creates a basic_position with zeros.
        */
        basic_position();

        /*!
            \brief Creates a basic_position.

            \param left A left.
            \param top  A top.
        */
        basic_position(unit_type left, unit_type top);


        // functions

        /*!
            \brief Checks whether one basic_position is equal to another.

            \tparam U A unit type.

            \param one     One basic_position.
            \param another Another basic_position.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        template <typename U>
        friend bool operator==(const basic_position<U>& one, const basic_position<U>& another);

        /*!
            \brief Returns the left.

            \return The left.
        */
        const unit_type& left() const;

        /*!
            \brief Returns the top.

            \return The top.
        */
        const unit_type& top() const;


    private:
        // variables

        unit_type m_left;

        unit_type m_top;
    };


    //! The EM-based position type.
    using em_position = basic_position<unit::em>;

    //! The pixel-based position type.
    using pixel_position = basic_position<unit::pixel>;

    //! The point-based position type.
    using point_position = basic_position<unit::point>;
}


#endif

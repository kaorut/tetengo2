/*! \file
    \brief The definition of tetengo2::gui::position.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_POSITION_H)
#define TETENGO2_GUI_POSITION_H

#include <boost/operators.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class for a position.

        \tparam Unit A unit type.
    */
    template <typename Unit>
    class position : private boost::equality_comparable<position<Unit>>
    {
    public:
        // types

        //! The unit type.
        using unit_type = Unit;


        // constructors and destructor

        /*!
            \brief Creates a position with zeros.
        */
        position();

        /*!
            \brief Creates a position.

            \param left A left.
            \param top  A top.
        */
        position(unit_type left, unit_type top);


        // functions

        /*!
            \brief Checks whether one position is equal to another.

            \tparam U A unit type.

            \param one     One position.
            \param another Another position.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        template <typename U>
        friend bool operator==(const position<U>& one, const position<U>& another);

        /*!
            \brief Returns the left.

            \return The left.
        */
        const unit_type& left()
        const;

        /*!
            \brief Returns the top.

            \return The top.
        */
        const unit_type& top()
        const;


    private:
        // variables

        unit_type m_left;

        unit_type m_top;


    };


}}


#endif

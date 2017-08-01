/*! \file
    \brief The definition of tetengo2::gui::position.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_POSITION_H)
#define TETENGO2_GUI_POSITION_H

#include <boost/operators.hpp>
#include <boost/rational.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class for a position.
    */
    class position : private boost::equality_comparable<position>
    {
    public:
        // types

        //! The value type.
        using value_type = boost::rational<type_list::integer_type>;


        // constructors and destructor

        /*!
            \brief Creates a position.

            \param left A left.
            \param top  A top.
        */
        position(value_type left, value_type top);


        // functions

        /*!
            \brief Checks whether one position is equal to another.

            \param one     One position.
            \param another Another position.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const position& one, const position& another);

        /*!
            \brief Returns the left.

            \return The left.
        */
        const value_type& left()
        const;

        /*!
            \brief Returns the top.

            \return The top.
        */
        const value_type& top()
        const;


    private:
        // variables

        value_type m_left;

        value_type m_top;


    };


}}


#endif

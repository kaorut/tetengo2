/*! \file
    \brief The definition of tetengo2::gui::position.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_POSITION_H)
#define TETENGO2_GUI_POSITION_H

#include <boost/rational.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class for a position.
    */
    class position
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


    private:
        // variables

        value_type m_left;

        value_type m_top;


    };


}}


#endif

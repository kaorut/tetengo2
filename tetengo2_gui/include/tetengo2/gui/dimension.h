/*! \file
    \brief The definition of tetengo2::gui::dimension.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DIMENSION_H)
#define TETENGO2_GUI_DIMENSION_H

#include <boost/rational.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class for a dimension.
    */
    class dimension
    {
    public:
        // types

        //! The value type.
        using value_type = boost::rational<type_list::size_type>;


        // constructors and destructor

        /*!
            \brief Creates a dimension.

            \param width  A width.
            \param height A height.
        */
        dimension(value_type width, value_type height);


    private:
        // variables

        value_type m_width;

        value_type m_height;


    };


}}


#endif

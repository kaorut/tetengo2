/*! \file
    \brief The definition of tetengo2::gui::dimension.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DIMENSION_H)
#define TETENGO2_GUI_DIMENSION_H

#include <boost/operators.hpp>
#include <boost/rational.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class for a dimension.
    */
    class dimension : private boost::equality_comparable<dimension>
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


        // functions

        /*!
            \brief Checks whether one dimension is equal to another.

            \param one     One dimension.
            \param another Another dimension.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const dimension& one, const dimension& another);

        /*!
            \brief Returns the width.

            \return The width.
        */
        const value_type& width()
        const;

        /*!
            \brief Returns the height.

            \return The height.
        */
        const value_type& height()
        const;


    private:
        // variables

        value_type m_width;

        value_type m_height;


    };


}}


#endif

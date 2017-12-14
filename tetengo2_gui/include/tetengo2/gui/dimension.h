/*! \file
    \brief The definition of tetengo2::gui::dimension.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DIMENSION_H)
#define TETENGO2_GUI_DIMENSION_H

#include <boost/operators.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a dimension.

        \tparam Unit A unit type.
    */
    template <typename Unit>
    class dimension : private boost::equality_comparable<dimension<Unit>>
    {
    public:
        // types

        //! The unit type.
        using unit_type = Unit;


        // constructors and destructor

        /*!
            \brief Creates a dimension with zeros.
        */
        dimension();

        /*!
            \brief Creates a dimension.

            \param width  A width.
            \param height A height.
        */
        dimension(unit_type width, unit_type height);


        // functions

        /*!
            \brief Checks whether one dimension is equal to another.

            \tparam U A unit type.

            \param one     One dimension.
            \param another Another dimension.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        template <typename U>
        friend bool operator==(const dimension<U>& one, const dimension<U>& another);

        /*!
            \brief Returns the width.

            \return The width.
        */
        const unit_type& width()
        const;

        /*!
            \brief Returns the height.

            \return The height.
        */
        const unit_type& height()
        const;


    private:
        // variables

        unit_type m_width;

        unit_type m_height;


    };


}}


#endif

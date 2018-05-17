/*! \file
    \brief The definition of tetengo2::gui::basic_dimension.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DIMENSION_H)
#define TETENGO2_GUI_DIMENSION_H

#include <boost/operators.hpp>
#include <boost/predef.h>

#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/gui/unit/point.h>


namespace tetengo2::gui {
    /*!
        \brief The class template for a dimension.

        \tparam Unit A unit type.
    */
    template <typename Unit>
    class basic_dimension : private boost::equality_comparable<basic_dimension<Unit>>
    {
    public:
        // types

        //! The unit type.
        using unit_type = Unit;


        // constructors and destructor

        /*!
            \brief Creates a dimension with zeros.
        */
        basic_dimension();

        /*!
            \brief Creates a dimension.

            \param width  A width.
            \param height A height.
        */
        basic_dimension(unit_type width, unit_type height);


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
        friend bool operator==(const basic_dimension<U>& one, const basic_dimension<U>& another);

        /*!
            \brief Returns the width.

            \return The width.
        */
        const unit_type& width() const;

        /*!
            \brief Returns the height.

            \return The height.
        */
        const unit_type& height() const;


    private:
        // variables

        unit_type m_width;

        unit_type m_height;
    };


    //! The pixel-based dimension type.
    using pixel_dimension = basic_dimension<unit::upixel>;

#if BOOST_OS_WINDOWS
    //! The EM-based dimension type.
    using em_dimension = basic_dimension<unit::uem>;

    //! The point-based dimension type.
    using point_dimension = basic_dimension<unit::upoint>;
#elif BOOST_OS_LINUX
    //! The EM-based dimension type.
    using em_dimension = basic_dimension<unit::uem_for_test>;

    //! The point-based dimension type.
    using point_dimension = basic_dimension<unit::upoint_for_test>;
#else
#error Unsupported platform.
#endif
}


#endif

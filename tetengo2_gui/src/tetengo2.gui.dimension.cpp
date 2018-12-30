/*! \file
    \brief The definition of tetengo2::gui::dimension.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/gui/unit/point.h>


namespace tetengo2::gui {
    template <typename Unit>
    basic_dimension<Unit>::basic_dimension() : m_width{ unit_type{} }, m_height{ unit_type{} }
    {}

    template <typename Unit>
    basic_dimension<Unit>::basic_dimension(unit_type width, unit_type height)
    : m_width{ std::move(width) }, m_height{ std::move(height) }
    {}

    template <typename U>
    bool operator==(const basic_dimension<U>& one, const basic_dimension<U>& another)
    {
        return one.m_width == another.m_width && one.m_height == another.m_height;
    }

    template <typename Unit>
    const typename basic_dimension<Unit>::unit_type& basic_dimension<Unit>::width() const
    {
        return m_width;
    }

    template <typename Unit>
    const typename basic_dimension<Unit>::unit_type& basic_dimension<Unit>::height() const
    {
        return m_height;
    }


    namespace {
        using em_unit_type = gui::unit::uem;

        using pixel_unit_type = gui::unit::upixel;

        using point_unit_type = gui::unit::upoint;
    }

    template class basic_dimension<em_unit_type>;

    template bool operator==(const basic_dimension<em_unit_type>& one, const basic_dimension<em_unit_type>& another);

    template class basic_dimension<pixel_unit_type>;

    template bool
    operator==(const basic_dimension<pixel_unit_type>& one, const basic_dimension<pixel_unit_type>& another);

    template class basic_dimension<point_unit_type>;

    template bool
    operator==(const basic_dimension<point_unit_type>& one, const basic_dimension<point_unit_type>& another);
}

/*! \file
    \brief The definition of tetengo2::gui::basic_position.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <tetengo2/gui/position.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/gui/unit/point.h>


namespace tetengo2::gui {
    template <typename Unit>
    basic_position<Unit>::basic_position() : m_left{ unit_type{} }, m_top{ unit_type{} }
    {}

    template <typename Unit>
    basic_position<Unit>::basic_position(unit_type left, unit_type top)
    : m_left{ std::move(left) }, m_top{ std::move(top) }
    {}

    template <typename U>
    bool operator==(const basic_position<U>& one, const basic_position<U>& another)
    {
        return one.m_left == another.m_left && one.m_top == another.m_top;
    }

    template <typename Unit>
    const typename basic_position<Unit>::unit_type& basic_position<Unit>::left() const
    {
        return m_left;
    }

    template <typename Unit>
    const typename basic_position<Unit>::unit_type& basic_position<Unit>::top() const
    {
        return m_top;
    }


    namespace {
        using em_unit_type = gui::unit::em;

        using pixel_unit_type = gui::unit::pixel;

        using point_unit_type = gui::unit::point;
    }

    template class basic_position<em_unit_type>;

    template bool operator==(const basic_position<em_unit_type>& one, const basic_position<em_unit_type>& another);

    template class basic_position<pixel_unit_type>;

    template bool
    operator==(const basic_position<pixel_unit_type>& one, const basic_position<pixel_unit_type>& another);

    template class basic_position<point_unit_type>;

    template bool
    operator==(const basic_position<point_unit_type>& one, const basic_position<point_unit_type>& another);
}

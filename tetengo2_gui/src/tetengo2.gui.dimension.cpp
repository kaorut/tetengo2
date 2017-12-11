/*! \file
    \brief The definition of tetengo2::gui::dimension.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>

#include <boost/predef.h>
#include <boost/rational.hpp>

#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/gui/unit/point.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui
{
    template <typename Unit>
    dimension<Unit>::dimension(unit_type width, unit_type height)
    :
    m_width(std::move(width)),
    m_height(std::move(height))
    {}

    template <typename U>
    bool operator==(const dimension<U>& one, const dimension<U>& another)
    {
        return one.m_width == another.m_width && one.m_height == another.m_height;
    }

    template <typename Unit>
    const typename dimension<Unit>::unit_type& dimension<Unit>::width()
    const
    {
        return m_width;
    }

    template <typename Unit>
    const typename dimension<Unit>::unit_type& dimension<Unit>::height()
    const
    {
        return m_height;
    }


    namespace
    {
        using em_stub_unit_type = gui::unit::uem;

        using pixel_unit_type = gui::unit::upixel;

        using point_stub_unit_type = gui::unit::upoint;

#if BOOST_OS_WINDOWS
        using em_windows_unit_type = gui::unit::uem;

        using point_windows_unit_type = gui::unit::upoint;
#endif

    }

    template class dimension<em_stub_unit_type>;

    template bool operator==(const dimension<em_stub_unit_type>& one, const dimension<em_stub_unit_type>& another);

    template class dimension<pixel_unit_type>;

    template bool operator==(const dimension<pixel_unit_type>& one, const dimension<pixel_unit_type>& another);

    template class dimension<point_stub_unit_type>;

    template bool operator==(
        const dimension<point_stub_unit_type>& one,
        const dimension<point_stub_unit_type>& another
    );

#if BOOST_OS_WINDOWS
    template class dimension<em_windows_unit_type>;

    template bool operator==(
        const dimension<em_windows_unit_type>& one,
        const dimension<em_windows_unit_type>& another
    );

    template class dimension<point_windows_unit_type>;

    template bool operator==(
        const dimension<point_windows_unit_type>& one,
        const dimension<point_windows_unit_type>& another
    );
#endif


}}

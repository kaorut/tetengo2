/*! \file
    \brief The definition of tetengo2::gui::position.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>

#include <boost/predef.h>
#include <boost/rational.hpp>

#include <tetengo2/gui/position.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/gui/unit/point.h>
#include <tetengo2/type_list.h>



namespace tetengo2 { namespace gui
{
    template <typename Unit>
    position<Unit>::position(unit_type left, unit_type top)
    :
    m_left(std::move(left)),
    m_top(std::move(top))
    {}

    template <typename U>
    bool operator==(const position<U>& one, const position<U>& another)
    {
        return one.m_left == another.m_left && one.m_top == another.m_top;
    }

    template <typename Unit>
    const typename position<Unit>::unit_type& position<Unit>::left()
    const
    {
        return m_left;
    }

    template <typename Unit>
    const typename position<Unit>::unit_type& position<Unit>::top()
    const
    {
        return m_top;
    }


    namespace
    {
        using em_stub_unit_type = gui::unit::em;

        using pixel_unit_type = gui::unit::pixel;

        using point_stub_unit_type = gui::unit::point<boost::rational<type_list::difference_type>>;

#if BOOST_OS_WINDOWS
        using em_windows_unit_type = gui::unit::em;

        using point_windows_unit_type = gui::unit::point<boost::rational<type_list::difference_type>>;
#endif

    }

    template class position<em_stub_unit_type>;

    template bool operator==(const position<em_stub_unit_type>& one, const position<em_stub_unit_type>& another);

    template class position<pixel_unit_type>;

    template bool operator==(const position<pixel_unit_type>& one, const position<pixel_unit_type>& another);

    template class position<point_stub_unit_type>;

    template bool operator==(const position<point_stub_unit_type>& one, const position<point_stub_unit_type>& another);

#if BOOST_OS_WINDOWS
    template class position<em_windows_unit_type>;

    template bool operator==(
        const position<em_windows_unit_type>& one,
        const position<em_windows_unit_type>& another
    );

    template class position<point_windows_unit_type>;

    template bool operator==(
        const position<point_windows_unit_type>& one,
        const position<point_windows_unit_type>& another
    );
#endif


}}

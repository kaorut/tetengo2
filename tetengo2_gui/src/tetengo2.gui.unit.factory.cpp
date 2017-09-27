/*! \file
    \brief The definition of tetengo2::gui::unit::factory.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/rational.hpp>

#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/factory.h>
#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/gui/unit/point.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui { namespace unit
{
    template <typename Unit>
    class factory<Unit>::impl : private boost::noncopyable
    {
    public:
        // types

        using unit_type = typename factory::unit_type;

        using value_type = typename factory::value_type;

        using unit_details_type = typename factory::unit_details_type;


        // constructors and destructor;

        explicit impl(const unit_details_type& unit_details)
        :
        m_unit_details(unit_details)
        {}


        // functions

        unit_type make(value_type value)
        const
        {
            return unit_type{ std::move(value), m_unit_details };
        }


    private:
        // variables

        const unit_details_type& m_unit_details;


    };


    template <typename Unit>
    factory<Unit>::factory(const unit_details_type& unit_details)
    :
    m_p_impl(stdalt::make_unique<impl>(unit_details))
    {}

    template <typename Unit>
    factory<Unit>::~factory()
    = default;

    template <typename Unit>
    typename factory<Unit>::unit_type factory<Unit>::make(value_type value)
    const
    {
        return m_p_impl->make(std::move(value));
    }


    namespace
    {
        using size_rational_type = boost::rational<type_list::size_type>;

        using difference_rational_type = boost::rational<type_list::difference_type>;

        using em_size_type = tetengo2::gui::unit::em<size_rational_type>;

        using em_difference_type = tetengo2::gui::unit::em<difference_rational_type>;

        using pixel_size_type = tetengo2::gui::unit::pixel<size_rational_type>;

        using pixel_difference_type = tetengo2::gui::unit::pixel<difference_rational_type>;

        using point_size_type = tetengo2::gui::unit::point<size_rational_type>;

        using point_difference_type = tetengo2::gui::unit::point<difference_rational_type>;

    }

    template class factory<em_size_type>;

    template class factory<em_difference_type>;

    template class factory<pixel_size_type>;

    template class factory<pixel_difference_type>;

    template class factory<point_size_type>;

    template class factory<point_difference_type>;


}}}

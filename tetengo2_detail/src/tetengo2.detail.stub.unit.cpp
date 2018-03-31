/*! \file
    \brief The definition of tetengo2::detail::stub::unit.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/rational.hpp>

#include <tetengo2/detail/stub/unit.h>


namespace tetengo2::detail::stub {
    class unit::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = unit::size_type;

        using difference_type = unit::difference_type;


        // static functions

        static const unit& instance()
        {
            static const unit singleton;
            return singleton;
        }


        // functions

        boost::rational<size_type> pixel_size_to_em_impl(const size_type pixel_size) const
        {
            return boost::rational<size_type>{ pixel_size, 12 };
        }

        boost::rational<difference_type> pixel_difference_to_em_impl(const difference_type pixel_difference) const
        {
            return boost::rational<difference_type>{ pixel_difference, 12 };
        }

        boost::rational<size_type> pixel_size_to_point_impl(const size_type pixel_size) const
        {
            return boost::rational<size_type>{ pixel_size * 3, 4 };
        }

        boost::rational<difference_type> pixel_difference_to_point_impl(const difference_type pixel_difference) const
        {
            return boost::rational<difference_type>{ pixel_difference * 3, 4 };
        }

        size_type em_size_to_pixel_impl(const boost::rational<size_type>& em_size) const
        {
            return boost::rational_cast<size_type>(em_size * boost::rational<size_type>{ 12 });
        }

        difference_type em_difference_to_pixel_impl(const boost::rational<difference_type>& em_difference) const
        {
            return boost::rational_cast<difference_type>(em_difference * boost::rational<difference_type>{ 12 });
        }

        size_type point_size_to_pixel_impl(const boost::rational<size_type>& point_size) const
        {
            return boost::rational_cast<size_type>(
                point_size * boost::rational<size_type>{ 4 } / boost::rational<size_type>{ 3 });
        }

        difference_type point_difference_to_pixel_impl(const boost::rational<difference_type>& point_difference) const
        {
            return boost::rational_cast<difference_type>(
                point_difference * boost::rational<difference_type>{ 4 } / boost::rational<difference_type>{ 3 });
        }
    };


    const unit& unit::instance()
    {
        return impl::instance();
    }

    unit::~unit() = default;

    unit::unit() : m_p_impl{ stdalt::make_unique<impl>() } {}

    boost::rational<unit::size_type> unit::pixel_size_to_em_impl(const size_type pixel_size) const
    {
        return m_p_impl->pixel_size_to_em_impl(pixel_size);
    }

    boost::rational<unit::difference_type>
    unit::pixel_difference_to_em_impl(const difference_type pixel_difference) const
    {
        return m_p_impl->pixel_difference_to_em_impl(pixel_difference);
    }

    boost::rational<unit::size_type> unit::pixel_size_to_point_impl(const size_type pixel_size) const
    {
        return m_p_impl->pixel_size_to_point_impl(pixel_size);
    }

    boost::rational<unit::difference_type>
    unit::pixel_difference_to_point_impl(const difference_type pixel_difference) const
    {
        return m_p_impl->pixel_difference_to_point_impl(pixel_difference);
    }

    unit::size_type unit::em_size_to_pixel_impl(const boost::rational<size_type>& em_size) const
    {
        return m_p_impl->em_size_to_pixel_impl(em_size);
    }

    unit::difference_type unit::em_difference_to_pixel_impl(const boost::rational<difference_type>& em_difference) const
    {
        return m_p_impl->em_difference_to_pixel_impl(em_difference);
    }

    unit::size_type unit::point_size_to_pixel_impl(const boost::rational<size_type>& point_size) const
    {
        return m_p_impl->point_size_to_pixel_impl(point_size);
    }

    unit::difference_type
    unit::point_difference_to_pixel_impl(const boost::rational<difference_type>& point_difference) const
    {
        return m_p_impl->point_difference_to_pixel_impl(point_difference);
    }
}

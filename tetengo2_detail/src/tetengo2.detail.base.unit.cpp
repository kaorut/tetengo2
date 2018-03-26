/*! \file
    \brief The definition of tetengo2::detail::base::unit.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/rational.hpp>

#include <tetengo2/detail/base/unit.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::detail::base {
    class unit::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = unit::size_type;

        using difference_type = unit::difference_type;


        // functions

        boost::rational<size_type> pixel_size_to_em(const size_type pixel_size, const unit& base) const
        {
            return base.pixel_size_to_em_impl(pixel_size);
        }

        boost::rational<difference_type>
        pixel_difference_to_em(const difference_type pixel_difference, const unit& base) const
        {
            return base.pixel_difference_to_em_impl(pixel_difference);
        }

        boost::rational<size_type> pixel_size_to_point(const size_type pixel_size, const unit& base) const
        {
            return base.pixel_size_to_point_impl(pixel_size);
        }

        boost::rational<difference_type>
        pixel_difference_to_point(const difference_type pixel_difference, const unit& base) const
        {
            return base.pixel_difference_to_point_impl(pixel_difference);
        }

        size_type em_size_to_pixel(const boost::rational<size_type>& em_size, const unit& base) const
        {
            return base.em_size_to_pixel_impl(em_size);
        }

        difference_type
        em_difference_to_pixel(const boost::rational<difference_type>& em_difference, const unit& base) const
        {
            return base.em_difference_to_pixel_impl(em_difference);
        }

        size_type point_size_to_pixel(const boost::rational<size_type>& point_size, const unit& base) const
        {
            return base.point_size_to_pixel_impl(point_size);
        }

        difference_type
        point_difference_to_pixel(const boost::rational<difference_type>& point_difference, const unit& base) const
        {
            return base.point_difference_to_pixel_impl(point_difference);
        }
    };


    unit::~unit() = default;

    boost::rational<unit::size_type> unit::pixel_size_to_em(const size_type pixel_size) const
    {
        return m_p_impl->pixel_size_to_em(pixel_size, *this);
    }

    boost::rational<unit::difference_type> unit::pixel_difference_to_em(const difference_type pixel_difference) const
    {
        return m_p_impl->pixel_difference_to_em(pixel_difference, *this);
    }

    boost::rational<unit::size_type> unit::pixel_size_to_point(const size_type pixel_size) const
    {
        return m_p_impl->pixel_size_to_point(pixel_size, *this);
    }

    boost::rational<unit::difference_type> unit::pixel_difference_to_point(const difference_type pixel_difference) const
    {
        return m_p_impl->pixel_difference_to_point(pixel_difference, *this);
    }

    unit::size_type unit::em_size_to_pixel(const boost::rational<size_type>& em_size) const
    {
        return m_p_impl->em_size_to_pixel(em_size, *this);
    }

    unit::difference_type unit::em_difference_to_pixel(const boost::rational<difference_type>& em_difference) const
    {
        return m_p_impl->em_difference_to_pixel(em_difference, *this);
    }

    unit::size_type unit::point_size_to_pixel(const boost::rational<size_type>& point_size) const
    {
        return m_p_impl->point_size_to_pixel(point_size, *this);
    }

    unit::difference_type
    unit::point_difference_to_pixel(const boost::rational<difference_type>& point_difference) const
    {
        return m_p_impl->point_difference_to_pixel(point_difference, *this);
    }

    unit::unit() : m_p_impl{ stdalt::make_unique<impl>() } {}
}

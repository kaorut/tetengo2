/*! \file
    \brief The definition of tetengo2::detail::stub::unit.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/stub/unit.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace detail { namespace stub
{
    class unit::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = unit::size_type;

        using difference_type = unit::difference_type;


        // functions

        boost::rational<size_type> to_em_impl(const size_type pixel_size)
        const
        {
            return boost::rational<size_type>{ pixel_size, 12 };
        }

        boost::rational<difference_type> to_em_impl(const difference_type pixel_difference)
        const
        {
            return boost::rational<difference_type>{ pixel_difference, 12 };
        }

        boost::rational<size_type> to_point_impl(const size_type pixel_size)
        const
        {
            return boost::rational<size_type>{ pixel_size * 3, 4 };
        }

        boost::rational<difference_type> to_point_impl(const difference_type pixel_difference)
        const
        {
            return boost::rational<difference_type>{ pixel_difference * 3, 4 };
        }

        size_type em_to_pixel_impl(const boost::rational<size_type>& em_size)
        const
        {
            return boost::rational_cast<size_type>(em_size * boost::rational<size_type>{ 12 });
        }

        difference_type em_to_pixel_impl(const boost::rational<difference_type>& em_difference)
        const
        {
            return boost::rational_cast<difference_type>(em_difference * boost::rational<difference_type>{ 12 });
        }

        size_type point_to_pixel_impl(const boost::rational<size_type>& point_size)
        const
        {
            return
                boost::rational_cast<size_type>(
                    point_size * boost::rational<size_type>{ 4 } / boost::rational<size_type>{ 3 }
                );
        }

        difference_type point_to_pixel_impl(const boost::rational<difference_type>& point_difference)
        const
        {
            return
                boost::rational_cast<difference_type>(
                    point_difference * boost::rational<difference_type>{ 4 } / boost::rational<difference_type>{ 3 }
                );
        }


    };


    unit::unit()
    :
    m_p_impl(stdalt::make_unique<impl>())
    {}

    boost::rational<unit::size_type> unit::to_em_impl(const size_type pixel_size)
    const
    {
        return m_p_impl->to_em_impl(pixel_size);
    }

    boost::rational<unit::difference_type> unit::to_em_impl(const difference_type pixel_difference)
    const
    {
        return m_p_impl->to_em_impl(pixel_difference);
    }

    boost::rational<unit::size_type> unit::to_point_impl(const size_type pixel_size)
    const
    {
        return m_p_impl->to_point_impl(pixel_size);
    }

    boost::rational<unit::difference_type> unit::to_point_impl(const difference_type pixel_difference)
    const
    {
        return m_p_impl->to_point_impl(pixel_difference);
    }

    unit::size_type unit::em_to_pixel_impl(const boost::rational<size_type>& em_size)
    const
    {
        return m_p_impl->em_to_pixel_impl(em_size);
    }

    unit::difference_type unit::em_to_pixel_impl(const boost::rational<difference_type>& em_difference)
    const
    {
        return m_p_impl->em_to_pixel_impl(em_difference);
    }

    unit::size_type unit::point_to_pixel_impl(const boost::rational<size_type>& point_size)
    const
    {
        return m_p_impl->point_to_pixel_impl(point_size);
    }

    unit::difference_type unit::point_to_pixel_impl(const boost::rational<difference_type>& point_difference)
    const
    {
        return m_p_impl->point_to_pixel_impl(point_difference);
    }


}}}

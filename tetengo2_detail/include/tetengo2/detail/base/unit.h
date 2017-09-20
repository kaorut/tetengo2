/*! \file
    \brief The definition of tetengo2::detail::base::unit.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_UNIT_H)
#define TETENGO2_DETAIL_BASE_UNIT_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/rational.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2 { namespace detail { namespace base
{
    /*!
        \brief The class for a detail implementation of a unit.
    */
    class unit : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = type_list::size_type;

        //! The difference type.
        using difference_type = type_list::difference_type;


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        ~unit();


        // functions

        /*!
            \brief Translates a size in pixels into a size in ems.

            \param pixel_size A size in pixels.

            \return The size in ems.
        */
        boost::rational<size_type> to_em(size_type pixel_size)
        const;

        /*!
            \brief Translates a size in pixels into a size in points.

            \param pixel_size A size in pixels.

            \return The size in points.
        */
        boost::rational<size_type> to_point(size_type pixel_size)
        const;

        /*!
            \brief Translates a size in ems into a size in pixels.

            \param em_size A size in ems.

            \return The size in pixels.
        */
        size_type em_to_pixel(const boost::rational<size_type>& em_size)
        const;

        /*!
            \brief Translates a size in points into a size in pixels.

            \param point_size A size in points.

            \return The size in pixels.
        */
        size_type point_to_pixel(const boost::rational<size_type>& point_size)
        const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        unit();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual boost::rational<size_type> pixel_size_to_em_impl(size_type pixel_size)
        const = 0;

        virtual boost::rational<difference_type> pixel_difference_to_em_impl(difference_type pixel_difference)
        const = 0;

        virtual boost::rational<size_type> pixel_size_to_point_impl(size_type pixel_size)
        const = 0;

        virtual boost::rational<difference_type> pixel_difference_to_point_impl(difference_type pixel_difference)
        const = 0;

        virtual size_type em_size_to_pixel_impl(const boost::rational<size_type>& em_size)
        const = 0;

        virtual difference_type em_difference_to_pixel_impl(const boost::rational<difference_type>& em_difference)
        const = 0;

        virtual size_type point_size_to_pixel_impl(const boost::rational<size_type>& point_size)
        const = 0;

        virtual difference_type point_difference_to_pixel_impl(
            const boost::rational<difference_type>& point_difference
        )
        const = 0;


        // functions

        boost::rational<size_type> pixel_size_to_em(size_type pixel_size)
        const;

        boost::rational<difference_type> pixel_difference_to_em(difference_type pixel_difference)
        const;

        boost::rational<size_type> pixel_size_to_point(size_type pixel_size)
        const;

        boost::rational<difference_type> pixel_difference_to_point(difference_type pixel_difference)
        const;

        size_type em_size_to_pixel(const boost::rational<size_type>& em_size)
        const;

        difference_type em_difference_to_pixel(const boost::rational<difference_type>& em_difference)
        const;

        size_type point_size_to_pixel(const boost::rational<size_type>& point_size)
        const;

        difference_type point_difference_to_pixel(const boost::rational<difference_type>& point_difference)
        const;


    };


}}}


#endif

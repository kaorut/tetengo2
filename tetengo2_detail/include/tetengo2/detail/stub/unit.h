/*! \file
    \brief The definition of tetengo2::detail::stub::unit.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_UNIT_H)
#define TETENGO2_DETAIL_STUB_UNIT_H

#include <memory>

#include <boost/rational.hpp>

#include <tetengo2/detail/base/unit.h>


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a unit.
    */
    class unit : public base::unit
    {
    public:
        // types

        //! The size type.
        using size_type = base::unit::size_type;

        //! The difference type.
        using difference_type = base::unit::difference_type;


        // constructors and destructor

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

        virtual boost::rational<size_type> to_em_impl(size_type pixel_size)
        const override;

        virtual boost::rational<difference_type> to_em_impl(difference_type pixel_difference)
        const override;

        virtual boost::rational<size_type> to_point_impl(size_type pixel_size)
        const override;

        virtual boost::rational<difference_type> to_point_impl(difference_type pixel_difference)
        const override;

        virtual size_type em_to_pixel_impl(const boost::rational<size_type>& em_size)
        const override;

        virtual difference_type em_to_pixel_impl(const boost::rational<difference_type>& em_difference)
        const override;

        virtual size_type point_to_pixel_impl(const boost::rational<size_type>& point_size)
        const override;

        virtual difference_type point_to_pixel_impl(const boost::rational<difference_type>& point_difference)
        const override;


    };


}}}


#endif

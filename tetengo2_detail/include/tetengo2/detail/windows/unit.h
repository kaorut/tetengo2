/*! \file
    \brief The definition of tetengo2::detail::windows::unit.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_UNIT_H)
#define TETENGO2_DETAIL_WINDOWS_UNIT_H

#include <memory>

#include <boost/rational.hpp>

#include <tetengo2/detail/base/unit.h>


namespace tetengo2::detail::windows {
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


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const unit& instance();


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        ~unit();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        unit();


        // virtual functions

        virtual boost::rational<size_type> pixel_size_to_em_impl(size_type pixel_size) const override;

        virtual boost::rational<difference_type>
        pixel_difference_to_em_impl(difference_type pixel_difference) const override;

        virtual boost::rational<size_type> pixel_size_to_point_impl(size_type pixel_size) const override;

        virtual boost::rational<difference_type>
        pixel_difference_to_point_impl(difference_type pixel_difference) const override;

        virtual size_type em_size_to_pixel_impl(const boost::rational<size_type>& em_size) const override;

        virtual difference_type
        em_difference_to_pixel_impl(const boost::rational<difference_type>& em_difference) const override;

        virtual size_type point_size_to_pixel_impl(const boost::rational<size_type>& point_size) const override;

        virtual difference_type
        point_difference_to_pixel_impl(const boost::rational<difference_type>& point_difference) const override;
    };
}


#endif

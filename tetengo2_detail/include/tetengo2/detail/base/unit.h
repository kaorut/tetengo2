/*! \file
    \brief The definition of tetengo2::detail::base::unit.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_UNIT_H)
#define TETENGO2_DETAIL_BASE_UNIT_H

#include <memory>
#include <type_traits>

#include <boost/core/noncopyable.hpp>
#include <boost/rational.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2::detail::base {
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
        virtual ~unit();


        // functions

        /*!
            \brief Translates a value in pixels into a value in ems.

            \tparam Integer An integer type.

            \param pixel_value A value in pixels.

            \return The value in ems.
        */
        template <typename Integer>
        boost::rational<Integer> to_em(const Integer pixel_value) const
        {
            return to_em_impl(pixel_value);
        }

        /*!
            \brief Translates a value in pixels into a value in points.

            \tparam Integer An integer type.

            \param pixel_value A value in pixels.

            \return The value in points.
        */
        template <typename Integer>
        boost::rational<Integer> to_point(const Integer pixel_value) const
        {
            return to_point_impl(pixel_value);
        }

        /*!
            \brief Translates a value in ems into a value in pixels.

            \tparam Integer An integer type.

            \param em_value A value in ems.

            \return The value in pixels.
        */
        template <typename Integer>
        Integer em_to_pixel(const boost::rational<Integer>& em_value) const
        {
            return em_to_pixel_impl(em_value);
        }

        /*!
            \brief Translates a value in points into a value in pixels.

            \tparam Integer An integer type.

            \param point_value A value in points.

            \return The value in pixels.
        */
        template <typename Integer>
        Integer point_to_pixel(const boost::rational<Integer>& point_value) const
        {
            return point_to_pixel_impl(point_value);
        }


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

        virtual boost::rational<size_type> pixel_size_to_em_impl(size_type pixel_size) const = 0;

        virtual boost::rational<difference_type>
        pixel_difference_to_em_impl(difference_type pixel_difference) const = 0;

        virtual boost::rational<size_type> pixel_size_to_point_impl(size_type pixel_size) const = 0;

        virtual boost::rational<difference_type>
        pixel_difference_to_point_impl(difference_type pixel_difference) const = 0;

        virtual size_type em_size_to_pixel_impl(const boost::rational<size_type>& em_size) const = 0;

        virtual difference_type
        em_difference_to_pixel_impl(const boost::rational<difference_type>& em_difference) const = 0;

        virtual size_type point_size_to_pixel_impl(const boost::rational<size_type>& point_size) const = 0;

        virtual difference_type
        point_difference_to_pixel_impl(const boost::rational<difference_type>& point_difference) const = 0;


        // functions

        template <typename Integer>
        boost::rational<Integer> to_em_impl(
            const Integer pixel_value,
            typename std::enable_if<std::is_unsigned<Integer>::value>::type* = nullptr) const
        {
            return pixel_size_to_em(pixel_value);
        }

        template <typename Integer>
        boost::rational<Integer> to_em_impl(
            const Integer pixel_value,
            typename std::enable_if<std::is_signed<Integer>::value>::type* = nullptr) const
        {
            return pixel_difference_to_em(pixel_value);
        }

        template <typename Integer>
        boost::rational<Integer> to_point_impl(
            const Integer pixel_value,
            typename std::enable_if<std::is_unsigned<Integer>::value>::type* = nullptr) const
        {
            return pixel_size_to_point(pixel_value);
        }

        template <typename Integer>
        boost::rational<Integer> to_point_impl(
            const Integer pixel_value,
            typename std::enable_if<std::is_signed<Integer>::value>::type* = nullptr) const
        {
            return pixel_difference_to_point(pixel_value);
        }

        template <typename Integer>
        Integer em_to_pixel_impl(
            const boost::rational<Integer>& em_value,
            typename std::enable_if<std::is_unsigned<Integer>::value>::type* = nullptr) const
        {
            return em_size_to_pixel(em_value);
        }

        template <typename Integer>
        Integer em_to_pixel_impl(
            const boost::rational<Integer>& em_value,
            typename std::enable_if<std::is_signed<Integer>::value>::type* = nullptr) const
        {
            return em_difference_to_pixel(em_value);
        }

        template <typename Integer>
        Integer point_to_pixel_impl(
            const boost::rational<Integer>& point_value,
            typename std::enable_if<std::is_unsigned<Integer>::value>::type* = nullptr) const
        {
            return point_size_to_pixel(point_value);
        }

        template <typename Integer>
        Integer point_to_pixel_impl(
            const boost::rational<Integer>& point_value,
            typename std::enable_if<std::is_signed<Integer>::value>::type* = nullptr) const
        {
            return point_difference_to_pixel(point_value);
        }

        boost::rational<size_type> pixel_size_to_em(size_type pixel_size) const;

        boost::rational<difference_type> pixel_difference_to_em(difference_type pixel_difference) const;

        boost::rational<size_type> pixel_size_to_point(size_type pixel_size) const;

        boost::rational<difference_type> pixel_difference_to_point(difference_type pixel_difference) const;

        size_type em_size_to_pixel(const boost::rational<size_type>& em_size) const;

        difference_type em_difference_to_pixel(const boost::rational<difference_type>& em_difference) const;

        size_type point_size_to_pixel(const boost::rational<size_type>& point_size) const;

        difference_type point_difference_to_pixel(const boost::rational<difference_type>& point_difference) const;
    };
}


#endif

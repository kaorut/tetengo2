/*! \file
    \brief The definition of tetengo2::gui::unit::em.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_UNIT_EM_H)
#define TETENGO2_GUI_UNIT_EM_H

//#include <utility>

#include <boost/operators.hpp>
#include <boost/swap.hpp>

#include "tetengo2.operators.h"


namespace tetengo2 { namespace gui { namespace unit
{
    /*!
        \brief The class template for a EM height unit.

        \tparam Value       A value type.
        \tparam PixelValue  A em value type.
        \tparam UnitDetails A detail implementation type of a unit.
   */
    template <typename Value, typename PixelValue, typename UnitDetails>
    class em :
        private boost::totally_ordered<em<Value, PixelValue, UnitDetails>>,
        private boost::totally_ordered<
            em<Value, PixelValue, UnitDetails>, Value
        >,
        private tetengo2::additive<em<Value, PixelValue, UnitDetails>>,
        private tetengo2::additive<em<Value, PixelValue, UnitDetails>, Value>
    {
    public:
        // types

        //! The value type.
        typedef Value value_type;

        //! The pixel value type.
        typedef PixelValue pixel_value_type;

        //! The detail implementation type of a unit.
        typedef UnitDetails unit_details_type;


        // static functions

        /*!
            \brief Returns an EM height unit made from a value in pixels.

            \param value A value in pixels.

            \return An EM height unit.
        */
        static em from_pixels(const pixel_value_type value)
        {
            return em(
                unit_details_type::template pixels_to_em<value_type>(value)
            );
        }

        /*!
            \brief Returns an EM height unit made from another unit.

            \tparam U A unit type.

            \param value A value in another unit.

            \return An EM height unit.
        */
        template <typename U>
        static em from(const U& value)
        {
            return from_pixels(value.to_pixels());
        }


        // constructors and destructor

        /*!
            \brief Creates an EM height unit.

            \param value A value.
        */
        explicit em(const value_type& value)
        :
        m_value(value)
        {}

        /*!
            \brief Creates an EM height unit.

            \param value A value.
        */
        explicit em(value_type&& value)
        :
        m_value(std::forward<value_type>(value))
        {}


        // functions

        /*!
            \brief Adds another EM height unit.

            \param another Another EM height unit.

            \return This object.
        */
        em& operator+=(const em& another)
        {
            return operator+=(another.m_value);
        }

        /*!
            \brief Adds another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        em& operator+=(const value_type& another)
        {
            em temp(*this);

            temp.m_value += another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Subtracts another EM height unit.

            \param another Another EM height unit.

            \return This object.
        */
        em& operator-=(const em& another)
        {
            return operator-=(another.m_value);
        }

        /*!
            \brief Subtracts another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        em& operator-=(const value_type& another)
        {
            em temp(*this);

            temp.m_value -= another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Checks whether one EM height unit is equal to another.

            \param one     One EM height unit.
            \param another Another EM height unit.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const em& one, const em& another)
        {
            return operator==(one, another.m_value);
        }

        /*!
            \brief Checks whether one EM height unit is equal to another.

            \param one     One EM height unit.
            \param another Another value in EM height unit.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const em& one, const value_type& another)
        {
            return one.m_value == another;
        }

        /*!
            \brief Checks whether one EM height unit is less than another.

            \param one     One EM height unit.
            \param another Another EM height unit.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        friend bool operator<(const em& one, const em& another)
        {
            return operator<(one, another.m_value);
        }

        /*!
            \brief Checks whether one EM height unit is less than another.

            \param one     One EM height unit.
            \param another Another value in EM height unit.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        friend bool operator<(const em& one, const value_type& another)
        {
            return one.m_value < another;
        }

        /*!
            \brief Checks whether one EM height unit is greater than another.

            \param one     One EM height unit.
            \param another Another value in EM height unit.

            \retval true  When the one is greater than the other.
            \retval false Otherwise.
        */
        friend bool operator>(const em& one, const value_type& another)
        {
            return one.m_value > another;
        }

        /*!
            \brief Returns the value.

            \return The value.
        */
        const value_type& value()
        const
        {
            return m_value;
        }

        /*!
            \brief Returns the value in pixels.

            \return The value in ems.
        */
        pixel_value_type to_pixels()
        const
        {
            return unit_details_type::template em_to_pixels<pixel_value_type>(
                m_value
            );
        }


    private:
        // variables

        value_type m_value;


    };


}}}


#endif

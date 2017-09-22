/*! \file
    \brief The definition of tetengo2::gui::unit::em.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_UNIT_EM_H)
#define TETENGO2_GUI_UNIT_EM_H

#include <type_traits>

#include <boost/rational.hpp>
#include <boost/swap.hpp>

#include <tetengo2/detail/base/unit.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui { namespace unit
{
    /*!
        \brief The class template for an EM height unit.

        \tparam Value A value type.
   */
    template <typename Value>
    class em : public unit<em<Value>, Value>
    {
    public:
        // types

        //! The value type.
        using value_type = Value;

        //! The unit details type.
        using unit_details_type = detail::base::unit;


        // static functions

        /*!
            \brief Returns a unit made from another em unit.

            \tparam V  A value type.

            \param another A value in another em unit.

            \return A em unit.
        */
        template <typename V>
        static em from(const em<V>& another)
        {
            return em{ cast<value_type>(another.value()), another.details() };
        }

        /*!
            \brief Returns an EM height unit made from a value in pixels.

            \tparam PixelValue A pixel value type.

            \param value        A value in pixels.
            \param unit_details Unit details.

            \return An EM height unit.
        */
        template <typename PixelValue>
        static em from_pixels(const PixelValue value, const unit_details_type& unit_details)
        {
            return from_pixels_impl(value, unit_details);
        }


        // constructors and destructor

        /*!
            \brief Creates an EM height unit.

            \param value        A value.
            \param unit_details Unit details.
        */
        em(const value_type& value, const unit_details_type& unit_details)
        :
        m_value(value),
        m_p_details(&unit_details)
        {}


        // functions

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
            \brief Adds another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        em& add(const value_type& another)
        {
            em temp{ *this };

            temp.m_value += another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Subtracts another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        em& subtract(const value_type& another)
        {
            em temp{ *this };

            temp.m_value -= another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Multiplies another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        em& multiply(const value_type& another)
        {
            em temp{ *this };

            temp.m_value *= another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Divides by another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        em& divide_by(const value_type& another)
        {
            em temp{ *this };

            temp.m_value /= another;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Divides by another EM height unit.

            \param another Another EM height unit.

            \return A value.
        */
        value_type divide_by(const em& another)
        const
        {
            return value() / another.value();
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

            \tparam PixelValue A pixel value type.

            \return The value in ems.
        */
        template <typename PixelValue>
        PixelValue to_pixels()
        const
        {
            return to_pixels_impl<PixelValue>(m_value, *m_p_details);
        }

        /*!
            \brief Returns the unit details.

            \return The unit details.
        */
        const unit_details_type& details()
        const
        {
            return *m_p_details;
        }


    private:
        // static functions

        template <typename To, typename From>
        static To cast(
            const From from,
            typename std::enable_if<std::is_convertible<From, To>::value>::type* = nullptr
        )
        {
            return static_cast<To>(from);
        }

        template <typename To, typename FromInteger>
        static To cast(const boost::rational<FromInteger>& from)
        {
            return
                To{
                    static_cast<typename To::int_type>(from.numerator()),
                    static_cast<typename To::int_type>(from.denominator())
                };
        }

        template <typename PixelValue>
        static em from_pixels_impl(
            const PixelValue         value,
            const unit_details_type& unit_details,
            typename std::enable_if<std::is_unsigned<PixelValue>::value>::type* = nullptr
        )
        {
            return em{ unit_details.to_em(static_cast<type_list::size_type>(value)), unit_details };
        }

        template <typename PixelValue>
        static em from_pixels_impl(
            const PixelValue         value,
            const unit_details_type& unit_details,
            typename std::enable_if<std::is_signed<PixelValue>::value>::type* = nullptr
        )
        {
            return em{ unit_details.to_em(static_cast<type_list::difference_type>(value)), unit_details };
        }

        template <typename PixelValue>
        static PixelValue to_pixels_impl(
            const value_type&        value,
            const unit_details_type& unit_details,
            typename std::enable_if<std::is_unsigned<PixelValue>::value>::type* = nullptr
        )
        {
            return unit_details.template em_to_pixel<type_list::size_type>(value);
        }

        template <typename PixelValue>
        static PixelValue to_pixels_impl(
            const value_type&        value,
            const unit_details_type& unit_details,
            typename std::enable_if<std::is_signed<PixelValue>::value>::type* = nullptr
        )
        {
            return unit_details.template em_to_pixel<type_list::difference_type>(value);
        }


        // variables

        value_type m_value;

        const unit_details_type* m_p_details;


    };


}}}


#endif

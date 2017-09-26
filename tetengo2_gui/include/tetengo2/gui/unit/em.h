/*! \file
    \brief The definition of tetengo2::gui::unit::em.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_UNIT_EM_H)
#define TETENGO2_GUI_UNIT_EM_H

#include <memory>
#include <type_traits>

#include <boost/core/noncopyable.hpp>
#include <boost/rational.hpp>

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
            return from_pixels_impl(static_cast<typename value_type::int_type>(value), unit_details);
        }


        // constructors and destructor

        /*!
            \brief Creates an EM height unit.

            \param value        A value.
            \param unit_details Unit details.
        */
        em(const value_type& value, const unit_details_type& unit_details);


        // functions

        /*!
            \brief Checks whether one EM height unit is equal to another.

            \tparam V1 A value #1 type.
            \tparam V2 A value #2 type.

            \param one     One EM height unit.
            \param another Another value in EM height unit.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        template <typename V1, typename V2>
        friend bool operator==(const em<V1>& one, const V2& another);

        /*!
            \brief Checks whether one EM height unit is less than another.

            \tparam V1 A value #1 type.
            \tparam V2 A value #2 type.

            \param one     One EM height unit.
            \param another Another value in EM height unit.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        template <typename V1, typename V2>
        friend bool operator<(const em<V1>& one, const V2& another);

        /*!
            \brief Checks whether one EM height unit is greater than another.

            \tparam V1 A value #1 type.
            \tparam V2 A value #2 type.

            \param one     One EM height unit.
            \param another Another value in EM height unit.

            \retval true  When the one is greater than the other.
            \retval false Otherwise.
        */
        template <typename V1, typename V2>
        friend bool operator>(const em<V1>& one, const V2& another);

        /*!
            \brief Adds another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        em& add(const value_type& another);

        /*!
            \brief Subtracts another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        em& subtract(const value_type& another);

        /*!
            \brief Multiplies another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        em& multiply(const value_type& another);

        /*!
            \brief Divides by another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        em& divide_by(const value_type& another);

        /*!
            \brief Divides by another EM height unit.

            \param another Another EM height unit.

            \return A value.
        */
        value_type divide_by(const em& another)
        const;

        /*!
            \brief Returns the value.

            \return The value.
        */
        const value_type& value()
        const;

        /*!
            \brief Returns the value in pixels.

            \tparam PixelValue A pixel value type.

            \return The value in pixels.
        */
        template <typename PixelValue>
        PixelValue to_pixels()
        const
        {
            return static_cast<PixelValue>(to_pixels_impl(m_value, *m_p_details));
        }

        /*!
            \brief Returns the unit details.

            \return The unit details.
        */
        const unit_details_type& details()
        const;


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

        static em from_pixels_impl(const typename value_type::int_type value, const unit_details_type& unit_details);

        static typename value_type::int_type to_pixels_impl(
            const value_type&        value,
            const unit_details_type& unit_details
        );


        // variables

        value_type m_value;

        const unit_details_type* m_p_details;


    };


    /*!
        \brief The class template for an EM height unit factory.

        \tparam Value A value type.
    */
    template <typename Value>
    class em_factory : private boost::noncopyable
    {
    public:
        // types

        //! The value type.
        using value_type = Value;

        //! The unit type.
        using unit_type = em<value_type>;

        //! The unit details type.
        using unit_details_type = detail::base::unit;


        // constructors and destructor;

        /*!
            \brief Creates an EM height unit factory.

            \param unit_details Unit details.
        */
        explicit em_factory(const unit_details_type& unit_details);

        /*!
            \brief Destroys the EM height unit factory.
        */
        ~em_factory();


        // functions

        /*!
            \brief Makes an EM height unit.

            \param value A value.

            \return An EM height unit.
        */
        unit_type make(value_type value)
        const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}}}


#endif

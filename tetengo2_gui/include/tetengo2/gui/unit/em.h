/*! \file
    \brief The definition of tetengo2::gui::unit::basic_em.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_UNIT_EM_H)
#define TETENGO2_GUI_UNIT_EM_H

#include <type_traits>

#include <boost/predef.h>
#include <boost/rational.hpp>

#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/type_list.h>

namespace tetengo2 { namespace detail
{
    namespace stub
    {
        class unit;
    }
#if BOOST_OS_WINDOWS
    namespace windows
    {
        class unit;
    }
#endif
}}


namespace tetengo2 { namespace gui { namespace unit
{
    /*!
        \brief The class template for an EM height unit.

        \tparam Value       A value type.
        \tparam UnitDetails A unit details type.
   */
    template <typename Value, typename UnitDetails>
    class basic_em : public unit<basic_em<Value, UnitDetails>, Value>
    {
    public:
        // types

        //! The value type.
        using value_type = Value;

        //! The unit details type.
        using unit_details_type = UnitDetails;


        // static functions

        /*!
            \brief Returns a unit made from another em unit.

            \tparam V  A value type.

            \param another A value in another em unit.

            \return A em unit.
        */
        template <typename V>
        static basic_em from(const basic_em<V, unit_details_type>& another)
        {
            return basic_em{ cast<value_type>(another.value()) };
        }

        /*!
            \brief Returns an EM height unit made from a value in pixels.

            \tparam PixelValue A pixel value type.

            \param value A value in pixels.

            \return An EM height unit.
        */
        template <typename PixelValue>
        static basic_em from_pixels(const PixelValue value)
        {
            return from_pixels_impl(static_cast<typename value_type::int_type>(value));
        }


        // constructors and destructor

        /*!
            \brief Creates an EM height unit with zero.
        */
        basic_em();

        /*!
            \brief Creates an EM height unit.

            \param value A value.
        */
        explicit basic_em(value_type value);


        // functions

        /*!
            \brief Checks whether one EM height unit is equal to another.

            \tparam V  A value type.
            \tparam UD A unit details_type.

            \param one     One EM height unit.
            \param another Another value in EM height unit.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        template <typename V, typename UD>
        friend bool operator==(const basic_em<V, UD>& one, const V& another);

        /*!
            \brief Checks whether one EM height unit is less than another.

            \tparam V  A value type.
            \tparam UD A unit details_type.

            \param one     One EM height unit.
            \param another Another value in EM height unit.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        template <typename V, typename UD>
        friend bool operator<(const basic_em<V, UD>& one, const V& another);

        /*!
            \brief Checks whether one EM height unit is greater than another.

            \tparam V  A value type.
            \tparam UD A unit details_type.

            \param one     One EM height unit.
            \param another Another value in EM height unit.

            \retval true  When the one is greater than the other.
            \retval false Otherwise.
        */
        template <typename V, typename UD>
        friend bool operator>(const basic_em<V, UD>& one, const V& another);

        /*!
            \brief Adds another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        basic_em& add(const value_type& another);

        /*!
            \brief Subtracts another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        basic_em& subtract(const value_type& another);

        /*!
            \brief Multiplies another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        basic_em& multiply(const value_type& another);

        /*!
            \brief Divides by another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        basic_em& divide_by(const value_type& another);

        /*!
            \brief Divides by another EM height unit.

            \param another Another EM height unit.

            \return A value.
        */
        value_type divide_by(const basic_em& another)
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
            return static_cast<PixelValue>(to_pixels_impl(m_value));
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

        static basic_em from_pixels_impl(const typename value_type::int_type value);

        static typename value_type::int_type to_pixels_impl(const value_type& value);


        // variables

        value_type m_value;


    };


#if BOOST_OS_WINDOWS
    //! The signed em type.
    using em = basic_em<boost::rational<type_list::difference_type>, detail::windows::unit>;

    //! The unsigned em type.
    using uem = basic_em<boost::rational<type_list::size_type>, detail::windows::unit>;
#else
    //! The signed em type.
    using em = basic_em<boost::rational<type_list::difference_type>, detail::stub::unit>;

    //! The unsigned em type.
    using uem = basic_em<boost::rational<type_list::size_type>, detail::stub::unit>;
#endif

    //! The signed em type for testing.
    using em_for_test = basic_em<boost::rational<type_list::difference_type>, detail::stub::unit>;

    //! The unsigned em type for testing.
    using uem_for_test = basic_em<boost::rational<type_list::size_type>, detail::stub::unit>;


}}}


#endif

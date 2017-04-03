/*! \file
    \brief The definition of tetengo2::gui::unit::unit.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_UNIT_UNIT_H)
#define TETENGO2_GUI_UNIT_UNIT_H

#include <boost/operators.hpp>


namespace tetengo2 { namespace gui { namespace unit
{
    /*!
        \brief The class template for a unit.

        \tparam ConcreteUnit A concrete unit type.
   */
    template <typename ConcreteUnit, typename Value>
    class unit :
        private boost::totally_ordered<ConcreteUnit>,
        private boost::totally_ordered<ConcreteUnit, Value>,
        private boost::additive<ConcreteUnit>,
        private boost::additive<ConcreteUnit, Value>,
        private boost::multiplicative<ConcreteUnit, Value>
    {
    public:
        // types

        //! The concrete unit type.
        using concrete_unit_type = ConcreteUnit;

        //! The value type.
        using value_type = Value;


        // static functions

        /*!
            \brief Returns a unit made from another unit.

            \tparam U  A unit type.

            \param value A value in another unit.

            \return A unit.
        */
        template <typename U>
        static concrete_unit_type from(const unit<U, typename U::value_type>& value)
        {
            return concrete_unit_type::from_pixels(static_cast<const U&>(value).template to_pixels<int>());
        }


        // functions

        /*!
            \brief Adds another unit.

            \param another Another unit.

            \return This object.
        */
        concrete_unit_type& operator+=(const concrete_unit_type& another)
        {
            return this_as_concrete().add(another.value());
        }

        /*!
            \brief Adds another unit.

            \tparam U A unit type.

            \param another Another unit.

            \return This object.
        */
        template <typename U>
        concrete_unit_type& operator+=(const unit<U, typename U::value_type>& another)
        {
            return this_as_concrete().add(from(another).value());
        }

        /*!
            \brief Adds another value.

            \param another Another value.

            \return This object.
        */
        concrete_unit_type& operator+=(const value_type& another)
        {
            return this_as_concrete().add(another);
        }

        /*!
            \brief Adds units.

            \tparam U A unit type.

            \param one     One unit.
            \param another Another unit.

            \return A unit.
        */
        template <typename U>
        friend concrete_unit_type operator+(
            const concrete_unit_type&              one,
            const unit<U, typename U::value_type>& another
        )
        {
            concrete_unit_type unit{ one };
            unit += another;
            return unit;
        }

        /*!
            \brief Subtracts another unit.

            \param another Another unit.

            \return This object.
        */
        concrete_unit_type& operator-=(const concrete_unit_type& another)
        {
            return this_as_concrete().subtract(another.value());
        }

        /*!
            \brief Subtracts another unit.

            \tparam U A unit type.

            \param another Another unit.

            \return This object.
        */
        template <typename U>
        concrete_unit_type& operator-=(const unit<U, typename U::value_type>& another)
        {
            return this_as_concrete().subtract(from(another).value());
        }

        /*!
            \brief Subtracts another value.

            \param another Another value.

            \return This object.
        */
        concrete_unit_type& operator-=(const value_type& another)
        {
            return this_as_concrete().subtract(another);
        }

        /*!
            \brief Subtracts units.

            \tparam U A unit type.

            \param one     One unit.
            \param another Another unit.

            \return A unit.
        */
        template <typename U>
        friend concrete_unit_type operator-(
            const concrete_unit_type&              one,
            const unit<U, typename U::value_type>& another
        )
        {
            concrete_unit_type unit{ one };
            unit -= another;
            return unit;
        }

        /*!
            \brief Multiplies another value.

            \param another Another value.

            \return This object.
        */
        concrete_unit_type& operator*=(const value_type& another)
        {
            return this_as_concrete().multiply(another);
        }

        /*!
            \brief Divides by another value.

            \param another Another value.

            \return This object.
        */
        concrete_unit_type& operator/=(const value_type& another)
        {
            return this_as_concrete().divide_by(another);
        }

        /*!
            \brief Divides by another unit.

            \param one     One unit.
            \param another Another unit.

            \return A value.
        */
        friend value_type operator/(const concrete_unit_type& one, const concrete_unit_type& another)
        {
            return one.divide_by(another);
        }

        /*!
            \brief Checks whether one unit is equal to another.

            \tparam U A unit type.

            \param one     One unit.
            \param another Another unit.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        template <typename U>
        friend bool operator==(const concrete_unit_type&  one, const unit<U, typename U::value_type>& another)
        {
            return operator==(one, from(another).value());
        }

        /*!
            \brief Checks whether one unit is equal to another.

            \param one     One unit.
            \param another Another unit.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const concrete_unit_type& one, const concrete_unit_type& another)
        {
            return operator==(one, another.value());
        }

        /*!
            \brief Checks whether one unit is not equal to another.

            \tparam U A unit type.

            \param one     One unit.
            \param another Another unit.

            \retval true  When the one is not equal to the other.
            \retval false Otherwise.
        */
        template <typename U>
        friend bool operator!=(const concrete_unit_type& one, const unit<U, typename U::value_type>& another)
        {
            return operator!=(one, from(another).value());
        }

        /*!
            \brief Checks whether one unit is less than another.

            \tparam U A unit type.

            \param one     One unit.
            \param another Another unit.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        template <typename U>
        friend bool operator<(const concrete_unit_type& one, const unit<U, typename U::value_type>& another)
        {
            return operator<(one, from(another).value());
        }

        /*!
            \brief Checks whether one unit is less than another.

            \param one     One unit.
            \param another Another unit.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        friend bool operator<(const concrete_unit_type& one, const concrete_unit_type& another)
        {
            return operator<(one, another.value());
        }

        /*!
            \brief Checks whether one unit is greater than another.

            \tparam U A unit type.

            \param one     One unit.
            \param another Another unit.

            \retval true  When the one is greater than the other.
            \retval false Otherwise.
        */
        template <typename U>
        friend bool operator>(const concrete_unit_type& one, const unit<U, typename U::value_type>& another)
        {
            return operator>(one, from(another).value());
        }


    private:
        // functions

        concrete_unit_type& this_as_concrete()
        {
            return *static_cast<concrete_unit_type*>(this);
        }


    };


}}}


#endif

/*! \file
    \brief The definition of tetengo2::text.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_OPERATORS_H)
#define TETENGO2_OPERATORS_H

#include <utility>


namespace tetengo2
{
    /*!
        \brief The class template for providing operator plus.

        \tparam T A type.
        \tparam U A type.
    */
    template <typename T, typename U = T>
    class addable
    {
    public:
        // functions

        /*!
            \brief Adds two values.

            \param t A value.
            \param u A value.

            \return The sum.
        */
        friend T operator+(const T& t, const U& u)
        {
            return operator+(T(t), u);
        }

        /*!
            \brief Adds two values.

            \param t A value.
            \param u A value.

            \return The sum.
        */
        friend T operator+(const T& t, U&& u)
        {
            return operator+(T(t), u);
        }

        /*!
            \brief Adds two values.

            \param t A value.
            \param u A value.

            \return The sum.
        */
        friend T operator+(T&& t, const U& u)
        {
            t += u;
            return t;
        }

        /*!
            \brief Adds two values.

            \param t A value.
            \param u A value.

            \return The sum.
        */
        friend T operator+(T&& t, U&& u)
        {
            return operator+(std::forward<T>(t), static_cast<const U&>(u));
        }


    };


    /*!
        \brief The class template for providing operator minus.

        \tparam T A type.
        \tparam U A type.
    */
    template <typename T, typename U = T>
    class substractable
    {
    public:
        // functions

        /*!
            \brief Subtracts two values.

            \param t A value.
            \param u A value.

            \return The difference.
        */
        friend T operator-(const T& t, const U& u)
        {
            return operator-(T(t), u);
        }

        /*!
            \brief Subtracts two values.

            \param t A value.
            \param u A value.

            \return The difference.
        */
        friend T operator-(const T& t, U&& u)
        {
            return operator-(T(t), u);
        }

        /*!
            \brief Subtracts two values.

            \param t A value.
            \param u A value.

            \return The difference.
        */
        friend T operator-(T&& t, const U& u)
        {
            t -= u;
            return t;
        }

        /*!
            \brief Subtracts two values.

            \param t A value.
            \param u A value.

            \return The difference.
        */
        friend T operator-(T&& t, U&& u)
        {
            return operator-(std::forward<T>(t), static_cast<const U&>(u));
        }


    };


    /*!
        \brief The class template for providing additive operators.

        \tparam T A type.
        \tparam U A type.
    */
    template <typename T, typename U = T>
    class additive : private addable<T, U>, private substractable<T, U>
    {};


}


#endif

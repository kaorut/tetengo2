/*! \file
    \brief The definition of tetengo2::text.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_OPERATORS_H)
#define TETENGO2_OPERATORS_H

#include <type_traits>
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

        friend T operator+(const T& t, const U& u)
        {
            return operator+(T(t), u);
        }

        friend T operator+(const T& t, U&& u)
        {
            return operator+(T(t), u);
        }

        friend T operator+(T&& t, const U& u)
        {
            t += u;
            return t;
        }

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

        friend T operator-(const T& t, const U& u)
        {
            return operator-(T(t), u);
        }

        friend T operator-(const T& t, U&& u)
        {
            return operator-(T(t), u);
        }

        friend T operator-(T&& t, const U& u)
        {
            t -= u;
            return t;
        }

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

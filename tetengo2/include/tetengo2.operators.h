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
    */
    template <typename T>
    class addable
    {
    public:
        // functions

        template <typename U>
        friend T operator+(const T& t, U&& u)
        {
            return plus_lr(t, std::forward<U>(u));
        }

        template <typename U>
        friend T operator+(T&& t, U&& u)
        {
            t += u;
            return t;
        }


    private:
        // static functions

        template <typename U>
        static T plus_lr(
            const T& t,
            U&&      u,
            typename std::enable_if<
                std::is_rvalue_reference<U&&>::value &&
                std::is_convertible<T, U>::value &&
                std::is_convertible<U, T>::value
            >::type* = NULL
        )
        {
            u += t;
            return u;
        }

        template <typename U>
        static T plus_lr(
            const T& t,
            U&&      u,
            typename std::enable_if<
                !std::is_rvalue_reference<U&&>::value ||
                !std::is_convertible<T, U>::value ||
                !std::is_convertible<U, T>::value
            >::type* = NULL
        )
        {
            return operator+(T(t), std::forward<U>(u));
        }


    };


    /*!
        \brief The class template for providing operator minus.

        \tparam T A type.
    */
    template <typename T>
    class substractable
    {
    public:
        // functions

        template <typename U>
        friend T operator-(const T& t, const U& u)
        {
            return operator-(T(t), u);
        }

        template <typename U>
        friend T operator-(T&& t, const U& u)
        {
            t -= u;
            return t;
        }


    };


}


#endif

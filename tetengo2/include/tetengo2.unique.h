/*! \file
    \brief The definition of tetengo2::unique.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_UNIQUE_H)
#define TETENGO2_UNIQUE_H

#include <memory>
#include <utility>


namespace tetengo2
{
    /*!
        \brief Makes a unique pointer.

        \tparam T A type.

        \return A unique pointer
    */
    template <typename T>
    std::unique_ptr<T> make_unique()
    {
        return std::unique_ptr<T>(new T());
    }

    /*!
        \brief Makes a unique pointer.

        \tparam T  A type.
        \tparam A1 An argument type #1.

        \param arg1 An argument #1.

        \return A unique pointer
    */
    template <typename T, typename A1>
    std::unique_ptr<T> make_unique(A1&& arg1)
    {
        return std::unique_ptr<T>(new T(std::forward<A1>(arg1)));
    }

    /*!
        \brief Makes a unique pointer.

        \tparam T  A type.
        \tparam A1 An argument type #1.
        \tparam A2 An argument type #2.

        \param arg1 An argument #1.
        \param arg2 An argument #2.

        \return A unique pointer
    */
    template <typename T, typename A1, typename A2>
    std::unique_ptr<T> make_unique(A1&& arg1, A2&& arg2)
    {
        return std::unique_ptr<T>(new T(std::forward<A1>(arg1), std::forward<A2>(arg2)));
    }

#if !defined(DOCUMENTATION)
    template <typename T, typename A1, typename A2, typename A3>
    std::unique_ptr<T> make_unique(A1&& arg1, A2&& arg2, A3&& arg3)
    {
        return std::unique_ptr<T>(new T(std::forward<A1>(arg1), std::forward<A2>(arg2), std::forward<A3>(arg3)));
    }

    template <typename T, typename A1, typename A2, typename A3, typename A4>
    std::unique_ptr<T> make_unique(A1&& arg1, A2&& arg2, A3&& arg3, A4&& arg4)
    {
        return
            std::unique_ptr<T>(
                new T(std::forward<A1>(arg1), std::forward<A2>(arg2), std::forward<A3>(arg3), std::forward<A4>(arg4))
            );
    }

    template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
    std::unique_ptr<T> make_unique(A1&& arg1, A2&& arg2, A3&& arg3, A4&& arg4, A5&& arg5)
    {
        return
            std::unique_ptr<T>(
                new T(
                    std::forward<A1>(arg1),
                    std::forward<A2>(arg2),
                    std::forward<A3>(arg3),
                    std::forward<A4>(arg4),
                    std::forward<A5>(arg5)
                )
            );
    }

    template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    std::unique_ptr<T> make_unique(A1&& arg1, A2&& arg2, A3&& arg3, A4&& arg4, A5&& arg5, A6&& arg6)
    {
        return
            std::unique_ptr<T>(
                new T(
                    std::forward<A1>(arg1),
                    std::forward<A2>(arg2),
                    std::forward<A3>(arg3),
                    std::forward<A4>(arg4),
                    std::forward<A5>(arg5),
                    std::forward<A6>(arg6)
                )
            );
    }

    template <typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    std::unique_ptr<T> make_unique(A1&& arg1, A2&& arg2, A3&& arg3, A4&& arg4, A5&& arg5, A6&& arg6, A7&& arg7)
    {
        return
            std::unique_ptr<T>(
                new T(
                    std::forward<A1>(arg1),
                    std::forward<A2>(arg2),
                    std::forward<A3>(arg3),
                    std::forward<A4>(arg4),
                    std::forward<A5>(arg5),
                    std::forward<A6>(arg6),
                    std::forward<A7>(arg7)
                )
            );
    }

    template <
        typename T,
        typename A1,
        typename A2,
        typename A3,
        typename A4,
        typename A5,
        typename A6,
        typename A7,
        typename A8
    >
    std::unique_ptr<T> make_unique(
        A1&& arg1,
        A2&& arg2,
        A3&& arg3,
        A4&& arg4,
        A5&& arg5,
        A6&& arg6,
        A7&& arg7,
        A8&& arg8
    )
    {
        return
            std::unique_ptr<T>(
                new T(
                    std::forward<A1>(arg1),
                    std::forward<A2>(arg2),
                    std::forward<A3>(arg3),
                    std::forward<A4>(arg4),
                    std::forward<A5>(arg5),
                    std::forward<A6>(arg6),
                    std::forward<A7>(arg7),
                    std::forward<A8>(arg8)
                )
            );
    }

    template <
        typename T,
        typename A1,
        typename A2,
        typename A3,
        typename A4,
        typename A5,
        typename A6,
        typename A7,
        typename A8,
        typename A9
    >
    std::unique_ptr<T> make_unique(
        A1&& arg1,
        A2&& arg2,
        A3&& arg3,
        A4&& arg4,
        A5&& arg5,
        A6&& arg6,
        A7&& arg7,
        A8&& arg8,
        A9&& arg9
    )
    {
        return
            std::unique_ptr<T>(
                new T(
                    std::forward<A1>(arg1),
                    std::forward<A2>(arg2),
                    std::forward<A3>(arg3),
                    std::forward<A4>(arg4),
                    std::forward<A5>(arg5),
                    std::forward<A6>(arg6),
                    std::forward<A7>(arg7),
                    std::forward<A8>(arg8),
                    std::forward<A9>(arg9)
                )
            );
    }

    template <
        typename T,
        typename A1,
        typename A2,
        typename A3,
        typename A4,
        typename A5,
        typename A6,
        typename A7,
        typename A8,
        typename A9,
        typename A10
    >
    std::unique_ptr<T> make_unique(
        A1&&  arg1,
        A2&&  arg2,
        A3&&  arg3,
        A4&&  arg4,
        A5&&  arg5,
        A6&&  arg6,
        A7&&  arg7,
        A8&&  arg8,
        A9&&  arg9,
        A10&& arg10
    )
    {
        return
            std::unique_ptr<T>(
                new T(
                    std::forward<A1>(arg1),
                    std::forward<A2>(arg2),
                    std::forward<A3>(arg3),
                    std::forward<A4>(arg4),
                    std::forward<A5>(arg5),
                    std::forward<A6>(arg6),
                    std::forward<A7>(arg7),
                    std::forward<A8>(arg8),
                    std::forward<A9>(arg9),
                    std::forward<A10>(arg10)
                )
        );
    }

    template <
        typename T,
        typename A1,
        typename A2,
        typename A3,
        typename A4,
        typename A5,
        typename A6,
        typename A7,
        typename A8,
        typename A9,
        typename A10,
        typename A11
    >
    std::unique_ptr<T> make_unique(
        A1&&  arg1,
        A2&&  arg2,
        A3&&  arg3,
        A4&&  arg4,
        A5&&  arg5,
        A6&&  arg6,
        A7&&  arg7,
        A8&&  arg8,
        A9&&  arg9,
        A10&& arg10,
        A11&& arg11
    )
    {
        return
            std::unique_ptr<T>(
                new T(
                    std::forward<A1>(arg1),
                    std::forward<A2>(arg2),
                    std::forward<A3>(arg3),
                    std::forward<A4>(arg4),
                    std::forward<A5>(arg5),
                    std::forward<A6>(arg6),
                    std::forward<A7>(arg7),
                    std::forward<A8>(arg8),
                    std::forward<A9>(arg9),
                    std::forward<A10>(arg10),
                    std::forward<A11>(arg11)
                )
        );
    }

    template <
        typename T,
        typename A1,
        typename A2,
        typename A3,
        typename A4,
        typename A5,
        typename A6,
        typename A7,
        typename A8,
        typename A9,
        typename A10,
        typename A11,
        typename A12
    >
    std::unique_ptr<T> make_unique(
        A1&&  arg1,
        A2&&  arg2,
        A3&&  arg3,
        A4&&  arg4,
        A5&&  arg5,
        A6&&  arg6,
        A7&&  arg7,
        A8&&  arg8,
        A9&&  arg9,
        A10&& arg10,
        A11&& arg11,
        A12&& arg12
    )
    {
        return
            std::unique_ptr<T>(
                new T(
                    std::forward<A1>(arg1),
                    std::forward<A2>(arg2),
                    std::forward<A3>(arg3),
                    std::forward<A4>(arg4),
                    std::forward<A5>(arg5),
                    std::forward<A6>(arg6),
                    std::forward<A7>(arg7),
                    std::forward<A8>(arg8),
                    std::forward<A9>(arg9),
                    std::forward<A10>(arg10),
                    std::forward<A11>(arg11),
                    std::forward<A12>(arg12)
                )
        );
    }
#endif


}


#endif

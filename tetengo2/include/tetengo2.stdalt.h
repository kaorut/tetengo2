/*! \file
    \brief The definition of the standard C++ alternatives for tetengo2.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_STDALT_H)
#define TETENGO2_STDALT_H

#include <boost/predef.h>

#include "tetengo2.utility.h"


/* noexcept *******************************************************************/

#if !defined(DOCUMENTATION)
#   if BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0)
#       define TETENGO2_STDALT_NOEXCEPT_SUPPORTED 1
#   else
#       define TETENGO2_STDALT_NOEXCEPT_SUPPORTED 0
#   endif
#endif

#if TETENGO2_STDALT_NOEXCEPT_SUPPORTED || defined(DOCUMENTATION)
    //! The alternative to the C++11 keyword noexcept.
#   define TETENGO2_STDALT_NOEXCEPT noexcept
#else
#   define TETENGO2_STDALT_NOEXCEPT throw ()
#endif


/* insertion iterator *********************************************************/

#if !defined(DOCUMENTATION)
#   if BOOST_COMP_MSVC >= BOOST_VERSION_NUMBER(11, 0, 0)
#       define TETENGO2_STDALT_INSERTION_ITERATOR_SUPPORTED 1
#   else
#       define TETENGO2_STDALT_INSERTION_ITERATOR_SUPPORTED 0
#   endif
#endif

#if !TETENGO2_STDALT_INSERTION_ITERATOR_SUPPORTED
#   include <iterator>
#endif

namespace tetengo2 { namespace stdalt
{
#if TETENGO2_STDALT_INSERTION_ITERATOR_SUPPORTED || defined(DOCUMENTATION)
    /*!
        \brief Returns an iterator for insert(), erase(), etc. of the containers.

        \param container A container.
        \param iterator  An iterator.

        \return An iterator for insert(), erase(), etc. of the container.
    */
    template <typename Container>
    typename Container::const_iterator as_insertion_iterator(
        Container&                               container,
        const typename Container::const_iterator iterator
    )
    {
        suppress_unused_variable_warning(container);

        return iterator;
    }
#else
    template <typename Container>
    typename Container::iterator as_insertion_iterator(
        Container&                               container,
        const typename Container::const_iterator iterator
    )
    {
        typename Container::iterator mutable_iterator = container.begin();
        std::advance(
            mutable_iterator, std::distance<typename Container::const_iterator>(container.begin(), iterator)
        );
        return mutable_iterator;
    }
#endif


}}


/* lambda this capture bug workaround *****************************************/

#if !defined(DOCUMENTATION)
#   if BOOST_COMP_GNUC && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)
#       define TETENGO2_STDALT_HAS_LAMBDA_THIS_CAPTURE_BUG 1
#   else
#       define TETENGO2_STDALT_HAS_LAMBDA_THIS_CAPTURE_BUG 0
#   endif
#endif

#if TETENGO2_STDALT_HAS_LAMBDA_THIS_CAPTURE_BUG || defined(DOCUMENTATION)
    //! The lambda this capture bug workaround.
#   define TETENGO2_STDALT_LAMBDA_THIS_BUG_WA this,
#else
#   define TETENGO2_STDALT_LAMBDA_THIS_BUG_WA
#endif


/* thread *********************************************************************/

#if !defined(DOCUMENTATION)
#   if BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0)
#       define TETENGO2_STDALT_STD_THREAD_SUPPORTED 1
#   else
#       define TETENGO2_STDALT_STD_THREAD_SUPPORTED 0
#   endif
#endif
#if !defined(DOCUMENTATION)
#   define TETENGO2_STDALT_STD_THIS_THREAD_SLEEP_FOR_SUPPORTED 0
#endif

#include <thread>
#include <boost/thread.hpp>
#if TETENGO2_STDALT_STD_THREAD_SUPPORTED
#   include <condition_variable>
#   include <mutex>
#else
#endif
#if TETENGO2_STDALT_STD_THIS_THREAD_SLEEP_FOR_SUPPORTED
#   include <chrono>
#else
#   include <boost/chrono.hpp>
#endif

namespace tetengo2 { namespace stdalt
{
#if TETENGO2_STDALT_STD_THREAD_SUPPORTED || defined(DOCUMENTATION)
    //! The thread.
    typedef std::thread thread;

    //! The mutex.
    typedef std::mutex mutex;

    //! The condition variable.
    typedef std::condition_variable condition_variable;

    /*!
        \brief The unique lock.

        \tparam Mutex A mutex type.
    */
    template <typename Mutex>
    struct unique_lock
    {
        //! The unique lock type.
        typedef std::unique_lock<Mutex> type;
    };
#else
    typedef boost::thread thread;

    typedef boost::mutex mutex;

    typedef boost::condition_variable condition_variable;

    template <typename Mutex>
    struct unique_lock
    {
        typedef boost::unique_lock<Mutex> type;
    };
#endif

#if TETENGO2_STDALT_STD_THIS_THREAD_SLEEP_FOR_SUPPORTED || defined(DOCUMENTATION)
    /*!
        \brief Sleep this thread.

        \tparam Int An integer type.

        \param ms Milliseconds.
    */
    template <typename Int>
    void this_thread_sleep_for(const Int ms)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
#else
    template <typename Int>
    void this_thread_sleep_for(const Int ms)
    {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(ms));
    }
#endif


}}


/* make_unique ****************************************************************/

#if !defined(DOCUMENTATION)
#   define TETENGO2_STDALT_STD_MAKE_UNIQUE_SUPPORTED 0
#endif

#include <utility>
#include <memory>

namespace tetengo2 { namespace stdalt
{
#if TETENGO2_STDALT_STD_MAKE_UNIQUE_SUPPORTED || defined(DOCUMENTATION)
    /*!
        \brief Makes a unique pointer.

        \tparam T A type.

        \return A unique pointer
    */
    template <typename T>
    std::unique_ptr<T> make_unique()
    {
        return std::make_unique<T>();
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
        return std::make_unique<T>(std::forward<A1>(arg1));
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
        return std::make_unique<T>(std::forward<A1>(arg1), std::forward<A2>(arg2));
    }
#else
    template <typename T>
    std::unique_ptr<T> make_unique()
    {
        return std::unique_ptr<T>(new T());
    }

    template <typename T, typename A1>
    std::unique_ptr<T> make_unique(A1&& arg1)
    {
        return std::unique_ptr<T>(new T(std::forward<A1>(arg1)));
    }

    template <typename T, typename A1, typename A2>
    std::unique_ptr<T> make_unique(A1&& arg1, A2&& arg2)
    {
        return std::unique_ptr<T>(new T(std::forward<A1>(arg1), std::forward<A2>(arg2)));
    }

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


}}


#endif

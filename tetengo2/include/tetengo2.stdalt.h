/*! \file
    \brief The definition of C++11 alternatives for tetengo2.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_CPP11_H)
#define TETENGO2_CPP11_H

#include "tetengo2.utility.h"


/* noexcept *****************************************************************/

#if !defined(DOCUMENTATION)
#   if (defined(__GNUC__) && defined(__GNUC_MINOR__) && __GNUC__ >= 4 && __GNUC_MINOR__ >= 7)
#       define TETENGO2_CPP11_NOEXCEPT_SUPPORTED 1
#   else
#       define TETENGO2_CPP11_NOEXCEPT_SUPPORTED 0
#   endif
#endif

#if TETENGO2_CPP11_NOEXCEPT_SUPPORTED || defined(DOCUMENTATION)
    //! The alternative to the C++11 keyword noexcept.
#   define TETENGO2_CPP11_NOEXCEPT noexcept
#else
#   define TETENGO2_CPP11_NOEXCEPT throw ()
#endif


/* insertion iterator *******************************************************/

#if !defined(DOCUMENTATION)
#   if (defined(_MSC_VER) && _MSC_VER >= 1600)
#       define TETENGO2_CPP11_INSERTION_ITERATOR_SUPPORTED 1
#   else
#       define TETENGO2_CPP11_INSERTION_ITERATOR_SUPPORTED 0
#   endif
#endif

#if !TETENGO2_CPP11_INSERTION_ITERATOR_SUPPORTED
#   include <iterator>
#endif

namespace tetengo2 { namespace cpp11
{
#if TETENGO2_CPP11_INSERTION_ITERATOR_SUPPORTED || defined(DOCUMENTATION)
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


/* lambda this capture bug workaround ***************************************/

#if !defined(DOCUMENTATION)
#   if (defined(__GNUC__) && defined(__GNUC_MINOR__) && __GNUC__ == 4 && __GNUC_MINOR__ <= 7)
#       define TETENGO2_CPP11_HAS_LAMBDA_THIS_CAPTURE_BUG 1
#   else
#       define TETENGO2_CPP11_HAS_LAMBDA_THIS_CAPTURE_BUG 0
#   endif
#endif

#if TETENGO2_CPP11_HAS_LAMBDA_THIS_CAPTURE_BUG || defined(DOCUMENTATION)
    //! The lambda this capture bug workaround.
#   define TETENGO2_CPP11_LAMBDA_THIS_BUG_WA this,
#else
#   define TETENGO2_CPP11_LAMBDA_THIS_BUG_WA
#endif


/* thread *******************************************************************/

#if !defined(DOCUMENTATION)
#   if (defined(__GNUC__) && defined(__GNUC_MINOR__) && __GNUC__ >= 4 && __GNUC_MINOR__ >= 7)
#       define TETENGO2_CPP11_STD_THREAD_SUPPORTED 1
#   else
#       define TETENGO2_CPP11_STD_THREAD_SUPPORTED 0
#   endif
#endif
#if !defined(DOCUMENTATION)
#   define TETENGO2_CPP11_STD_THIS_THREAD_SLEEP_FOR_SUPPORTED 0
#endif

#   include <thread>
#   include <boost/thread.hpp>
#if TETENGO2_CPP11_STD_THREAD_SUPPORTED
#   include <condition_variable>
#   include <mutex>
#else
#endif
#if TETENGO2_CPP11_STD_THIS_THREAD_SLEEP_FOR_SUPPORTED
#   include <chrono>
#else
#   include <boost/chrono.hpp>
#endif

namespace tetengo2 { namespace cpp11
{
#if TETENGO2_CPP11_STD_THREAD_SUPPORTED || defined(DOCUMENTATION)
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

#if TETENGO2_CPP11_STD_THIS_THREAD_SLEEP_FOR_SUPPORTED || defined(DOCUMENTATION)
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


#endif

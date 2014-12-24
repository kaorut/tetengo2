/*! \file
    \brief The definition of the standard C++ alternatives for tetengo2.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_STDALT_H)
#define TETENGO2_STDALT_H

#include <boost/core/ignore_unused.hpp>
#include <boost/predef.h>


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
#   define TETENGO2_STDALT_NOEXCEPT
#endif


/* destructor default implementation ******************************************/

#if !defined(DOCUMENTATION)
#   if BOOST_COMP_MSVC >= BOOST_VERSION_NUMBER(12, 0, 0) || BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 8, 0)
#       define TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION_SUPPORTED 1
#   else
#       define TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION_SUPPORTED 0
#   endif
#endif

#if TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION_SUPPORTED || defined(DOCUMENTATION)
//! The destructor default implementation.
#   define TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION TETENGO2_STDALT_NOEXCEPT = default
#else
#   define TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION TETENGO2_STDALT_NOEXCEPT {}
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
        boost::ignore_unused(container);

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
#   define TETENGO2_STDALT_STD_THIS_THREAD_SLEEP_FOR_SUPPORTED 0
#endif

#include <thread>
#include <boost/thread.hpp>
#if TETENGO2_STDALT_STD_THIS_THREAD_SLEEP_FOR_SUPPORTED
#   include <chrono>
#else
#   include <boost/chrono.hpp>
#endif

namespace tetengo2 { namespace stdalt
{
#if TETENGO2_STDALT_STD_THIS_THREAD_SLEEP_FOR_SUPPORTED || defined(DOCUMENTATION)
    /*!
        \brief Sleep this thread.

        \tparam Int An integer type.

        \param ms Milliseconds.
    */
    template <typename Int>
    void this_thread_sleep_for(const Int ms)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds{ ms });
    }
#else
    template <typename Int>
    void this_thread_sleep_for(const Int ms)
    {
        boost::this_thread::sleep_for(boost::chrono::milliseconds{ ms });
    }
#endif


}}


/* make_unique ****************************************************************/

#if !defined(DOCUMENTATION)
#   if BOOST_COMP_MSVC >= BOOST_VERSION_NUMBER(12, 0, 0)
#       define TETENGO2_STDALT_STD_MAKE_UNIQUE_SUPPORTED 1
#   else
#       define TETENGO2_STDALT_STD_MAKE_UNIQUE_SUPPORTED 0
#   endif
#endif

#include <utility>
#include <memory>

namespace tetengo2 { namespace stdalt
{
#if TETENGO2_STDALT_STD_MAKE_UNIQUE_SUPPORTED || defined(DOCUMENTATION)
    /*!
        \brief Makes a unique pointer.

        \tparam T A type.
        \tparam A Argument types.

        \param args An arguments.

        \return A unique pointer
    */
    template <typename T, typename... A>
    std::unique_ptr<T> make_unique(A&&... args)
    {
        return std::make_unique<T>(std::forward<A>(args)...);
    }
#else
    template <typename T, typename... A>
    std::unique_ptr<T> make_unique(A&&... args)
    {
        return std::unique_ptr<T>{ new T(std::forward<A>(args)...) };
    }
#endif


}}


#endif

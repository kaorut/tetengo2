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


/* bind *********************************************************************/

#if !defined(DOCUMENTATION)
#   if \
        (defined(_MSC_VER) && _MSC_VER >= 1600) || \
        (defined(__GNUC__) && defined(__GNUC_MINOR__) && __GNUC__ >= 4 && __GNUC_MINOR__ >= 5)
#       define TETENGO2_CPP11_STD_BIND_SUPPORTED 1
#   else
#       define TETENGO2_CPP11_STD_BIND_SUPPORTED 0
#   endif
#endif

#include <functional>
#if !TETENGO2_CPP11_STD_BIND_SUPPORTED
#   include <boost/bind.hpp>
#endif

#if TETENGO2_CPP11_STD_BIND_SUPPORTED || defined(DOCUMENTATION)
    //! The alternative to std::bind.
#   define TETENGO2_CPP11_BIND std::bind
#else
#   define TETENGO2_CPP11_BIND boost::bind
#endif

namespace tetengo2 { namespace cpp11
{
#if TETENGO2_CPP11_STD_BIND_SUPPORTED || defined(DOCUMENTATION)
    /*!
        \brief The function for the placeholder #1 for bind().

        \return The placeholder #1.
    */
    inline decltype(std::placeholders::_1)& placeholders_1()
    {
        static decltype(std::placeholders::_1)& ph = std::placeholders::_1;
        return ph;
    }

    /*!
        \brief The function for the placeholder #2 for bind().

        \return The placeholder #2.
    */
    inline decltype(std::placeholders::_2)& placeholders_2()
    {
        static decltype(std::placeholders::_2)& ph = std::placeholders::_2;
        return ph;
    }

    /*!
        \brief The function for the placeholder #3 for bind().

        \return The placeholder #3.
    */
    inline decltype(std::placeholders::_3)& placeholders_3()
    {
        static decltype(std::placeholders::_3)& ph = std::placeholders::_3;
        return ph;
    }

    /*!
        \brief The function for the placeholder #4 for bind().

        \return The placeholder #4.
    */
    inline decltype(std::placeholders::_4)& placeholders_4()
    {
        static decltype(std::placeholders::_4)& ph = std::placeholders::_4;
        return ph;
    }

    /*!
        \brief The function for the placeholder #5 for bind().

        \return The placeholder #5.
    */
    inline decltype(std::placeholders::_5)& placeholders_5()
    {
        static decltype(std::placeholders::_5)& ph = std::placeholders::_5;
        return ph;
    }

    /*!
        \brief The function for the placeholder #6 for bind().

        \return The placeholder #6.
    */
    inline decltype(std::placeholders::_6)& placeholders_6()
    {
        static decltype(std::placeholders::_6)& ph = std::placeholders::_6;
        return ph;
    }

    /*!
        \brief The function for the placeholder #7 for bind().

        \return The placeholder #7.
    */
    inline decltype(std::placeholders::_7)& placeholders_7()
    {
        static decltype(std::placeholders::_7)& ph = std::placeholders::_7;
        return ph;
    }

    /*!
        \brief The function for the placeholder #8 for bind().

        \return The placeholder #8.
    */
    inline decltype(std::placeholders::_8)& placeholders_8()
    {
        static decltype(std::placeholders::_8)& ph = std::placeholders::_8;
        return ph;
    }

    /*!
        \brief The function for the placeholder #9 for bind().

        \return The placeholder #9.
    */
    inline decltype(std::placeholders::_9)& placeholders_9()
    {
        static decltype(std::placeholders::_9)& ph = std::placeholders::_9;
        return ph;
    }

    /*!
        \brief The function for the placeholder #10 for bind().

        \return The placeholder #10.
    */
    inline decltype(std::placeholders::_10)& placeholders_10()
    {
        static decltype(std::placeholders::_10)& ph = std::placeholders::_10;
        return ph;
    }
#else
    inline decltype(_1)& placeholders_1()
    {
        static decltype(_1)& ph = _1;
        return ph;
    }

    inline decltype(_2)& placeholders_2()
    {
        static decltype(_2)& ph = _2;
        return ph;
    }

    inline decltype(_3)& placeholders_3()
    {
        static decltype(_3)& ph = _3;
        return ph;
    }

    inline decltype(_4)& placeholders_4()
    {
        static decltype(_4)& ph = _4;
        return ph;
    }

    inline decltype(_5)& placeholders_5()
    {
        static decltype(_5)& ph = _5;
        return ph;
    }

    inline decltype(_6)& placeholders_6()
    {
        static decltype(_6)& ph = _6;
        return ph;
    }

    inline decltype(_7)& placeholders_7()
    {
        static decltype(_7)& ph = _7;
        return ph;
    }

    inline decltype(_8)& placeholders_8()
    {
        static decltype(_8)& ph = _8;
        return ph;
    }

    inline decltype(_9)& placeholders_9()
    {
        static decltype(_9)& ph = _9;
        return ph;
    }
#endif


}}


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


#endif

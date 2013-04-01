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


#endif

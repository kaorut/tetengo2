/*! \file
    \brief The definition of C++0x alternatives for tetengo2.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_CPP0X_H)
#define TETENGO2_CPP0X_H

#if !defined(DOCUMENTATION)
#   if \
        (defined(_MSC_VER) && _MSC_VER >= 1600) || \
        ( \
            defined(__GNUC__) && defined(__GNUC_MINOR__) && \
            __GNUC__ >= 4 && __GNUC_MINOR__ >= 4 \
        )
#       define TETENGO2_CPP0X_STD_UNIQUEPTR_SUPPORTED 1
#   else
#       define TETENGO2_CPP0X_STD_UNIQUEPTR_SUPPORTED 0
#   endif
#endif

#if TETENGO2_CPP0X_STD_UNIQUEPTR_SUPPORTED
#   include <memory>
#endif

#if !TETENGO2_CPP0X_STD_UNIQUEPTR_SUPPORTED
#   include <boost/interprocess/smart_ptr/unique_ptr.hpp>
#   include <boost/utility.hpp>
#endif


//! The alternative to the C++0x keyword noexcept.
#define TETENGO2_CPP0X_NOEXCEPT throw ()


namespace tetengo2 { namespace cpp0x
{
#if TETENGO2_CPP0X_STD_UNIQUEPTR_SUPPORTED
    /*!
        \brief The meta function for unique pointer implementation.

        \tparam T       A type.
        \tparam Deleter A deleter type.
    */
    template <typename T, typename Deleter = std::default_delete<T>>
    struct unique_ptr
    {
        //! The unique pointer implementation type.
        typedef std::unique_ptr<T, Deleter> type;


    };
#else
    template <typename T, typename Deleter = boost::checked_deleter<T>>
    struct unique_ptr
    {
        typedef boost::interprocess::unique_ptr<T, Deleter> type;


    };
#endif

}}


#endif

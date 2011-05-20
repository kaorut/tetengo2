/*! \file
    \brief The definition of C++0x alternatives for tetengo2.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_CPP0X_H)
#define TETENGO2_CPP0X_H

/* noexcept *****************************************************************/

//! The alternative to the C++0x keyword noexcept.
#define TETENGO2_CPP0X_NOEXCEPT throw ()


/* unique_ptr ***************************************************************/

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
#else
#   include <boost/interprocess/smart_ptr/unique_ptr.hpp>
#   include <boost/utility.hpp>
#endif

namespace tetengo2 { namespace cpp0x
{
#if TETENGO2_CPP0X_STD_UNIQUEPTR_SUPPORTED || defined(DOCUMENTATION)
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


/* reference_wrapper, ref ***************************************************/

#if !defined(DOCUMENTATION)
#   if \
        ( \
            defined(__GNUC__) && defined(__GNUC_MINOR__) && \
            __GNUC__ >= 4 && __GNUC_MINOR__ >= 3 \
        )
#       define TETENGO2_CPP0X_STD_REFERENCEWRAPPER_SUPPORTED 1
#   else
#       define TETENGO2_CPP0X_STD_REFERENCEWRAPPER_SUPPORTED 0
#   endif
#endif

#if TETENGO2_CPP0X_STD_REFERENCEWRAPPER_SUPPORTED
#   include <functional>
#else
#   include <boost/ref.hpp>
#endif

namespace tetengo2 { namespace cpp0x
{
#if TETENGO2_CPP0X_STD_REFERENCEWRAPPER_SUPPORTED || defined(DOCUMENTATION)
    /*!
        \brief The meta function for reference wrapper implementation.

        \tparam T A type.
    */
    template <typename T>
    struct reference_wrapper
    {
        //! The reference wrapper implementation type.
        typedef std::reference_wrapper<T> type;
    };

    /*!
        \brief The function for ref implementation.

        \tparam T A type.

        \param value A value.

        \return A reference wrapper.
    */
    template <typename T>
    inline std::reference_wrapper<T> ref(T& value)
    {
        return std::ref(value);
    }

    /*!
        \brief The function for cref implementation.

        \tparam T A type.

        \param value A value.

        \return A reference wrapper.
    */
    template <typename T>
    inline std::reference_wrapper<const T> cref(const T& value)
    {
        return std::cref(value);
    }

#else
    template <typename T>
    struct reference_wrapper
    {
        typedef boost::reference_wrapper<T> type;
    };

    template <typename T>
    inline boost::reference_wrapper<T> ref(T& value)
    {
        return boost::ref(value);
    }

    template <typename T>
    inline boost::reference_wrapper<const T> cref(const T& value)
    {
        return boost::cref(value);
    }
#endif


}}


#endif

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


/* bind *********************************************************************/

#if !defined(DOCUMENTATION)
#   if \
        (defined(_MSC_VER) && _MSC_VER >= 1600) || \
        ( \
            defined(__GNUC__) && defined(__GNUC_MINOR__) && \
            __GNUC__ >= 4 && __GNUC_MINOR__ >= 5 \
        )
#       define TETENGO2_CPP0X_STD_BIND_SUPPORTED 1
#   else
#       define TETENGO2_CPP0X_STD_BIND_SUPPORTED 0
#   endif
#endif

#include <functional>
#if !TETENGO2_CPP0X_STD_BIND_SUPPORTED
#   include <boost/bind.hpp>
#endif

#if TETENGO2_CPP0X_STD_BIND_SUPPORTED || defined(DOCUMENTATION)
    //! The alternative to std::bind.
#   define TETENGO2_CPP0X_BIND std::bind
#else
#   define TETENGO2_CPP0X_BIND boost::bind
#endif

namespace tetengo2 { namespace cpp0x
{
#if TETENGO2_CPP0X_STD_BIND_SUPPORTED || defined(DOCUMENTATION)
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

// <functional> is included above.
#if !TETENGO2_CPP0X_STD_REFERENCEWRAPPER_SUPPORTED
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

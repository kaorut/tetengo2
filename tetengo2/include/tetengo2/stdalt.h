/*! \file
    \brief The definition of the standard C++ alternatives for tetengo2.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_STDALT_H)
#define TETENGO2_STDALT_H

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

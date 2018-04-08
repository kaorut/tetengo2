/*! \file
    \brief The definition of the standard C++ alternatives for tetengo2.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_STDALT_H)
#define TETENGO2_STDALT_H

#if __has_include(<filesystem>)
#include <filesystem>
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
#else
#error Standard filesystem library not found.
#endif

#include <boost/predef.h>


#if BOOST_COMP_GNUC && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(7, 0, 0)
#define TETENGO2_STDALT_MAYBE_UNUSED __attribute__((unused))
#else
/*!
    \brief The alternate to [[maybe_unused]].
*/
#define TETENGO2_STDALT_MAYBE_UNUSED [[maybe_unused]]
#endif


namespace tetengo2::stdalt {
#if (BOOST_COMP_MSVC && BOOST_COMP_MSVC < BOOST_VERSION_NUMBER(19, 20, 0)) || \
    (BOOST_COMP_CLANG && BOOST_COMP_CLANG < BOOST_VERSION_NUMBER(6, 0, 0)) || \
    (BOOST_COMP_GNUC && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(7, 0, 0))
    namespace filesystem = std::experimental::filesystem;
#elif defined(DOCUMENTATION)
    /*!
        \brief The alternate to std::filesystem.
    */
    namespace filesystem = std::filesystem;
#else
#error Unsupported compiler.
#endif
}


#endif

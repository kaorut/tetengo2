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
#if __has_include(<optional>)
#include <optional>
#elif __has_include(<experimental/optional>)
#include <experimental/optional>
#else
#error Standard optional library not found.
#endif
#include <type_traits>
#include <utility>

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
#else
    /*!
        \brief The alternate to std::filesystem.
    */
    namespace filesystem = std::filesystem;
#endif
}


namespace tetengo2::stdalt {
#if (BOOST_COMP_CLANG && BOOST_COMP_CLANG < BOOST_VERSION_NUMBER(6, 0, 0)) || \
    (BOOST_COMP_GNUC && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(7, 0, 0))
    template <typename T>
    using optional = std::experimental::optional<T>;

    template <typename T>
    bool has_value(const std::experimental::optional<T>& o)
    {
        return static_cast<bool>(o);
    }
#else
    /*!
        \brief The alternate to std::optional.

        \tparam T A type.
    */
    template <typename T>
    using optional = std::optional<T>;

    /*!
        \brief The alternate to std::optional::has_value().

        \tparam T A type.

        \param o An optional.

        \retval ture  When o.has_value() is true.
        \retval false Otherwise.
    */
    template <typename T>
    bool has_value(const std::optional<T>& o)
    {
        return o.has_value();
    }
#endif

    /*!
        \brief The alternate to std::make_optional().

        \tparam T A type.

        \param v A value.

        \return The optional.
    */
    template <class T>
    constexpr optional<T> make_optional(T&& v)
    {
        return optional<std::decay_t<T>>(std::forward<T>(v));
    }
}

#if (BOOST_COMP_CLANG && BOOST_COMP_CLANG < BOOST_VERSION_NUMBER(6, 0, 0)) || \
    (BOOST_COMP_GNUC && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(7, 0, 0))
#define TETENGO2_STDALT_NULLOPT std::experimental::nullopt
#else
#define TETENGO2_STDALT_NULLOPT std::nullopt
#endif


#endif

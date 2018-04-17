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
#include <experimental/filesystem> // IWYU pragma: keep
#else
#error Standard filesystem library not found.
#endif
#if __has_include(<optional>)
#include <optional>
#elif __has_include(<experimental/optional>)
#include <experimental/optional> // IWYU pragma: keep
#else
#error Standard optional library not found.
#endif
#if __has_include(<variant>)
#include <string_view>
#else
#include <boost/utility/string_view.hpp>
#endif
#include <type_traits>
#include <utility>
#if __has_include(<variant>)
#include <variant>
#else
#include <boost/variant.hpp>
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
    template <typename T>
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


namespace tetengo2::stdalt {
#if (BOOST_COMP_CLANG && BOOST_COMP_CLANG < BOOST_VERSION_NUMBER(6, 0, 0)) || \
    (BOOST_COMP_GNUC && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(7, 0, 0))
    template <typename... Types>
    using variant = boost::variant<Types...>;

    template <typename T, typename... Types>
    constexpr T& get(variant<Types...>& v)
    {
        return boost::get<T>(v);
    }

    template <typename T, typename... Types>
    constexpr T&& get(variant<Types...>&& v)
    {
        return boost::get<T>(v);
    }

    template <typename T, typename... Types>
    constexpr const T& get(const variant<Types...>& v)
    {
        return boost::get<T>(v);
    }

    template <typename T, typename... Types>
    constexpr const T& get(const variant<Types...>&& v)
    {
        return boost::get<T>(v);
    }

    template <typename... Types>
    constexpr std::size_t index(const variant<Types...>& v)
    {
        return v.which();
    }
#else
    /*!
        \brief The alternate to std::variant.
    */
    template <typename... Types>
    using variant = std::variant<Types...>;

    /*!
        \brief The alternate to std::get().

        \tparam T     A return type.
        \tparam Types Parameter types.

        \param v A variant.

        \return The value.
    */
    template <typename T, typename... Types>
    constexpr T& get(variant<Types...>& v)
    {
        return std::get<T>(v);
    }

    /*!
        \brief The alternate to std::get().

        \tparam T     A return type.
        \tparam Types Parameter types.

        \param v A variant.

        \return The value.
    */
    template <typename T, typename... Types>
    constexpr T&& get(variant<Types...>&& v)
    {
        return std::get<T>(v);
    }

    /*!
        \brief The alternate to std::get().

        \tparam T     A return type.
        \tparam Types Variant template parameter types.

        \param v A variant.

        \return The value.
    */
    template <typename T, typename... Types>
    constexpr const T& get(const variant<Types...>& v)
    {
        return std::get<T>(v);
    }

    /*!
        \brief The alternate to std::get().

        \tparam T     A return type.
        \tparam Types Parameter types.

        \param v A variant.

        \return The value.
    */
    template <typename T, typename... Types>
    constexpr const T& get(const variant<Types...>&& v)
    {
        return std::get<T>(v);
    }

    /*!
        \brief The alternate to std::variant::index().

        \tparam Types Parameter types.

        \param v A variant.

        \return The index.
    */
    template <typename... Types>
    constexpr std::size_t index(const variant<Types...>& v)
    {
        return v.index();
    }
#endif
}


namespace tetengo2::stdalt {
#if (BOOST_COMP_CLANG && BOOST_COMP_CLANG < BOOST_VERSION_NUMBER(6, 0, 0)) || \
    (BOOST_COMP_GNUC && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(7, 0, 0))
    template <typename CharT, typename Traits = std::char_traits<CharT>>
    using basic_string_view = boost::basic_string_view<CharT>;
#else
    /*!
        \brief The alternate to std::basic_string_view.

        \tparam CharT  A character type.
        \tparam Traits A traits type.
    */
    template <typename CharT, typename Traits = std::char_traits<CharT>>
    using basic_string_view = std::basic_string_view<CharT>;
#endif

    /*!
        \brief The alternate to std::string_view.
    */
    using string_view = basic_string_view<char>;

    /*!
        \brief The alternate to std::wstring_view.
    */
    using wstring_view = basic_string_view<wchar_t>;

    /*!
        \brief The alternate to std::u16string_view.
    */
    using u16string_view = basic_string_view<char16_t>;

    /*!
        \brief The alternate to std::u32string_view.
    */
    using u32string_view = basic_string_view<char32_t>;
}


#endif

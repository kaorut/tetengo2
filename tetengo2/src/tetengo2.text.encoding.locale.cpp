/*! \file
    \brief The definition of tetengo2::text::encoding::locale.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <cassert>
#include <cwchar>
#include <iterator>
#include <locale>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>
#include <boost/throw_exception.hpp>

#if BOOST_OS_WINDOWS
#   include <tetengo2/detail/windows/encoding.h>
#elif BOOST_OS_LINUX
#   include <tetengo2/detail/unixos/encoding.h>
#else
#   error Unsupported platform.
#endif
#include <tetengo2/text.h>
#include <tetengo2/text/encoding/locale.h>


namespace tetengo2 { namespace text { namespace encoding
{
    template <typename String>
    class locale<String>::impl : private boost::noncopyable
    {
    public:
        // types

        using base_type = typename locale::base_type;

        using string_type = typename locale::string_type;

        using encoding_details_type = typename locale::encoding_details_type;


        // constructors and destructors

        impl()
        :
        m_locale(),
#if BOOST_OS_WINDOWS
        m_encoding_details(tetengo2::detail::windows::encoding::instance())
#elif BOOST_OS_LINUX
        m_encoding_details(tetengo2::detail::unixos::encoding::instance())
#else
#   error Unsupported platform.
#endif
        {}

        explicit impl(std::locale locale_based_on)
        :
        m_locale(std::move(locale_based_on)),
#if BOOST_OS_WINDOWS
        m_encoding_details(tetengo2::detail::windows::encoding::instance())
#elif BOOST_OS_LINUX
        m_encoding_details(tetengo2::detail::unixos::encoding::instance())
#else
#   error Unsupported platform.
#endif
        {}


        // functions

        const std::locale& locale_based_on()
        const
        {
            return m_locale;
        }

        string_type from_pivot_impl(const typename base_type::pivot_type& pivot)
        const
        {
            return from_pivot_impl2(pivot);
        }

        typename base_type::pivot_type to_pivot_impl(const string_type& string)
        const
        {
            return to_pivot_impl2(string);
        }


    private:
        // type

        using pivot_char_type = typename base_type::pivot_type::value_type;

        using string_char_type = typename string_type::value_type;

        using converter_type = std::codecvt<pivot_char_type, string_char_type, std::mbstate_t>;


        // variables

        const std::locale m_locale;

        const encoding_details_type& m_encoding_details;


        // functions

        template <typename Pivot>
        string_type from_pivot_impl2(
            Pivot&& pivot,
            const typename std::enable_if<std::is_convertible<Pivot, string_type>::value>::type* const = nullptr
        )
        const
        {
            return std::move(pivot);
        }

        template <typename Pivot>
        string_type from_pivot_impl2(
            Pivot&& pivot,
            const typename std::enable_if<!std::is_convertible<Pivot, string_type>::value>::type* const = nullptr
        )
        const
        {
            return from_pivot_impl3(std::move(pivot));
        }

        string_type from_pivot_impl3(const typename base_type::pivot_type& pivot)
        const
        {
            if (pivot.empty())
                return string_type{};
            if (!std::has_facet<converter_type>(m_locale))
                return string_type{ pivot.begin(), pivot.end() };

            const auto& converter = std::use_facet<converter_type>(m_locale);
            auto state = std::mbstate_t();

            const auto* p_pivot_first = pivot.c_str();
            const auto* const p_pivot_last = p_pivot_first + pivot.length();

            std::vector<string_char_type> string_chars{ 8, TETENGO2_TEXT('\0') };
            auto* p_string_first = string_chars.data();
            auto* p_string_last = p_string_first + string_chars.size() - 1;

            for (;;)
            {
                const pivot_char_type* p_pivot_next = nullptr;
                string_char_type* p_string_next = nullptr;

                const auto result =
                    converter.out(
                        state, p_pivot_first, p_pivot_last, p_pivot_next, p_string_first, p_string_last, p_string_next
                    );
                if (p_pivot_next == p_pivot_last)
                {
                    unshift(converter, state, string_chars, p_string_next, p_string_last, p_string_next);
                    assert(*p_string_next == static_cast<string_char_type>(TETENGO2_TEXT('\0')));
                    return string_type{ string_chars.data(), p_string_next };
                }

                if (result == converter_type::error)
                {
                    *p_string_next = TETENGO2_TEXT('?');
                    ++p_pivot_next;
                    ++p_string_next;
                }
                else
                {
                    expand_destination(string_chars, p_string_first, p_string_last, p_string_next);
                }

                p_pivot_first = p_pivot_next;
                p_string_first = p_string_next;
            }
        }

        void unshift(
            const converter_type&          converter,
            std::mbstate_t&                state,
            std::vector<string_char_type>& string_chars,
            string_char_type*              p_string_first,
            string_char_type*              p_string_last,
            string_char_type*&             p_string_next
        )
        const
        {
            for (;;)
            {
                const auto result = converter.unshift(state, p_string_first, p_string_last, p_string_next);
                if (result == converter_type::error)
                    BOOST_THROW_EXCEPTION((std::invalid_argument{ "Can't unshift the string." }));

                if (result == converter_type::ok || result == converter_type::noconv)
                    break;

                expand_destination(string_chars, p_string_first, p_string_last, p_string_next);

                p_string_first = p_string_next;
            }
        }

        template <typename Str>
        typename base_type::pivot_type to_pivot_impl2(
            Str&& string,
            const typename std::enable_if<
                std::is_convertible<Str, typename base_type::pivot_type>::value
            >::type* const = nullptr
        )
        const
        {
            return std::move(string);
        }

        template <typename Str>
        typename base_type::pivot_type to_pivot_impl2(
            Str&& string,
            const typename std::enable_if<
                !std::is_convertible<Str, typename base_type::pivot_type>::value
            >::type* const = nullptr
        )
        const
        {
            return to_pivot_impl3(std::move(string));
        }

        typename base_type::pivot_type to_pivot_impl3(const string_type& string)
        const
        {
            if (string.empty())
                return typename base_type::pivot_type{};
            if (!std::has_facet<converter_type>(m_locale))
                return typename base_type::pivot_type{ string.begin(), string.end() };

            const converter_type& converter = std::use_facet<converter_type>(m_locale);
            auto state = std::mbstate_t();

            const auto* p_string_first = string.c_str();
            const string_char_type* const p_string_last = p_string_first + string.length();

            std::vector<pivot_char_type> pivot_chars{ 8, TETENGO2_TEXT('\0') };
            auto* p_pivot_first = pivot_chars.data();
            pivot_char_type* p_pivot_last = p_pivot_first + pivot_chars.size() - 1;

            for (;;)
            {
                const string_char_type* p_string_next = nullptr;
                pivot_char_type* p_pivot_next = nullptr;

                const typename converter_type::result result =
                    converter.in(
                        state, p_string_first, p_string_last, p_string_next, p_pivot_first, p_pivot_last, p_pivot_next
                    );
                if (p_string_next == p_string_last)
                {
                    assert(*p_pivot_next == static_cast<pivot_char_type>(TETENGO2_TEXT('\0')));
                    return typename base_type::pivot_type{ pivot_chars.data(), p_pivot_next };
                }

                if (result == converter_type::error)
                {
                    *p_pivot_next = TETENGO2_TEXT('?');
                    ++p_string_next;
                    ++p_pivot_next;
                }
                else
                {
                    expand_destination(pivot_chars, p_pivot_first, p_pivot_last, p_pivot_next);
                }

                p_string_first = p_string_next;
                p_pivot_first = p_pivot_next;
            }
        }

        template <typename Char>
        void expand_destination(std::vector<Char>& chars, Char*& p_first, Char*& p_last, Char*& p_next)
        const
        {
            const typename std::vector<Char>::difference_type first_offset = std::distance(chars.data(), p_first);
            const typename std::vector<Char>::difference_type next_offset = std::distance(chars.data(), p_next);

            chars.resize(chars.size() * 2, TETENGO2_TEXT('\0'));

            p_first = chars.data() + first_offset;
            p_last = chars.data() + chars.size() - 1;
            p_next = chars.data() + next_offset;
        }


    };


    template <typename String>
    locale<String>::locale()
    :
    m_p_impl(std::make_shared<impl>())
    {}

    template <typename String>
    locale<String>::locale(std::locale locale_based_on)
    :
    m_p_impl(std::make_shared<impl>(std::move(locale_based_on)))
    {}

    template <typename String>
    locale<String>::~locale()
    = default;

    template <typename String>
    const std::locale& locale<String>::locale_based_on()
    const
    {
        return m_p_impl->locale_based_on();
    }

    template <typename S>
    bool operator==(const locale<S>& one, const locale<S>& another)
    {
        return one.locale_based_on() == another.locale_based_on();
    }

    template <typename String>
    typename locale<String>::string_type locale<String>::from_pivot_impl(const pivot_type& pivot)
    const
    {
        return m_p_impl->from_pivot_impl(pivot);
    }

    template <typename String>
    typename locale<String>::pivot_type locale<String>::to_pivot_impl(const string_type& string)
    const
    {
        return m_p_impl->to_pivot_impl(string);
    }


    template class locale<std::string>;

    template class locale<std::wstring>;

    template bool operator==(const locale<std::string>& one, const locale<std::string>& another);

    template bool operator==(const locale<std::wstring>& one, const locale<std::wstring>& another);


}}}

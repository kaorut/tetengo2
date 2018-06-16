/*! \file
    \brief The definition of tetengo2::text::encoding::locale.

    Copyright (C) 2007-2018 kaoru

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
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/encoding.h>
#include <tetengo2/detail/base/impl_set.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoding/locale.h>


namespace tetengo2::text::encoding {
    template <typename String>
    class locale<String>::impl : private boost::noncopyable
    {
    public:
        // types

        using base_type = typename locale::base_type;

        using pivot_type = typename locale::pivot_type;

        using string_type = typename locale::string_type;


        // constructors and destructors

        impl() : m_locale{} {}

        explicit impl(std::locale locale_based_on) : m_locale{ std::move(locale_based_on) } {}


        // functions

        const std::locale& locale_based_on() const
        {
            return m_locale;
        }

        const std::string& name_impl() const
        {
            static const std::string multibyte("LocaleMultibyte");
            static const std::string wide("LocaleWide");
            return sizeof(typename string_type::value_type) == 1 ? multibyte : wide;
        }

        string_type from_pivot_impl(pivot_type pivot) const
        {
            switch (detail::detail_impl_set().encoding_().pivot_type_())
            {
            case pivot_type_type::std_string:
                if (tetengo2::stdalt::index(pivot) != 0)
                    pivot = std::string{};
                return from_pivot_impl2(std::move(tetengo2::stdalt::get<std::string>(pivot)));
            case pivot_type_type::std_wstring:
                if (tetengo2::stdalt::index(pivot) != 1)
                    pivot = std::wstring{};
                return from_pivot_impl2(std::move(tetengo2::stdalt::get<std::wstring>(pivot)));
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("Unknown pivot type."));
            }
        }

        pivot_type to_pivot_impl(string_type string) const
        {
            switch (detail::detail_impl_set().encoding_().pivot_type_())
            {
            case pivot_type_type::std_string:
                return pivot_type{ to_pivot_impl2<std::string>(std::move(string)) };
            case pivot_type_type::std_wstring:
                return pivot_type{ to_pivot_impl2<std::wstring>(std::move(string)) };
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("Unknown pivot type."));
            }
        }


    private:
        // type

        using string_char_type = typename string_type::value_type;

        using pivot_type_type = detail::base::encoding::pivot_type_type;

        template <typename Pivot>
        using converter_type = std::codecvt<typename Pivot::value_type, string_char_type, std::mbstate_t>;


        // variables

        const std::locale m_locale;


        // functions

        template <typename Pivot>
        string_type from_pivot_impl2(
            Pivot&& pivot,
            const typename std::enable_if<std::is_convertible<Pivot, string_type>::value>::type* const = nullptr) const
        {
            return std::move(pivot);
        }

        template <typename Pivot>
        string_type from_pivot_impl2(
            Pivot&& pivot,
            const typename std::enable_if<!std::is_convertible<Pivot, string_type>::value>::type* const = nullptr) const
        {
            return from_pivot_impl3(std::move(pivot));
        }

        template <typename Pivot>
        string_type from_pivot_impl3(Pivot pivot) const
        {
            if (pivot.empty())
                return string_type{};
            if (!std::has_facet<converter_type<Pivot>>(m_locale))
                return string_type{ pivot.begin(), pivot.end() };

            const auto& converter = std::use_facet<converter_type<Pivot>>(m_locale);
            auto        state = std::mbstate_t();

            const auto*       p_pivot_first = pivot.c_str();
            const auto* const p_pivot_last = p_pivot_first + pivot.length();

            std::vector<string_char_type> string_chars{ 8, TETENGO2_TEXT('\0') };
            auto*                         p_string_first = string_chars.data();
            auto*                         p_string_last = p_string_first + string_chars.size() - 1;

            for (;;)
            {
                const typename Pivot::value_type* p_pivot_next = nullptr;
                string_char_type*                 p_string_next = nullptr;

                const auto result = converter.out(
                    state, p_pivot_first, p_pivot_last, p_pivot_next, p_string_first, p_string_last, p_string_next);
                if (p_pivot_next == p_pivot_last)
                {
                    unshift<Pivot>(converter, state, string_chars, p_string_next, p_string_last, p_string_next);
                    assert(*p_string_next == static_cast<string_char_type>(TETENGO2_TEXT('\0')));
                    return string_type{ string_chars.data(), p_string_next };
                }

                if (result == converter_type<Pivot>::error)
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

        template <typename Pivot>
        void unshift(
            const converter_type<Pivot>&   converter,
            std::mbstate_t&                state,
            std::vector<string_char_type>& string_chars,
            string_char_type*              p_string_first,
            string_char_type*              p_string_last,
            string_char_type*&             p_string_next) const
        {
            for (;;)
            {
                const auto result = converter.unshift(state, p_string_first, p_string_last, p_string_next);
                if (result == converter_type<Pivot>::error)
                    BOOST_THROW_EXCEPTION((std::invalid_argument{ "Can't unshift the string." }));

                if (result == converter_type<Pivot>::ok || result == converter_type<Pivot>::noconv)
                    break;

                expand_destination(string_chars, p_string_first, p_string_last, p_string_next);

                p_string_first = p_string_next;
            }
        }

        template <typename Pivot, typename Str>
        Pivot to_pivot_impl2(
            Str&& string,
            const typename std::enable_if<std::is_convertible<Str, Pivot>::value>::type* const = nullptr) const
        {
            return std::move(string);
        }

        template <typename Pivot, typename Str>
        Pivot to_pivot_impl2(
            Str&& string,
            const typename std::enable_if<!std::is_convertible<Str, Pivot>::value>::type* const = nullptr) const
        {
            return to_pivot_impl3<Pivot>(std::move(string));
        }

        template <typename Pivot>
        Pivot to_pivot_impl3(const string_type& string) const
        {
            if (string.empty())
                return Pivot{};
            if (!std::has_facet<converter_type<Pivot>>(m_locale))
                return Pivot{ string.begin(), string.end() };

            const converter_type<Pivot>& converter = std::use_facet<converter_type<Pivot>>(m_locale);
            auto                         state = std::mbstate_t();

            const auto*                   p_string_first = string.c_str();
            const string_char_type* const p_string_last = p_string_first + string.length();

            std::vector<typename Pivot::value_type> pivot_chars{ 8, TETENGO2_TEXT('\0') };
            auto*                                   p_pivot_first = pivot_chars.data();
            typename Pivot::value_type*             p_pivot_last = p_pivot_first + pivot_chars.size() - 1;

            for (;;)
            {
                const string_char_type*     p_string_next = nullptr;
                typename Pivot::value_type* p_pivot_next = nullptr;

                const typename converter_type<Pivot>::result result = converter.in(
                    state, p_string_first, p_string_last, p_string_next, p_pivot_first, p_pivot_last, p_pivot_next);
                if (p_string_next == p_string_last)
                {
                    assert(*p_pivot_next == static_cast<typename Pivot::value_type>(TETENGO2_TEXT('\0')));
                    return Pivot{ pivot_chars.data(), p_pivot_next };
                }

                if (result == converter_type<Pivot>::error)
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
        void expand_destination(std::vector<Char>& chars, Char*& p_first, Char*& p_last, Char*& p_next) const
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
    locale<String>::locale() : m_p_impl{ std::make_shared<impl>() }
    {}

    template <typename String>
    locale<String>::locale(std::locale locale_based_on) : m_p_impl{ std::make_shared<impl>(std::move(locale_based_on)) }
    {}

    template <typename String>
    locale<String>::~locale() = default;

    template <typename String>
    const std::locale& locale<String>::locale_based_on() const
    {
        return m_p_impl->locale_based_on();
    }

    template <typename String>
    const std::string& locale<String>::name_impl() const
    {
        return m_p_impl->name_impl();
    }

    template <typename S>
    bool operator==(const locale<S>& one, const locale<S>& another)
    {
        return one.locale_based_on() == another.locale_based_on();
    }

    template <typename S>
    bool operator!=(const locale<S>& one, const locale<S>& another)
    {
        return !operator==(one, another);
    }

    template <typename String>
    typename locale<String>::string_type locale<String>::from_pivot_impl(pivot_type pivot) const
    {
        return m_p_impl->from_pivot_impl(pivot);
    }

    template <typename String>
    typename locale<String>::pivot_type locale<String>::to_pivot_impl(string_type string) const
    {
        return m_p_impl->to_pivot_impl(string);
    }


    template class locale<std::string>;

    template class locale<std::wstring>;

    template bool operator==(const locale<std::string>& one, const locale<std::string>& another);

    template bool operator==(const locale<std::wstring>& one, const locale<std::wstring>& another);

    template bool operator!=(const locale<std::string>& one, const locale<std::string>& another);

    template bool operator!=(const locale<std::wstring>& one, const locale<std::wstring>& another);
}

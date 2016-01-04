/*! \file
    \brief The definition of tetengo2::text::encoding::locale.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODING_LOCALE_H)
#define TETENGO2_TEXT_ENCODING_LOCALE_H

#include <cassert>
#include <cwchar>
#include <iterator>
#include <locale>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/operators.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/text.h>
#include <tetengo2/text/encoding/encoding.h>


namespace tetengo2 { namespace text { namespace encoding
{
    /*!
        \brief The class template for an encoding based on a locale.

        \tparam String          A string type.
        \tparam EncodingDetails A detail implementation type of an encoding.
    */
    template <typename String, typename EncodingDetails>
    class locale :
        public encoding<EncodingDetails>,
        private boost::equality_comparable<locale<String, EncodingDetails>>
    {
    public:
        // types

        //! The base type.
        using base_type = encoding<EncodingDetails>;

        //! The string type.
        using string_type = String;


        // constructors and destructor

        /*!
            \brief Creates an encoding based on the current locale.
        */
        locale()
        :
        m_locale()
        {}

        /*!
            \brief Creates an encoding based on a locale.

            \param locale_based_on A locale based on.
        */
        explicit locale(std::locale locale_based_on)
        :
        m_locale(std::move(locale_based_on))
        {}


        // functions

        /*!
            \brief Checks whether one encoding based on a locale is equal to another.

            \param one     One encoding based on a locale.
            \param another Another encoding based on a locale.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const locale& one, const locale& another)
        {
            return one.m_locale == another.m_locale;
        }

        /*!
            \brief Returns the locale based on.

            \return The locale based on.
        */
        const std::locale& locale_based_on()
        const
        {
            return m_locale;
        }

        /*!
            \brief Translates a string from the pivot encoding.

            \param pivot A pivot string.

            \return A translated string.

            \throw std::invalid_argument When the string cannot be translated.
        */
        string_type from_pivot(typename base_type::pivot_type pivot)
        const
        {
            return from_pivot_impl(std::move(pivot));
        }

        /*!
            \brief Translates a string to the pivot encoding.

            \param string A string.

            \return A translated pivot string.

            \throw std::invalid_argument When the string cannot be translated.
        */
        typename base_type::pivot_type to_pivot(string_type string)
        const
        {
            return to_pivot_impl(std::move(string));
        }


    private:
        // type

        using pivot_char_type = typename base_type::pivot_type::value_type;

        using string_char_type = typename string_type::value_type;

        using converter_type = std::codecvt<pivot_char_type, string_char_type, std::mbstate_t>;


        // variables

        std::locale m_locale;


        // functions

        template <typename Pivot>
        string_type from_pivot_impl(
            Pivot&& pivot,
            const typename std::enable_if<std::is_convertible<Pivot, string_type>::value>::type* const = nullptr
        )
        const
        {
            return std::move(pivot);
        }

        template <typename Pivot>
        string_type from_pivot_impl(
            Pivot&& pivot,
            const typename std::enable_if<!std::is_convertible<Pivot, string_type>::value>::type* const = nullptr
        )
        const
        {
            return from_pivot_impl_impl(std::move(pivot));
        }

        string_type from_pivot_impl_impl(const typename base_type::pivot_type& pivot)
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
        typename base_type::pivot_type to_pivot_impl(
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
        typename base_type::pivot_type to_pivot_impl(
            Str&& string,
            const typename std::enable_if<
                !std::is_convertible<Str, typename base_type::pivot_type>::value
            >::type* const = nullptr
        )
        const
        {
            return to_pivot_impl_impl(std::move(string));
        }

        typename base_type::pivot_type to_pivot_impl_impl(const string_type& string)
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


}}}


#endif

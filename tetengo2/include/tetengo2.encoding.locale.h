/*! \file
    \brief The definition of tetengo2::encoding::locale.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODING_LOCALE_H)
#define TETENGO2_ENCODING_LOCALE_H

#include <cassert>
#include <cstddef>
#include <cwchar>
#include <iterator>
#include <locale>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/operators.hpp>
#include <boost/throw_exception.hpp>

#include "tetengo2.text.h"
#include "tetengo2.encoding.encoding.h"


namespace tetengo2 { namespace encoding
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
        typedef encoding<EncodingDetails> base_type;

        //! The string type.
        typedef String string_type;

        //! The string character type.
        typedef typename string_type::value_type string_char_type;


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

            \tparam L A locale type.

            \param locale_based_on A locale based on.
        */
        template <typename L>
        explicit locale(L&& locale_based_on)
        :
        m_locale(std::forward<L>(locale_based_on))
        {}


        // functions

        /*!
            \brief Checks whether one encoding based on a locale is equal to
                   another.

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

            \tparam P A pivot type.

            \param pivot A pivot string.

            \return A translated string.
        */
        template <typename P>
        string_type from_pivot(P&& pivot)
        const
        {
            return from_pivot_impl(std::forward<P>(pivot));
        }

        /*!
            \brief Translates a string to the pivot encoding.

            \tparam S A string type.

            \param string A string.

            \return A translated pivot string.
        */
        template <typename S>
        typename base_type::pivot_type to_pivot(S&& string)
        const
        {
            return to_pivot_impl(std::forward<S>(string));
        }


    private:
        // type

        typedef
            std::codecvt<
                typename base_type::pivot_char_type,
                string_char_type,
                std::mbstate_t
            >
            converter_type;


        // variables

        std::locale m_locale;


        // functions

        template <typename Pivot>
        string_type from_pivot_impl(
            Pivot&& pivot,
            const typename std::enable_if<
                std::is_convertible<Pivot, string_type>::value
            >::type* const = NULL
        )
        const
        {
            return std::forward<Pivot>(pivot);
        }

        template <typename Pivot>
        string_type from_pivot_impl(
            const Pivot& pivot,
            const typename std::enable_if<
                !std::is_convertible<Pivot, string_type>::value
            >::type* const = NULL
        )
        const
        {
            if (!std::has_facet<converter_type>(m_locale))
                return string_type(pivot.begin(), pivot.end());

            const converter_type& converter =
                std::use_facet<converter_type>(m_locale);
            std::mbstate_t state = std::mbstate_t();

            const typename base_type::pivot_char_type* p_pivot_first =
                pivot.c_str();
            const typename base_type::pivot_char_type* const p_pivot_last =
                p_pivot_first + pivot.length();

            std::vector<string_char_type> string_chars(
                8, TETENGO2_TEXT('\0')
            );
            string_char_type* p_string_first = string_chars.data();
            string_char_type* p_string_last =
                p_string_first + string_chars.size() - 1;

            for (;;)
            {
                const typename base_type::pivot_char_type* p_pivot_next =
                    NULL;
                string_char_type* p_string_next = NULL;

                const typename converter_type::result result =
                    converter.out(
                        state,
                        p_pivot_first,
                        p_pivot_last,
                        p_pivot_next,
                        p_string_first,
                        p_string_last,
                        p_string_next
                    );
                if (p_pivot_next == p_pivot_last)
                {
                    unshift(
                        converter,
                        state,
                        string_chars,
                        p_string_next,
                        p_string_last,
                        p_string_next
                    );
                    assert(
                        *p_string_next ==
                        static_cast<string_char_type>(TETENGO2_TEXT('\0'))
                    );
                    return string_type(string_chars.data(), p_string_next);
                }

                if (result == converter_type::error)
                {
                    *p_string_next = TETENGO2_TEXT('?');
                    ++p_pivot_next;
                    ++p_string_next;
                }
                else
                {
                    expand_destination(
                        string_chars,
                        p_string_first,
                        p_string_last,
                        p_string_next
                    );
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
                const typename converter_type::result result =
                    converter.unshift(
                        state, p_string_first, p_string_last, p_string_next
                    );
                if (result == converter_type::error)
                {
                    BOOST_THROW_EXCEPTION(
                        std::runtime_error("Can't unshift the string.")
                    );
                }

                if (
                    result == converter_type::ok ||
                    result == converter_type::noconv
                )
                {
                    break;
                }

                expand_destination(
                    string_chars, p_string_first, p_string_last, p_string_next
                );

                p_string_first = p_string_next;
            }
        }

        template <typename Str>
        typename base_type::pivot_type to_pivot_impl(
            Str&& string,
            const typename std::enable_if<
                std::is_convertible<
                    Str, typename base_type::pivot_type
                >::value
            >::type* const = NULL
        )
        const
        {
            return std::forward<Str>(string);
        }

        template <typename Str>
        typename base_type::pivot_type to_pivot_impl(
            const Str& string,
            const typename std::enable_if<
                !std::is_convertible<
                    Str, typename base_type::pivot_type
                >::value
            >::type* const = NULL
        )
        const
        {
            if (!std::has_facet<converter_type>(m_locale))
            {
                return typename base_type::pivot_type(
                    string.begin(), string.end()
                );
            }

            const converter_type& converter =
                std::use_facet<converter_type>(m_locale);
            std::mbstate_t state = std::mbstate_t();

            const string_char_type* p_string_first = string.c_str();
            const string_char_type* const p_string_last =
                p_string_first + string.length();

            std::vector<typename base_type::pivot_char_type> pivot_chars(
                8, TETENGO2_TEXT('\0')
            );
            typename base_type::pivot_char_type* p_pivot_first =
                pivot_chars.data();
            typename base_type::pivot_char_type* p_pivot_last =
                p_pivot_first + pivot_chars.size() - 1;

            for (;;)
            {
                const string_char_type* p_string_next = NULL;
                typename base_type::pivot_char_type* p_pivot_next = NULL;

                const typename converter_type::result result =
                    converter.in(
                        state,
                        p_string_first,
                        p_string_last,
                        p_string_next,
                        p_pivot_first,
                        p_pivot_last,
                        p_pivot_next
                    );
                if (p_string_next == p_string_last)
                {
                    assert(
                        *p_pivot_next ==
                        static_cast<typename base_type::pivot_char_type>(
                            TETENGO2_TEXT('\0')
                        )
                    );
                    return typename base_type::pivot_type(
                        pivot_chars.data(), p_pivot_next
                    );
                }

                if (result == converter_type::error)
                {
                    *p_pivot_next = TETENGO2_TEXT('?');
                    ++p_string_next;
                    ++p_pivot_next;
                }
                else
                {
                    expand_destination(
                        pivot_chars, p_pivot_first, p_pivot_last, p_pivot_next
                    );
                }

                p_string_first = p_string_next;
                p_pivot_first = p_pivot_next;
            }
        }

        template <typename Char>
        void expand_destination(
            std::vector<Char>& chars,
            Char*&             p_first,
            Char*&             p_last,
            Char*&             p_next
        )
        const
        {
            const typename std::vector<Char>::difference_type first_offset =
                std::distance(chars.data(), p_first);
            const typename std::vector<Char>::difference_type next_offset =
                std::distance(chars.data(), p_next);

            chars.resize(chars.size() * 2, TETENGO2_TEXT('\0'));

            p_first = chars.data() + first_offset;
            p_last = chars.data() + chars.size() - 1;
            p_next = chars.data() + next_offset;
        }


    };


}}


#endif

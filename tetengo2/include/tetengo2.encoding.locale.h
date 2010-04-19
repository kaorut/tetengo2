/*! \file
    \brief The definition of tetengo2::encoding::locale.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODING_LOCALE_H)
#define TETENGO2_ENCODING_LOCALE_H

#include <cassert>
#include <cstddef>
#include <cwchar>
#include <limits>
#include <locale>
#include <stdexcept>
#include <vector>

//#include <boost/concept_check.hpp>
#include <boost/scoped_array.hpp>
//#include <boost/swap.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility.hpp>

#include "concept_tetengo2.String.h"
#include "tetengo2.assignable.h"
#include "tetengo2.swappable.h"
#include "tetengo2.text.h"
#include "tetengo2.encoding.encoding.h"


namespace tetengo2 { namespace encoding
{
    /*!
        \brief The class template for an encoding based on a locale.

        \tparam String A string type. It must conform to
                       concept_tetengo2::String<String>.
    */
    template <typename String>
    class locale :
        public encoding,
        public assignable<locale<String> >,
        private swappable<locale<String> >
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));


    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The string character type.
        typedef typename string_type::value_type string_char_type;


        // constructors and destructor

        /*!
            \brief Creates an encoding based on a locale.

            \param locale_based_on A locale based on.
        */
        explicit locale(const std::locale& locale_based_on = std::locale())
        :
        m_locale(locale_based_on)
        {}

        /*!
            \brief Copies an encoding based on a locale.

            \param another Another encoding based on a locale.
        */
        locale(const locale& another)
        :
        m_locale(another.m_locale)
        {}

        /*!
            \brief Destroys the encoding based on a locale.
        */
        ~locale()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another encoding based on a locale.

            \param another Another encoding based on a locale.
        */
        void swap(locale& another)
        throw ()
        {
            boost::swap(m_locale, another.m_locale);
        }

        /*!
            \brief Assigns another encoding based on a locale.

            \param another Another encoding based on a locale.

            \return this object.
        */
        locale& operator=(const locale& another)
        {
            return assign(another);
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
        */
        string_type from_pivot(const pivot_type& pivot)
        const
        {
            return from_pivot_impl(pivot);
        }

        /*!
            \brief Translates a string to the pivot encoding.

            \param string A string.

            \return A translated pivot string.
        */
        pivot_type to_pivot(const string_type& string)
        const
        {
            return to_pivot_impl(string);
        }


    private:
        // type

        typedef
            std::codecvt<pivot_char_type, string_char_type, std::mbstate_t>
            converter_type;


        // variables

        std::locale m_locale;


        // functions

        template <typename Pivot>
        string_type from_pivot_impl(
            const Pivot& pivot,
            const typename boost::enable_if<
                boost::is_same<Pivot, string_type>
            >::type* const = NULL
        )
        const
        {
            return pivot;
        }

        template <typename Pivot>
        string_type from_pivot_impl(
            const Pivot& pivot,
            const typename boost::disable_if<
                boost::is_same<Pivot, string_type>
            >::type* const = NULL
        )
        const
        {
            if (!std::has_facet<converter_type>(m_locale))
                return string_type(pivot.begin(), pivot.end());

            const converter_type& converter =
                std::use_facet<converter_type>(m_locale);
            std::mbstate_t state = std::mbstate_t();

            const pivot_char_type* p_pivot_first = pivot.c_str();
            const pivot_char_type* const p_pivot_last =
                p_pivot_first + pivot.length();

            std::vector<string_char_type> string_chars(
                8, TETENGO2_TEXT('\0')
            );
            string_char_type* p_string_first = &string_chars[0];
            string_char_type* p_string_last =
                p_string_first + string_chars.size() - 1;

            for (;;)
            {
                const pivot_char_type* p_pivot_next = NULL;
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
                    return string_type(&string_chars[0], p_string_next);
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
            const converter_type& converter,
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
        pivot_type to_pivot_impl(
            const Str& string,
            const typename boost::enable_if<
                boost::is_same<pivot_type, Str>
            >::type* const = NULL
        )
        const
        {
            return string;
        }

        template <typename Str>
        pivot_type to_pivot_impl(
            const Str& string,
            const typename boost::disable_if<
                boost::is_same<pivot_type, Str>
            >::type* const = NULL
        )
        const
        {
            if (!std::has_facet<converter_type>(m_locale))
                return pivot_type(string.begin(), string.end());

            const converter_type& converter =
                std::use_facet<converter_type>(m_locale);

            const std::size_t pivot_max_length =
                calc_pivot_max_length(converter, string);

            return convert_to_pivot(converter, string, pivot_max_length);
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
                std::distance(&chars[0], p_first);
            const typename std::vector<Char>::difference_type next_offset =
                std::distance(&chars[0], p_next);

            chars.resize(chars.size() * 2, TETENGO2_TEXT('\0'));

            p_first = &chars[0] + first_offset;
            p_last = &chars[0] + chars.size() - 1;
            p_next = &chars[0] + next_offset;
        }

        typename pivot_type::size_type calc_pivot_max_length(
            const converter_type& converter,
            const string_type&    string
        )
        const
        {
            std::mbstate_t state = std::mbstate_t();

            return converter.length(
                state,
                string.c_str(),
                string.c_str() + string.length(),
                std::numeric_limits<std::size_t>::max()
            ) + 1;
        }

        pivot_type convert_to_pivot(
            const converter_type&                converter,
            const string_type&                   string,
            const typename pivot_type::size_type pivot_max_length
        )
        const
        {
            std::mbstate_t state = std::mbstate_t();

            const string_char_type* p_string_next = NULL;

            boost::scoped_array<pivot_char_type> p_pivot(
                new pivot_char_type[pivot_max_length]
            );
            pivot_char_type* p_pivot_next = NULL;
            
            const typename converter_type::result result =
                converter.in(
                    state,
                    string.c_str(),
                    string.c_str() + string.length(),
                    p_string_next,
                    p_pivot.get(),
                    p_pivot.get() + pivot_max_length,
                    p_pivot_next
                );
            
            if (result == converter_type::ok)
            {
                *p_pivot_next = TETENGO2_TEXT('\0');
                return pivot_type(p_pivot.get());
            }
            else if (result == converter_type::noconv)
            {
                assert(string.length() + 1 == pivot_max_length);
                return pivot_type(string.begin(), string.end());
            }
            else
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't convert string to pivot.")
                );
            }
        }


    };


}}


#endif

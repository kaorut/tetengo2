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

//#include <boost/concept_check.hpp>
#include <boost/scoped_array.hpp>
//#include <boost/swap.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits.hpp>

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
            return from_pivot_impl(pivot, encodings_are_same_type());
        }

        /*!
            \brief Translates a string to the pivot encoding.

            \param string A string.

            \return A translated pivot string.
        */
        pivot_type to_pivot(const string_type& string)
        const
        {
            return to_pivot_impl(string, encodings_are_same_type());
        }


    private:
        // type

        typedef
            std::codecvt<pivot_char_type, string_char_type, std::mbstate_t>
            converter_type;

        typedef
            typename boost::is_same<pivot_type, string_type>::type
            encodings_are_same_type;


        // variables

        std::locale m_locale;


        // functions

        string_type from_pivot_impl(
            const pivot_type&       pivot,
            const boost::true_type& encodings_are_same
        )
        const
        {
            return pivot;
        }

        string_type from_pivot_impl(
            const pivot_type&        pivot,
            const boost::false_type& encodings_are_same
        )
        const
        {
            if (!std::has_facet<converter_type>(m_locale))
                return string_type(pivot.begin(), pivot.end());

            const converter_type& converter =
                std::use_facet<converter_type>(m_locale);

            const std::size_t string_max_length =
                (pivot.length() + 1) * converter.max_length();

            return convert_from_pivot(converter, pivot, string_max_length);
        }

        pivot_type to_pivot_impl(
            const string_type&      string,
            const boost::true_type& encodings_are_same
        )
        const
        {
            return string;
        }

        pivot_type to_pivot_impl(
            const string_type&       string,
            const boost::false_type& encodings_are_same
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

        string_type convert_from_pivot(
            const converter_type&                 converter,
            const pivot_type&                     pivot,
            const typename string_type::size_type string_max_length
        )
        const
        {
            std::mbstate_t state = std::mbstate_t();

            const pivot_char_type* p_pivot_next = NULL;

            boost::scoped_array<string_char_type> p_string(
                new string_char_type[string_max_length]
            );
            string_char_type* p_string_next = NULL;
            
            const typename converter_type::result result =
                converter.out(
                    state,
                    pivot.c_str(),
                    pivot.c_str() + pivot.length(),
                    p_pivot_next,
                    p_string.get(),
                    p_string.get() + string_max_length,
                    p_string_next
                );
            
            if (result == converter_type::ok)
            {
                *p_string_next = TETENGO2_TEXT('\0');
                return string_type(p_string.get());
            }
            else if (result == converter_type::noconv)
            {
                assert(pivot.length() + 1 == string_max_length);
                return string_type(pivot.begin(), pivot.end());
            }
            else
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't convert pivot to string.")
                );
            }
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

/*! \file
    \brief The definition of tetengo2::encoding::locale.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODING_LOCALE_H)
#define TETENGO2_ENCODING_LOCALE_H

//#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cwchar>
#include <locale>
#include <stdexcept>

//#include <boost/concept_check.hpp>
#include <boost/scoped_array.hpp>

#include "concept_tetengo2.String.h"
#include "tetengo2.assignable.h"
#include "tetengo2.text.h"
#include "tetengo2.encoding.encoding.h"


namespace tetengo2 { namespace encoding
{
    /*!
        \brief The class template for a encoding based on a locale.

        \tparam String A string type. It must conform to
                       concept_tetengo2::String<String>.
    */
    template <typename String>
    class locale : public encoding, public assignable<locale<String> >
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
        locale(const std::locale& locale_based_on = std::locale())
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
            std::swap(m_locale, another.m_locale);
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
            if (!std::has_facet<converter_type>(m_locale))
                return string_type(pivot.begin(), pivot.end());

            const converter_type& converter =
                std::use_facet<converter_type>(m_locale);

            const int string_max_length =
                (pivot.length() + 1) * converter.max_length();

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
                assert(
                    pivot.length() + 1 ==
                    static_cast<typename pivot_type::size_type>(
                        string_max_length
                    )
                );
                return string_type(pivot.begin(), pivot.end());
            }
            else
            {
                throw std::runtime_error("Can't convert pivot to string.");
            }
        }

        /*!
            \brief Translates a string to the pivot encoding.

            \param string A string.

            \return A translated pivot string.
        */
        pivot_type to_pivot(const string_type& string)
        const
        {
            return pivot_type();
        }


    private:
        // type

        typedef
            std::codecvt<pivot_char_type, string_char_type, std::mbstate_t>
            converter_type;


        // variables

        std::locale m_locale;


    };


}}


#endif

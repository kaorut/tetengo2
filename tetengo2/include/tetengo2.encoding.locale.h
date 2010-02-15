/*! \file
    \brief The definition of tetengo2::encoding::locale.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODING_LOCALE_H)
#define TETENGO2_ENCODING_LOCALE_H

#include <algorithm>
#include <locale>
#include <string>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.String.h"
#include "tetengo2.assignable.h"


namespace tetengo2 { namespace encoding
{
    /*!
        \brief The class template for a encoding based on a locale.

        \tparam String A string type. It must conform to
                       concept_tetengo2::String<String>.
    */
    template <typename String>
    class locale : public assignable<locale<String> >
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));


    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The pivot type.
        typedef std::wstring pivot_type;


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
            \brief Translates a string from the pivot encoding.

            \param string A string.

            \return A translated string.
        */
        string_type from_pivot(const pivot_type& string)
        const
        {
            return string_type();
        }

        /*!
            \brief Translates a string to the pivot encoding.

            \param string A string.

            \return A translated string.
        */
        pivot_type to_pivot(const string_type& string)
        const
        {
            return pivot_type();
        }


    private:
        // variables

        std::locale m_locale;


    };


}}


#endif

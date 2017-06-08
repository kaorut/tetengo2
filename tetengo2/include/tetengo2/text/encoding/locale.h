/*! \file
    \brief The definition of tetengo2::text::encoding::locale.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODING_LOCALE_H)
#define TETENGO2_TEXT_ENCODING_LOCALE_H

#include <locale>
#include <memory>
#include <stdexcept>

#include <boost/operators.hpp>

#include <tetengo2/detail/base/encoding.h>
#include <tetengo2/text/encoding/encoding.h>


namespace tetengo2 { namespace text { namespace encoding
{
    /*!
        \brief The class template for an encoding based on a locale.

        \tparam String A string type.
    */
    template <typename String>
    class locale : public encoding<String>, private boost::equality_comparable<locale<String>>
    {
    public:
        // types

        //! The base type.
        using base_type = encoding<String>;

        //! The pivot type.
        using pivot_type = typename base_type::pivot_type;

        //! The string type.
        using string_type = typename base_type::string_type;

        //! The encoding detail type.
        using encoding_details_type = tetengo2::detail::base::encoding;


        // constructors and destructor

        /*!
            \brief Creates an encoding based on the current locale.
        */
        locale();

        /*!
            \brief Creates an encoding based on a locale.

            \param locale_based_on A locale based on.
        */
        locale(std::locale locale_based_on);

        /*!
            \brief Destroys the encoding based on a locale.
        */
        virtual ~locale();


        // functions

        /*!
            \brief Checks whether one encoding based on a locale is equal to another.

            \tparam S A string type.

            \param one     One encoding based on a locale.
            \param another Another encoding based on a locale.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        template <typename S>
        friend bool operator==(const locale<S>& one, const locale<S>& another);

        /*!
            \brief Returns the locale based on.

            \return The locale based on.
        */
        const std::locale& locale_based_on()
        const;

        /*!
            \brief Translates a string from the pivot encoding.

            \param pivot A pivot string.

            \return A translated string.

            \throw std::invalid_argument When the string cannot be translated.
        */
        string_type from_pivot(const pivot_type& pivot)
        const;

        /*!
            \brief Translates a string to the pivot encoding.

            \param string A string.

            \return A translated pivot string.

            \throw std::invalid_argument When the string cannot be translated.
        */
        pivot_type to_pivot(const string_type& string)
        const;


    private:
        // type

        class impl;


        // variables

        std::shared_ptr<impl> m_p_impl;


    };


}}}


#endif

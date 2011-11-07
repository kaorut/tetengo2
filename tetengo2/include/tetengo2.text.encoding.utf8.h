/*! \file
    \brief The definition of tetengo2::encoding::utf8.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODING_UTF8_H)
#define TETENGO2_ENCODING_UTF8_H

#include <string>

#include <boost/operators.hpp>

#include "tetengo2.text.encoding.encoding.h"


namespace tetengo2 { namespace encoding
{
    /*!
        \brief The class template for a UTF-8 encoding.

        \tparam EncodingDetails A detail implementation type of an encoding.
    */
    template <typename EncodingDetails>
    class utf8 :
        public encoding<EncodingDetails>,
        private boost::equality_comparable<utf8<EncodingDetails>>
    {
    public:
        // types

        //! The base type.
        typedef encoding<EncodingDetails> base_type;

        //! The string type.
        typedef std::string string_type;

        //! The string character type.
        typedef string_type::value_type string_char_type;

        //! The detail implementation type of an encoding.
        typedef EncodingDetails encoding_details_type;


        // functions

        /*!
            \brief Checks whether one UTF-8 encoding is equal to another.

            \param one     One UTF-8 encoding.
            \param another Another UTF-8 encoding.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const utf8& one, const utf8& another)
        {
            return true;
        }

        /*!
            \brief Translates a string from the pivot encoding.

            \param pivot A pivot string.

            \return A translated string.
        */
        string_type from_pivot(const typename base_type::pivot_type& pivot)
        const
        {
            return encoding_details_type::pivot_to_utf8(pivot);
        }

        /*!
            \brief Translates a string to the pivot encoding.

            \param string A string.

            \return A translated pivot string.
        */
        typename base_type::pivot_type to_pivot(const string_type& string)
        const
        {
            return encoding_details_type::utf8_to_pivot(string);
        }


    };


}}


#endif

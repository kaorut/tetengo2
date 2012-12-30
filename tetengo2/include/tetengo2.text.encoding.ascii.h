/*! \file
    \brief The definition of tetengo2::text::encoding::ascii.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODING_ASCII_H)
#define TETENGO2_TEXT_ENCODING_ASCII_H

#include <stdexcept>
#include <string>

#include <boost/iterator/transform_iterator.hpp>
#include <boost/operators.hpp>
#include <boost/throw_exception.hpp>

#include "tetengo2.text.encoding.encoding.h"


namespace tetengo2 { namespace text { namespace encoding
{
    /*!
        \brief The class template for an ASCII encoding.

        \tparam EncodingDetails A detail implementation type of an encoding.
    */
    template <typename EncodingDetails>
    class ascii : public encoding<EncodingDetails>, private boost::equality_comparable<ascii<EncodingDetails>>
    {
    public:
        // types

        //! The base type.
        typedef encoding<EncodingDetails> base_type;

        //! The string type.
        typedef std::string string_type;

        //! The string character type.
        typedef string_type::value_type string_char_type;


        // functions

        /*!
            \brief Checks whether one ascii encoding is equal to another.

            \param one     One ASCII encoding.
            \param another Another ASCII encoding.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const ascii& one, const ascii& another)
        {
            return true;
        }

        /*!
            \brief Translates a string from the pivot encoding.

            \param pivot A pivot string.

            \return A translated string.

            \throw std::invalid_argument When the string cannot be translated.
        */
        string_type from_pivot(const typename base_type::pivot_type& pivot)
        const
        {
            return
                string_type(
                    boost::make_transform_iterator(pivot.begin(), to_ascii),
                    boost::make_transform_iterator(pivot.end(), to_ascii)
                );
        }

        /*!
            \brief Translates a string to the pivot encoding.

            \param string A string.

            \return A translated pivot string.

            \throw std::invalid_argument When the string cannot be translated.
        */
        typename base_type::pivot_type to_pivot(const string_type& string)
        const
        {
            return
                typename base_type::pivot_type(
                    boost::make_transform_iterator(string.begin(), from_ascii),
                    boost::make_transform_iterator(string.end(), from_ascii)
                );
        }


    private:
        // static functions

        static string_char_type to_ascii(const typename base_type::pivot_char_type pivot_char)
        {
            static const string_char_type question = 0x3F;

            return 0 <= pivot_char && pivot_char <= 0x7F ? static_cast<string_char_type>(pivot_char) : question;
        }

        static typename base_type::pivot_char_type from_ascii(const string_char_type ascii_char)
        {
            if (ascii_char < 0 || 0x80 <= ascii_char)
                BOOST_THROW_EXCEPTION(std::invalid_argument("Not ASCII code."));

            return ascii_char;
        }


    };


}}}


#endif

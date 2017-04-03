/*! \file
    \brief The definition of tetengo2::text::encoding::ascii.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODING_ASCII_H)
#define TETENGO2_TEXT_ENCODING_ASCII_H

#include <stdexcept>
#include <string>

#include <boost/core/ignore_unused.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/operators.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/text/encoding/encoding.h>


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
        using base_type = encoding<EncodingDetails>;

        //! The string type.
        using string_type = std::string;


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
            boost::ignore_unused(one, another);

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
                {
                    boost::make_transform_iterator(pivot.begin(), to_ascii),
                    boost::make_transform_iterator(pivot.end(), to_ascii)
                };
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
                {
                    boost::make_transform_iterator(string.begin(), from_ascii),
                    boost::make_transform_iterator(string.end(), from_ascii)
                };
        }


    private:
        // types

        using pivot_char_type = typename base_type::pivot_type::value_type;

        using string_char_type = typename string_type::value_type;


        // static functions

        static string_char_type to_ascii(const pivot_char_type pivot_char)
        {
            return to_ascii_impl(pivot_char);
        }

        static string_char_type to_ascii_impl(const char pivot_char)
        {
            if (pivot_char >= 0)
                return pivot_char;
            else
                return 0x3F;
        }

        static string_char_type to_ascii_impl(const wchar_t pivot_char)
        {
            if (pivot_char <= 0x7F)
                return static_cast<string_char_type>(pivot_char);
            else
                return 0x3F;
        }

        static pivot_char_type from_ascii(const string_char_type ascii_char)
        {
            if (ascii_char < 0)
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Not ASCII code." }));

            return ascii_char;
        }


    };


}}}


#endif

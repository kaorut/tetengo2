/*! \file
    \brief The definition of tetengo2::text::encoding::cp932.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODING_CP932_H)
#define TETENGO2_TEXT_ENCODING_CP932_H

#include <stdexcept>
#include <string>

#include <boost/core/ignore_unused.hpp>
#include <boost/operators.hpp>

#include <tetengo2/text/encoding/encoding.h>


namespace tetengo2 { namespace text { namespace encoding
{
    /*!
        \brief The class template for a CP932 encoding.

        \tparam EncodingDetails A detail implementation type of an encoding.
    */
    template <typename EncodingDetails>
    class cp932 : public encoding<EncodingDetails>, private boost::equality_comparable<cp932<EncodingDetails>>
    {
    public:
        // types

        //! The base type.
        using base_type = encoding<EncodingDetails>;

        //! The string type.
        using string_type = std::string;

        //! The encoding details type.
        using encoding_details_type = EncodingDetails;


        // functions

        /*!
            \brief Checks whether one CP932 encoding is equal to another.

            \param one     One CP932 encoding.
            \param another Another CP932 encoding.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const cp932& one, const cp932& another)
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
            return encoding_details_type::pivot_to_cp932(pivot);
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
            return encoding_details_type::cp932_to_pivot(string);
        }


    };


}}}


#endif

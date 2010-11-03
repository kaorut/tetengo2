/*! \file
    \brief The definition of tetengo2::encoder.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODER_H)
#define TETENGO2_ENCODER_H

//#include <cstddef>
//#include <type_traits>
//#include <utility>

//#include <boost/operators.hpp>
//#include <boost/utility.hpp>

#include "tetengo2.encoding.locale.h"


namespace tetengo2
{
    /*!
        \brief The class template for an encoder.

        \tparam InternalEncoding An internal encoding type.
        \tparam ExternalEncoding An external encoding type.
    */
    template <typename InternalEncoding, typename ExternalEncoding>
    class encoder :
        public boost::equality_comparable<
            encoder<InternalEncoding, ExternalEncoding>
        >
    {
    public:
        // types

        //! The internal encoding type.
        typedef InternalEncoding internal_encoding_type;

        //! The internal string type.
        typedef
            typename internal_encoding_type::string_type internal_string_type;

        //! The external encoding type.
        typedef ExternalEncoding external_encoding_type;

        //! The external string type.
        typedef
            typename external_encoding_type::string_type external_string_type;


        // constructors and destructor

        /*!
            \brief Creates an encoder.
        */
        encoder()
        :
        m_internal_encoding(),
        m_external_encoding()
        {}

        /*!
            \brief Creates an encoder.

            \tparam IE An internal encoding type.
            \tparam EE An external encoding type.

            \param internal_encoding An internal encoding.
            \param external_encoding An external encoding.
        */
        template <typename IE, typename EE>
        explicit encoder(IE&& internal_encoding, EE&& external_encoding)
        :
        m_internal_encoding(std::forward<IE>(internal_encoding)),
        m_external_encoding(std::forward<EE>(external_encoding))
        {}


        // functions

        /*!
            \brief Checks whether one encoder is equal to another.

            \param one     One encoder.
            \param another Another encoder.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const encoder& one, const encoder& another)
        {
            return one.m_internal_encoding == another.m_internal_encoding &&
                one.m_external_encoding == another.m_external_encoding;
        }

        /*!
            \brief Returns the internal encoding.

            \return The internal encoding.
        */
        const internal_encoding_type& internal_encoding()
        const
        {
            return m_internal_encoding;
        }

        /*!
            \brief Returns the external encoding.

            \return The external encoding.
        */
        const external_encoding_type& external_encoding()
        const
        {
            return m_external_encoding;
        }

        /*!
            \brief Encodes a string.

            \tparam IS An internal string type.

            \param string A string

            \return An encoded string.
        */
        template <typename IS>
        external_string_type encode(IS&& string)
        const
        {
            return encode_impl(
                std::forward<IS>(string),
                m_internal_encoding,
                m_external_encoding
            );
        }

        /*!
            \brief Decodes a string.

            \tparam ES An external string type.

            \param string A string.

            \return A decoded string.
        */
        template <typename ES>
        internal_string_type decode(ES&& string)
        const
        {
            return decode_impl(
                std::forward<ES>(string),
                m_internal_encoding,
                m_external_encoding
            );
        }


    private:
        // types

        typedef
            typename std::is_same<
                internal_encoding_type, external_encoding_type
            >::type
            encodings_are_same_type;


        // static functions

        template <typename IS, typename InternEnc, typename ExternEnc>
        static external_string_type encode_impl(
            IS&&             string,
            const InternEnc& internal_encoding,
            const ExternEnc& external_encoding,
            const typename std::enable_if<
                std::is_same<InternEnc, ExternEnc>::value
            >::type* const = NULL
        )
        {
            return std::forward<IS>(string);
        }

        template <typename IS, typename InternEnc, typename ExternEnc>
        static external_string_type encode_impl(
            IS&&             string,
            const InternEnc& internal_encoding,
            const ExternEnc& external_encoding,
            const typename std::enable_if<
                !std::is_same<InternEnc, ExternEnc>::value
            >::type* const = NULL
        )
        {
            return external_encoding.from_pivot(
                internal_encoding.to_pivot(std::forward<IS>(string))
            );
        }

        template <typename IS, typename Str>
        static external_string_type encode_impl(
            IS&&                         string,
            const encoding::locale<Str>& internal_encoding,
            const encoding::locale<Str>& external_encoding
        )
        {
            if (
                internal_encoding.locale_based_on() ==
                external_encoding.locale_based_on()
            )
            {
                return std::forward<IS>(string);
            }
            else
            {
                return external_encoding.from_pivot(
                    internal_encoding.to_pivot(std::forward<IS>(string))
                );
            }
        }

        template <typename ES, typename InternEnc, typename ExternEnc>
        static internal_string_type decode_impl(
            ES&&             string,
            const InternEnc& internal_encoding,
            const ExternEnc& external_encoding,
            const typename std::enable_if<
                std::is_same<InternEnc, ExternEnc>::value
            >::type* const = NULL
        )
        {
            return std::forward<ES>(string);
        }

        template <typename ES, typename InternEnc, typename ExternEnc>
        static internal_string_type decode_impl(
            ES&&             string,
            const InternEnc& internal_encoding,
            const ExternEnc& external_encoding,
            const typename std::enable_if<
                !std::is_same<InternEnc, ExternEnc>::value
            >::type* const = NULL
        )
        {
            return internal_encoding.from_pivot(
                external_encoding.to_pivot(std::forward<ES>(string))
            );
        }

        template <typename ES, typename Str>
        static internal_string_type decode_impl(
            ES&&                         string,
            const encoding::locale<Str>& internal_encoding,
            const encoding::locale<Str>& external_encoding
        )
        {
            if (
                internal_encoding.locale_based_on() ==
                external_encoding.locale_based_on()
            )
            {
                return std::forward<ES>(string);
            }
            else
            {
                return internal_encoding.from_pivot(
                    external_encoding.to_pivot(std::forward<ES>(string))
                );
            }
        }


        // variables

        internal_encoding_type m_internal_encoding;

        external_encoding_type m_external_encoding;


    };


}

#endif

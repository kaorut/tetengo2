/*! \file
    \brief The definition of tetengo2::encoder.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODER_H)
#define TETENGO2_ENCODER_H

//#include <cstddef>

//#include <boost/concept_check.hpp>
//#include <boost/swap.hpp>
#include <boost/operators.hpp>
//#include <boost/type_traits.hpp>
//#include <boost/utility.hpp>

#include "concept_tetengo2.encoding.Encoding.h"
#include "tetengo2.assignable.h"
#include "tetengo2.swappable.h"
#include "tetengo2.encoding.locale.h"


namespace tetengo2
{
    /*!
        \brief The class template for an encoder.

        \tparam InternalEncoding An internal encoding type. It must conform to
                                 concept_tetengo2::Encoding<InternalEncoding>.
        \tparam ExternalEncoding An external encoding type. It must conform to
                                 concept_tetengo2::Encoding<ExternalEncoding>.
    */
    template <typename InternalEncoding, typename ExternalEncoding>
    class encoder :
        public assignable<encoder<InternalEncoding, ExternalEncoding> >,
        public swappable<encoder<InternalEncoding, ExternalEncoding> >,
        public boost::equality_comparable<
            encoder<InternalEncoding, ExternalEncoding>
        >
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::encoding::Encoding<InternalEncoding>
        ));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::encoding::Encoding<ExternalEncoding>
        ));


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

            \param internal_encoding An internal encoding.
            \param external_encoding An external encoding.
        */
        explicit encoder(
            const internal_encoding_type& internal_encoding =
                internal_encoding_type(),
            const external_encoding_type& external_encoding =
                external_encoding_type()
        )
        :
        m_internal_encoding(internal_encoding),
        m_external_encoding(external_encoding)
        {}

        /*!
            \brief Copies an encoder.

            \param another Another encoder;
        */
        encoder(const encoder& another)
        :
        m_internal_encoding(another.m_internal_encoding),
        m_external_encoding(another.m_external_encoding)
        {}
        
        /*!
            \brief Destroys the encoder.
        */
        ~encoder()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another encoder.

            \param another Another encoder.
        */
        void swap(encoder& another)
        throw ()
        {
            boost::swap(m_internal_encoding, another.m_internal_encoding);
            boost::swap(m_external_encoding, another.m_external_encoding);
        }

        /*!
            \brief Assigns another encoder.

            \param another Another encoder.

            \return this object.
        */
        encoder& operator=(const encoder& another)
        {
            return assign(another);
        }

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

            \param string A string

            \return An encoded string.
        */
        external_string_type encode(const internal_string_type& string)
        const
        {
            return encode_impl(
                string, m_internal_encoding, m_external_encoding
            );
        }

        /*!
            \brief Decodes a string.

            \param string A string.

            \return A decoded string.
        */
        internal_string_type decode(const external_string_type& string)
        const
        {
            return decode_impl(
                string, m_internal_encoding, m_external_encoding
            );
        }


    private:
        // types

        typedef
            typename boost::is_same<
                internal_encoding_type, external_encoding_type
            >::type
            encodings_are_same_type;


        // static functions

        template <typename InternEnc, typename ExternEnc>
        static external_string_type encode_impl(
            const internal_string_type& string,
            const InternEnc&            internal_encoding,
            const ExternEnc&            external_encoding,
            const typename boost::enable_if<
                boost::is_same<InternEnc, ExternEnc>
            >::type* const = NULL
        )
        {
            return string;
        }

        template <typename InternEnc, typename ExternEnc>
        static external_string_type encode_impl(
            const internal_string_type& string,
            const InternEnc&            internal_encoding,
            const ExternEnc&            external_encoding,
            const typename boost::disable_if<
                boost::is_same<InternEnc, ExternEnc>
            >::type* const = NULL
        )
        {
            return external_encoding.from_pivot(
                internal_encoding.to_pivot(string)
            );
        }

        template <typename Str>
        static external_string_type encode_impl(
            const internal_string_type&  string,
            const encoding::locale<Str>& internal_encoding,
            const encoding::locale<Str>& external_encoding
        )
        {
            if (
                internal_encoding.locale_based_on() ==
                external_encoding.locale_based_on()
            )
            {
                return string;
            }
            else
            {
                return external_encoding.from_pivot(
                    internal_encoding.to_pivot(string)
                );
            }
        }


        template <typename InternEnc, typename ExternEnc>
        static internal_string_type decode_impl(
            const external_string_type& string,
            const InternEnc&            internal_encoding,
            const ExternEnc&            external_encoding,
            const typename boost::enable_if<
                boost::is_same<InternEnc, ExternEnc>
            >::type* const = NULL
        )
        {
            return string;
        }

        template <typename InternEnc, typename ExternEnc>
        static internal_string_type decode_impl(
            const external_string_type& string,
            const InternEnc&            internal_encoding,
            const ExternEnc&            external_encoding,
            const typename boost::disable_if<
                boost::is_same<InternEnc, ExternEnc>
            >::type* const = NULL
        )
        {
            return internal_encoding.from_pivot(
                external_encoding.to_pivot(string)
            );
        }

        template <typename Str>
        static internal_string_type decode_impl(
            const external_string_type&  string,
            const encoding::locale<Str>& internal_encoding,
            const encoding::locale<Str>& external_encoding
        )
        {
            if (
                internal_encoding.locale_based_on() ==
                external_encoding.locale_based_on()
            )
            {
                return string;
            }
            else
            {
                return internal_encoding.from_pivot(
                    external_encoding.to_pivot(string)
                );
            }
        }


        // variables

        internal_encoding_type m_internal_encoding;

        external_encoding_type m_external_encoding;


    };


}

#endif

/*! \file
    \brief The definition of tetengo2::text::encoder.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODER_H)
#define TETENGO2_TEXT_ENCODER_H

#include <type_traits>
#include <utility>

#include <boost/core/ignore_unused.hpp>
#include <boost/operators.hpp>

#include <tetengo2/text/encoding/locale.h>


namespace tetengo2 { namespace text
{
    /*!
        \brief The class template for an encoder.

        \tparam InternalEncoding An internal encoding type.
        \tparam ExternalEncoding An external encoding type.
    */
    template <typename InternalEncoding, typename ExternalEncoding>
    class encoder : public boost::equality_comparable<encoder<InternalEncoding, ExternalEncoding>>
    {
    public:
        // types

        //! The internal encoding type.
        using internal_encoding_type = InternalEncoding;

        //! The internal string type.
        using internal_string_type = typename internal_encoding_type::string_type;

        //! The external encoding type.
        using external_encoding_type = ExternalEncoding;

        //! The external string type.
        using external_string_type = typename external_encoding_type::string_type;


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

            \param internal_encoding An internal encoding.
            \param external_encoding An external encoding.
        */
        explicit encoder(internal_encoding_type internal_encoding, external_encoding_type external_encoding)
        :
        m_internal_encoding(std::move(internal_encoding)),
        m_external_encoding(std::move(external_encoding))
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
            return
                one.m_internal_encoding == another.m_internal_encoding &&
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
        external_string_type encode(internal_string_type string)
        const
        {
            return encode_impl(std::move(string), m_internal_encoding, m_external_encoding);
        }

        /*!
            \brief Decodes a string.

            \param string A string.

            \return A decoded string.
        */
        internal_string_type decode(external_string_type string)
        const
        {
            return decode_impl(std::move(string), m_internal_encoding, m_external_encoding);
        }


    private:
        // static functions

        template <typename IE, typename EE>
        static external_string_type encode_impl(
            internal_string_type&& string,
            const IE&              internal_encoding,
            const EE&              external_encoding,
            const typename std::enable_if<std::is_same<IE, EE>::value>::type* const = nullptr
        )
        {
            boost::ignore_unused(internal_encoding, external_encoding);

            return std::move(string);
        }

        template <typename IE, typename EE>
        static external_string_type encode_impl(
            internal_string_type&& string,
            const IE&              internal_encoding,
            const EE&              external_encoding,
            const typename std::enable_if<!std::is_same<IE, EE>::value>::type* const = nullptr
        )
        {
            return external_encoding.from_pivot(internal_encoding.to_pivot(std::move(string)));
        }

        template <typename S, typename D>
        static external_string_type encode_impl(
            internal_string_type&&        string,
            const encoding::locale<S, D>& internal_encoding,
            const encoding::locale<S, D>& external_encoding
        )
        {
            if (internal_encoding.locale_based_on() == external_encoding.locale_based_on())
                return std::move(string);
            else
                return external_encoding.from_pivot(internal_encoding.to_pivot(std::move(string)));
        }

        template <typename IE, typename EE>
        static internal_string_type decode_impl(
            external_string_type&& string,
            const IE&              internal_encoding,
            const EE&              external_encoding,
            const typename std::enable_if<std::is_same<IE, EE>::value>::type* const = nullptr
        )
        {
            boost::ignore_unused(internal_encoding, external_encoding);

            return std::move(string);
        }

        template <typename IE, typename EE>
        static internal_string_type decode_impl(
            external_string_type&& string,
            const IE&              internal_encoding,
            const EE&              external_encoding,
            const typename std::enable_if<!std::is_same<IE, EE>::value>::type* const = nullptr
        )
        {
            return internal_encoding.from_pivot(external_encoding.to_pivot(std::move(string)));
        }

        template <typename S, typename D>
        static internal_string_type decode_impl(
            external_string_type&&        string,
            const encoding::locale<S, D>& internal_encoding,
            const encoding::locale<S, D>& external_encoding
        )
        {
            if (internal_encoding.locale_based_on() == external_encoding.locale_based_on())
                return std::move(string);
            else
                return internal_encoding.from_pivot(external_encoding.to_pivot(std::move(string)));
        }


        // variables

        internal_encoding_type m_internal_encoding;

        external_encoding_type m_external_encoding;


    };


}}


#endif

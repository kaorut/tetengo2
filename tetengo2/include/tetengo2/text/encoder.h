/*! \file
    \brief The definition of tetengo2::text::encoder.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODER_H)
#define TETENGO2_TEXT_ENCODER_H

#include <type_traits>
#include <utility>


namespace tetengo2 { namespace text
{
    /*!
        \brief The class template for an encoder.

        \tparam InternalEncoding An internal encoding type.
        \tparam ExternalEncoding An external encoding type.
    */
    template <typename InternalEncoding, typename ExternalEncoding>
    class encoder
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
            return encode_impl<external_string_type>(std::move(string));
        }

        /*!
            \brief Decodes a string.

            \param string A string.

            \return A decoded string.
        */
        internal_string_type decode(external_string_type string)
        const
        {
            return m_internal_encoding.from_pivot(m_external_encoding.to_pivot(std::move(string)));
        }


    private:
        // variables

        internal_encoding_type m_internal_encoding;

        external_encoding_type m_external_encoding;


        // functions

        template <typename ES, typename IS>
        ES encode_impl(IS string, typename std::enable_if<std::is_convertible<IS, ES>::value>::type* = nullptr)
        const
        {
            if (m_internal_encoding == m_external_encoding)
                return std::move(string);
            else
                return m_external_encoding.from_pivot(m_internal_encoding.to_pivot(std::move(string)));
        }

        template <typename ES, typename IS>
        ES encode_impl(IS string, typename std::enable_if<!std::is_convertible<IS, ES>::value>::type* = nullptr)
        const
        {
            return m_external_encoding.from_pivot(m_internal_encoding.to_pivot(std::move(string)));
        }

        template <typename IS, typename ES>
        IS decode(ES string, typename std::enable_if<std::is_convertible<ES, IS>::value>::type* = nullptr)
        const
        {
            if (m_internal_encoding == m_external_encoding)
                return std::move(string);
            else
                return m_internal_encoding.from_pivot(m_external_encoding.to_pivot(std::move(string)));
        }

        template <typename IS, typename ES>
        IS decode(ES string, typename std::enable_if<!std::is_convertible<ES, IS>::value>::type* = nullptr)
        const
        {
            return m_internal_encoding.from_pivot(m_external_encoding.to_pivot(std::move(string)));
        }


    };


}}


#endif

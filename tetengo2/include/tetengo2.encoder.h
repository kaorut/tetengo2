/*! \file
    \brief The definition of tetengo2::encoder.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODER_H)
#define TETENGO2_ENCODER_H

#include "tetengo2.assignable.h"


namespace tetengo2
{
    /*!
        \brief The class template for an encoder.

        \tparam InternalEncoding An internal encoding type.
        \tparam ExternalEncoding An external encoding type.
    */
    template <typename InternalEncoding, typename ExternalEncoding>
    class encoder :
        public assignable<encoder<InternalEncoding, ExternalEncoding> >
    {
    private:
        // concept checks


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
            m_internal_encoding.swap(another.m_internal_encoding);
            m_external_encoding.swap(another.m_external_encoding);
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
            \brief Encodes a string.

            \param string A string

            \return An encoded string.
        */
        external_string_type encode(const internal_string_type& string)
        const
        {
            return m_external_encoding.from_pivot(
                m_internal_encoding.to_pivot(string)
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
            return m_internal_encoding.from_pivot(
                m_external_encoding.to_pivot(string)
            );
        }


    private:
        // variables

        internal_encoding_type m_internal_encoding;

        external_encoding_type m_external_encoding;


    };


}

#endif

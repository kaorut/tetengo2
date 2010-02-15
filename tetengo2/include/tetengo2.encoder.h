/*! \file
    \brief The definition of tetengo2::encoder.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODER_H)
#define TETENGO2_ENCODER_H


namespace tetengo2
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
        {}

        /*!
            \brief Destroys the encoder.
        */
        ~encoder()
        throw ()
        {}


        // functions

        /*!
            \brief Encodes a string.

            \param string A string

            \return An encoded string.
        */
        external_string_type encode(const internal_string_type& string)
        const
        {
            
        }

        /*!
            \brief Decodes a string.

            \param string A string.

            \return A decoded string.
        */
        internal_string_type decode(const external_string_type& string)
        const
        {

        }


    private:
        // variables


    };


}

#endif

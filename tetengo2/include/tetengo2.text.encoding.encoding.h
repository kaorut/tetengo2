/*! \file
    \brief The definition of tetengo2::text::encoding::encoding.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODING_ENCODING_H)
#define TETENGO2_TEXT_ENCODING_ENCODING_H


namespace tetengo2 { namespace text { namespace encoding
{
    /*!
        \brief The class template for a encoding.

        \tparam EncodingDetails A detail implementation type of an encoding.
    */
    template <typename EncodingDetails>
    class encoding
    {
    public:
        // types

        //! The detail implementation type of an encoding.
        typedef EncodingDetails encoding_details_type;

        //! The pivot type.
        typedef typename encoding_details_type::pivot_type pivot_type;

        //! The pivot character type.
        typedef typename pivot_type::value_type pivot_char_type;


    protected:
        // constructors and destructor

        /*!
            \brief Creates an encoding.
        */
        encoding()
        {}


    };


}}}


#endif

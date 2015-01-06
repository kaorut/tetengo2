/*! \file
    \brief The definition of tetengo2::text::encoding::encoding.

    Copyright (C) 2007-2015 kaoru

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

        //! The encoding details type.
        using encoding_details_type = EncodingDetails;

        //! The pivot type.
        using pivot_type = typename encoding_details_type::pivot_type;


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

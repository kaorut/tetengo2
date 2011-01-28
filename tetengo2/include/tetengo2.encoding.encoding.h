/*! \file
    \brief The definition of tetengo2::encoding::encoding.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODING_ENCODING_H)
#define TETENGO2_ENCODING_ENCODING_H

#include <string>


namespace tetengo2 { namespace encoding
{
    /*!
        \brief The class template for a encoding.

        \tparam DetailEncoding A detail implementation type of an encoding.
    */
    template <typename DetailEncoding>
    class encoding
    {
    public:
        // types

        //! The detail implementation type of an encoding.
        typedef DetailEncoding detail_encoding_type;

        //! The pivot type.
        typedef typename detail_encoding_type::pivot_type pivot_type;

        //! The pivot character type.
        typedef typename pivot_type::value_type pivot_char_type;


    protected:
        // constructors

        /*!
            \brief Creates an encoding.
        */
        encoding()
        {}


    };


}}


#endif

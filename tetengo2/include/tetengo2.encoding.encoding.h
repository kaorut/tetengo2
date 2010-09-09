/*! \file
    \brief The definition of tetengo2::encoding::encoding.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODING_ENCODING_H)
#define TETENGO2_ENCODING_ENCODING_H

#include <string>

#include "tetengo2.cpp0x_keyword.h"


namespace tetengo2 { namespace encoding
{
    /*!
        \brief The class for a encoding.
    */
    class encoding
    {
    public:
        // types

        //! \return The pivot type.
        typedef std::wstring pivot_type;

        //! \return The pivot character type.
        typedef pivot_type::value_type pivot_char_type;


        // constructors and destructor

        /*!
            \brief Destroys the encoding based on a encoding.
        */
        ~encoding()
        TETENGO2_NOEXCEPT
        {}


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

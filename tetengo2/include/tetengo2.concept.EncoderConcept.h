/*! \file
    \brief The definition of tetengo2::concept::EncoderConcept.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCEPT_ENCODERCONCEPT_H)
#define TETENGO2_CONCEPT_ENCODERCONCEPT_H

#include <boost/concept_check.hpp>


namespace tetengo2 { namespace concept
{
    /*!
        \brief The concept class template for an encoder.
        
        \param Encoder An encoder type.
    */
    template <typename Encoder>
    class EncoderConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints.
        */
        void constraints()
        {
            const_constraints(m_encoder);
        }

        /*!
            \brief Checks the const constraints.
        */
        void const_constraints(const Encoder& encoder)
        {
            encoder.encode<int>(0);
        }

    private:
        // variables

        Encoder m_encoder;


    };
}}

#endif

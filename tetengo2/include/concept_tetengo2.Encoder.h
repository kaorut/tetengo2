/*! \file
    \brief The definition of concept_tetengo2::Encoder.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_ENCODER_H)
#define CONCEPTTETENGO2_ENCODER_H

#include <boost/concept_check.hpp>


namespace concept_tetengo2
{
    /*!
        \brief The concept check class template for an encoder.

        \tparam Type A type.
    */
    template <typename Type>
    class Encoder
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::internal_encoding_type internal_encoding_type;

        typedef typename Type::internal_string_type internal_string_type;

        typedef typename Type::external_encoding_type external_encoding_type;

        typedef typename Type::external_string_type external_string_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Encoder)
        {
            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const external_string_type external_string =
                object.encode(internal_string_type());
            const internal_string_type internal_string =
                object.decode(external_string_type());
        }


    private:
        // variables

        Type m_object;


#endif
    };


}

#endif

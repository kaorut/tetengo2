/*! \file
    \brief The definition of stub_tetengo2::encode.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_ENCODE_H)
#define STUBTETENGO2_ENCODE_H

#include <functional>

#include <boost/concept_check.hpp>

#include "tetengo2.StringConcept.h"


namespace stub_tetengo2
{
    template <typename Target, typename Source>
    class encode :
        public std::unary_function<Source, Target>
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((tetengo2::StringConcept<Target>));
        BOOST_CONCEPT_ASSERT((tetengo2::StringConcept<Source>));


    public:
        // types

        typedef result_type target_type;

        typedef argument_type source_type;


        // functions

        const target_type operator()(const source_type& string)
        {
            return target_type();
        }


    };


}


#endif

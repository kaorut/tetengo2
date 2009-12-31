/*! \file
    \brief The definition of stub_tetengo2::encode.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_ENCODE_H)
#define STUBTETENGO2_ENCODE_H

#include <functional>

#include <boost/concept_check.hpp>

#include "concept_tetengo2.String.h"


namespace stub_tetengo2
{
    template <typename Target, typename Source>
    class encode :
        public std::unary_function<Source, Target>
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<Target>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<Source>));


    public:
        // types

        typedef Target target_type;

        typedef Source source_type;


        // functions

        const target_type operator()(const source_type& string)
        {
            return target_type();
        }


    };


}


#endif

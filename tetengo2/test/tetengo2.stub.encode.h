/*! \file
    \brief The definition of tetengo2::stub::encode.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_STUB_ENCODE_H)
#define TETENGO2_STUB_ENCODE_H

#include <functional>

#include <boost/concept_check.hpp>

#include "tetengo2.StringConcept.h"


namespace tetengo2 { namespace stub
{
    /*!
        \brief The unary functor class template for an encode for testing.

        \param Target A string type of the target. It must conform to
                      tetengo2::StringConcept<Target>.
        \param Source A string type of the source. It must conform to
                      tetengo2::StringConcept<Source>.
    */
    template <typename Target, typename Source>
    class encode :
        public std::unary_function<Source, Target>
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(Target, tetengo2, StringConcept);
        BOOST_CLASS_REQUIRE(Source, tetengo2, StringConcept);


    public:
        // types

        //! The string type of the target.
        typedef result_type target_type;

        //! The string type of the source.
        typedef argument_type source_type;


        // functions

        /*!
            \brief Encodes a source string to a target string.

            \param string A string.

            \return The encoded string. Always empty.
        */
        const target_type operator()(const source_type& string)
        {
            return target_type();
        }


    };


}}


#endif

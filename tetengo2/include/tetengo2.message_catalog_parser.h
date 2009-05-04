/*! \file
    \brief The definition of tetengo2::message_catalog_parser.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGECATALOGPARSER_H)
#define TETENGO2_MESSAGECATALOGPARSER_H

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#include "concept_tetengo2.String.h"


namespace tetengo2
{
    /*!
        \brief The class template for message_catalog_parser.

        It is a customized locale facet for message_catalog_parser.

        \tparam String A string type. It must conform to
                       concept_tetengo2::String<String>.
        \tparam Encode An encoding unary functor type. The types
                       Encode<String, std::string> must conform to
                       boost::UnaryFunction<Encode, String, std::string>.
    */
    template <
        typename String,
        template <typename Target, typename Source> class Encode
    >
    class message_catalog_parser : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        struct concept_check_Encode
        {
            typedef Encode<String, std::string> encode_from_stdstring_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_from_stdstring_type, String, std::string
                >
            ));
        };


    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The unary functor type for encoding from the std::string.
        typedef Encode<string_type, std::string> encode_from_stdstring_type;


        // constructors and destructor

        /*!
            \brief Creates a message catalog parser.
7        */
        message_catalog_parser()
        {}

        /*!
            \brief Destroys a message catalog parser.
        */
        virtual ~message_catalog_parser()
        throw ()
        {}


        // functions


    };


}

#endif

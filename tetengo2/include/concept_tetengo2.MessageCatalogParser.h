/*! \file
    \brief The definition of concept_tetengo2::MessageCatalogParser.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_MESSAGECATALOGPARSER_H)
#define CONCEPTTETENGO2_MESSAGECATALOGPARSER_H

#include <boost/concept_check.hpp>


namespace concept_tetengo2
{
    /*!
        \brief The concept check class template for a message catalog parser.

        \tparam Type A type.
    */
    template <typename Type>
    class MessageCatalogParser
    {
#if !defined(DOCUMENTATION)
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(MessageCatalogParser)
        {

        }

       
    private:
        // variables

        Type m_object;


#endif
    };


}

#endif

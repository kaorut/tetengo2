/*! \file
    \brief The definition of concept_tetengo2::MessageCatalogParser.

    Copyright (C) 2007-2010 kaoru

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
        // typedef checks

        typedef typename Type::input_stream_type input_stream_type;

        typedef typename Type::input_string_type input_string_type;

        typedef typename Type::string_type string_type;

        typedef typename Type::encoder_type encoder_type;

        typedef typename Type::entry_type entry_type;


        // usage checks

        BOOST_CONCEPT_USAGE(MessageCatalogParser)
        {
            const entry_type entry = m_object.next();
            boost::ignore_unused_variable_warning(entry);

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const bool has_next_entry = object.has_next();
            boost::ignore_unused_variable_warning(has_next_entry);
        }


    private:
        // variables

        Type m_object;


#endif
    };


}

#endif

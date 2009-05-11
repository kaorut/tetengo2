/*! \file
    \brief The definition of concept_tetengo2::MessageCatalog.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_MESSAGECATALOG_H)
#define CONCEPTTETENGO2_MESSAGECATALOG_H

#include <boost/concept_check.hpp>


namespace concept_tetengo2
{
    /*!
        \brief The concept check class template for a message catalog parser.

        \tparam Type A type.
    */
    template <typename Type>
    class MessageCatalog
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::messages_type messages_type;

        typedef typename Type::string_type string_type;


        // usage checks

        BOOST_CONCEPT_USAGE(MessageCatalog)
        {
            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const string_type text = object.get(string_type());
            boost::ignore_unused_variable_warning(text);
        }


    private:
        // variables

        Type m_object;


#endif
    };


}

#endif

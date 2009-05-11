/*! \file
    \brief The definition of concept_tetengo2::Messages.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_MESSAGES_H)
#define CONCEPTTETENGO2_MESSAGES_H

#include <locale>
#include <string>

#include <boost/concept_check.hpp>


namespace concept_tetengo2
{
    /*!
        \brief The concept check class template for a messages facet.

        \tparam Type A type.
    */
    template <typename Type>
    class Messages
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::catalog catalog;

        typedef typename Type::char_type char_type;

        typedef typename Type::string_type string_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Messages)
        {
            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const catalog catalog_value =
                object.open(std::string(), std::locale());
            boost::ignore_unused_variable_warning(catalog_value);

            const string_type text =
                object.get(catalog(), 0, 0, string_type());
            boost::ignore_unused_variable_warning(text);

            object.close(catalog());
        }


    private:
        // variables

        Type m_object;


#endif
    };


}

#endif

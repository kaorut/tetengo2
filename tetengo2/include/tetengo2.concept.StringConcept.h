/*! \file
    \brief The definition of tetengo2::concept::StringConcept.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCEPT_STRINGCONCEPT_H)
#define TETENGO2_CONCEPT_STRINGCONCEPT_H

#include <boost/concept_check.hpp>


namespace tetengo2 { namespace concept
{
    /*!
        \brief The concept class template for a string.

        This is a subconcept of boost::Mutable_RandomAccessContainerConcept.
        
        \param String A string type.
    */
    template <typename String>
    class StringConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints.
        */
        void constraints()
        {
            boost::function_requires<
                boost::Mutable_RandomAccessContainerConcept<String>
            >();

            String s1;
            String s2(m_string);
            String s3(m_iterator, m_iterator);
            boost::ignore_unused_variable_warning(s1);
            boost::ignore_unused_variable_warning(s2);
            boost::ignore_unused_variable_warning(s3);

            const_constraints(m_string);
        }

        /*!
            \brief Checks the const constraints.
        */
        void const_constraints(const String& string)
        {
            string.c_str();
            string.length();
        }

    private:
        // variables

        String m_string;

        typename String::iterator m_iterator;


    };
}}

#endif

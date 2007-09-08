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

        This is a refinement of boost::DefaultConstructibleConcept,
        boost::CopyConstructibleConcept and
        boost::Mutable_RandomAccessContainerConcept.
        
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
                boost::DefaultConstructibleConcept<String>
            >();
            boost::function_requires<
                boost::CopyConstructibleConcept<String>
            >();
            boost::function_requires<
                boost::Mutable_RandomAccessContainerConcept<String>
            >();

            String s(m_iterator, m_iterator);
            boost::ignore_unused_variable_warning(s);

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

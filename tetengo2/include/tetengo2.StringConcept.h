/*! \file
    \brief The definition of tetengo2::StringConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_STRINGCONCEPT_H)
#define TETENGO2_STRINGCONCEPT_H

#include <string>

#include <boost/concept_check.hpp>


namespace tetengo2
{
    /*!
        \brief The concept check class template for strings.

        \tparam String A string type.
    */
    template <typename String>
    class StringConcept
    {
#if !defined(DOCUMENTATION)
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(StringConcept)
        {
            m_string.error_type_must_be_a_string_type();
        }

       
    private:
        // variables

        String m_string;


#endif
    };

#if !defined(DOCUMENTATION)
    // A specialized template.
    template <typename Char, typename CharTraits, typename Allocator>
    class StringConcept<std::basic_string<Char, CharTraits, Allocator> >
    {
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(StringConcept)
        {}


    };
#endif


}

#endif

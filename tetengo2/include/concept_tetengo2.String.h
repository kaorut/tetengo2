/*! \file
    \brief The definition of concept_tetengo2::String.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_STRING_H)
#define CONCEPTTETENGO2_STRING_H

#include <string>

#include <boost/concept_check.hpp>


namespace concept_tetengo2
{
    /*!
        \brief The concept check class template for a string.

        \tparam Type A type.
    */
    template <typename Type>
    class String
    {
#if !defined(DOCUMENTATION)
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(String)
        {
            m_object.error_type_must_be_a_string_type();
        }

       
    private:
        // variables

        Type m_object;


#endif
    };

#if !defined(DOCUMENTATION)
    // A specialized template.
    template <typename Char, typename CharTraits, typename Allocator>
    class String<std::basic_string<Char, CharTraits, Allocator> >
    {
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(String)
        {}


    };
#endif


}

#endif

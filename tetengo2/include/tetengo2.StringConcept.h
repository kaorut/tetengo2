/*! \file
    \brief The definition of tetengo2::StringConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_STRINGCONCEPT_H)
#define TETENGO2_STRINGCONCEPT_H

#include <string>


namespace tetengo2
{
    /*!
        \brief The concept check class template for strings.

        \param String A string type.
    */
    template <typename String>
    class StringConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints on a string.
        */
        void constraints()
        {
            m_string.error_type_must_be_a_string_type();
        }


    private:
        // variables

        String m_string;


    };

#if !defined(DOCUMENTATION)
    // A specialized template.
    template <>
    class StringConcept<std::string>
    {
    public:
        // functions

        void constraints()
        {}


    };

    // A specialized template.
    template <>
    class StringConcept<std::wstring>
    {
    public:
        // functions

        void constraints()
        {}


    };
#endif


}

#endif

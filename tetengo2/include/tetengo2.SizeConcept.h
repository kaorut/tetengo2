/*! \file
    \brief The definition of tetengo2::SizeConcept.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_SIZECONCEPT_H)
#define TETENGO2_SIZECONCEPT_H

#include <cstddef>


namespace tetengo2
{
    /*!
        \brief The concept check class template for size types.

        \param Size A size type.
    */
    template <typename Size>
    class SizeConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints on a size.
        */
        void constraints()
        {
            m_size.error_type_must_be_a_size_type();
        }


    private:
        // variables

        Size m_size;


    };

#if !defined(DOCUMENTATION)
    // A specialized template.
    template <>
    class SizeConcept<std::size_t>
    {
    public:
        // functions

        void constraints()
        {}


    };
#endif


}

#endif

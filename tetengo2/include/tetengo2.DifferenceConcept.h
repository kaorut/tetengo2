/*! \file
    \brief The definition of tetengo2::DifferenceConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_DIFFERENCECONCEPT_H)
#define TETENGO2_DIFFERENCECONCEPT_H

#include <cstddef>


namespace tetengo2
{
    /*!
        \brief The concept check class template for difference types.

        \tparam Difference A difference type.
    */
    template <typename Difference>
    class DifferenceConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints on a difference.
        */
        void constraints()
        {
            m_size.error_type_must_be_a_difference_type();
        }


    private:
        // variables

        Difference m_difference;


    };

#if !defined(DOCUMENTATION)
    // A specialized template.
    template <>
    class DifferenceConcept<std::ptrdiff_t>
    {
    public:
        // functions

        void constraints()
        {}


    };
#endif


}

#endif

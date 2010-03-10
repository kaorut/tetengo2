/*! \file
    \brief The definition of concept_tetengo2::Assignable.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_ASSIGNABLE_H)
#define CONCEPTTETENGO2_ASSIGNABLE_H

#include <boost/concept_check.hpp>


namespace concept_tetengo2
{
    /*!
        \brief The concept check class template for an assignable object.

        \tparam Type A type.
    */
    template <typename Type>
    class Assignable :
        private boost::Assignable<Type>,
        private boost::CopyConstructible<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // types

        struct derived_type : private Type
        {
            void constraints()
            {
                Type& assigned = this->assign(*this);
                boost::ignore_unused_variable_warning(assigned);
            }
        };


        // usage checks

        BOOST_CONCEPT_USAGE(Assignable)
        {
            m_object.constraints();
        }


    private:
        // variables

        derived_type m_object;


#endif
    };


}

#endif

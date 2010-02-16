/*! \file
    \brief The definition of concept_tetengo2::Encoding.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_ENCODING_H)
#define CONCEPTTETENGO2_ENCODING_H

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace encoding
{
    /*!
        \brief The concept check class template for an encoding.

        \tparam Type A type.
    */
    template <typename Type>
    class Encoding :
        private boost::Assignable<Type>,
        private boost::CopyConstructible<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::string_type string_type;

        typedef typename Type::pivot_type pivot_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Encoding)
        {
            m_object.swap(m_object);

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const string_type string = object.from_pivot(pivot_type());
            const pivot_type pivot = object.to_pivot(string_type());
        }


    private:
        // variables

        Type m_object;


#endif
    };


}}


#endif

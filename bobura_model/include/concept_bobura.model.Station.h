/*! \file
    \brief The definition of concept_bobura::model::Station.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(CONCEPTBOBURA_MODEL_STATION_H)
#define CONCEPTBOBURA_MODEL_STATION_H

#include <boost/concept_check.hpp>


namespace concept_bobura { namespace model
{
    /*!
        \brief The concept check class template for a station.

        \tparam Type A type.
    */
    template <typename Type>
    class Station :
        private boost::CopyConstructible<Type>,
        private boost::Assignable<Type>,
        private boost::EqualityComparable<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::name_type name_type;

        typedef typename Type::grade_type grade_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Station)
        {
            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const name_type name = object.name();
            boost::ignore_unused_variable_warning(name);

            const grade_type& grade = object.grade();
            boost::ignore_unused_variable_warning(grade);
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif

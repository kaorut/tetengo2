/*! \file
    \brief The definition of concept_bobura::model::station_info::Grade.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTBOBURA_MODEL_STATIONINFO_GRADE_H)
#define CONCEPTBOBURA_MODEL_STATIONINFO_GRADE_H

#include <boost/concept_check.hpp>


namespace concept_bobura { namespace model { namespace station_info
{
    /*!
        \brief The concept check class template for a grade.

        \tparam Type A type.
    */
    template <typename Type>
    class Grade
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::name_type name_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Grade)
        {
            const Type& object = Type::instance();

            const_constraints(object);
        }

        void const_constraints(const Type& object)
        {
            const name_type name = object.name();
            boost::ignore_unused_variable_warning(name);
        }

        
#endif
    };


}}}

#endif

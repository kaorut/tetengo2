/*! \file
    \brief The definition of bobura::model::station_info::GradeConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATIONINFO_GRADECONCEPT_H)
#define BOBURA_MODEL_STATIONINFO_GRADECONCEPT_H

#include <boost/concept_check.hpp>


namespace bobura { namespace model { namespace station_info
{
    /*!
        \brief The concept check class template for a grade.

        \tparam Grade A grade type.
    */
    template <typename Grade>
    class GradeConcept
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Grade::name_type name_type;


        // usage checks

        BOOST_CONCEPT_USAGE(GradeConcept)
        {
            const Grade& grade = Grade::instance();

            const_constraints(grade);
        }

        void const_constraints(const Grade& grade)
        {
            const name_type name = grade.name();
            boost::ignore_unused_variable_warning(name);
        }

        
#endif
    };


}}}

#endif

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
    public:
        // functions

        /*!
            \brief Checks the constraints on a grade.
        */
        void constraints()
        {
            typedef typename Grade::string_type string_type;

            const Grade& grade = Grade::instance();

            const_constraints(grade);
        }

        /*!
            \brief Checks the const constraints on a grade.

            \param grade A constant object.
        */
        void const_constraints(const Grade& grade)
        {
            const typename Grade::string_type name = grade.name();
            boost::ignore_unused_variable_warning(name);
        }


    };


}}}

#endif

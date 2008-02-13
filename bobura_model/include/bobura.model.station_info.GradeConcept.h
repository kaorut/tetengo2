/*! \file
    \brief The definition of bobura::model::station_info::GradeConcept.

    Copyright (C) 2007-2008 kaoru

    $Id: bobura.model.StationConcept.h 155 2008-02-01 14:07:53Z kaoru $
*/

#if !defined(BOBURA_MODEL_STATIONINFO_GRADECONCEPT_H)
#define BOBURA_MODEL_STATIONINFO_GRADECONCEPT_H

#include <boost/concept_check.hpp>


namespace bobura { namespace model { namespace station_info
{
    /*!
        \brief The concept check class template for a grade.

        \param Grade A grade type.
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
            const Grade& grade = Grade::instance();

            const_constraints(grade);
        }

        /*!
            \brief Checks the const constraints on a station.
        */
        void const_constraints(const Grade& grade)
        {
            
        }


    };


}}}

#endif

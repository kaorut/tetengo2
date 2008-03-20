/*! \file
    \brief The definition of bobura::model::station_info::GradeNameConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATIONINFO_GRADENAMECONCEPT_H)
#define BOBURA_MODEL_STATIONINFO_GRADENAMECONCEPT_H

#include <tetengo2.StringConcept.h>


namespace bobura { namespace model { namespace station_info
{
    /*!
        \brief The concept check class template for a station grade name.

        This class template is an alias of tetengo2::StringConcept.

        \tparam GradeName A grade name type.
    */
    template <typename GradeName>
    class GradeNameConcept : public tetengo2::StringConcept<GradeName>
    {};


}}}

#endif

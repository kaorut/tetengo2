/*! \file
    \brief The definition of bobura::model::timetable_info::MeterageConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_METERAGECONCEPT_H)
#define BOBURA_MODEL_TIMETABLEINFO_METERAGECONCEPT_H

#include <tetengo2.SizeConcept.h>


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The concept check class template for a meterage.

        This class template is an alias of tetengo2::SizeConcept.

        \tparam Meterage A meterage type.
    */
    template <typename Meterage>
    class MeterageConcept : public tetengo2::SizeConcept<Meterage>
    {};


}}}

#endif

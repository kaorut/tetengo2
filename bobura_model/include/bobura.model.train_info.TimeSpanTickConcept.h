/*! \file
    \brief The definition of bobura::model::train_info::TimeSpanTickConcept.

    Copyright (C) 2007-2008 kaoru

    $Id: bobura.model.train_info.TimeSpanTickConcept.h 256 2008-03-20 23:49:11Z kaoru $
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIMESPANTICKCONCEPT_H)
#define BOBURA_MODEL_TRAININFO_TIMESPANTICKCONCEPT_H

#include <tetengo2.DifferenceConcept.h>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The concept check class template for a time span tick.

        This class template is an alias of tetengo2::DifferenceConcept.

        \tparam TimeSpanTick A time span tick type.
    */
    template <typename TimeSpanTick>
    class TimeSpanTickConcept :
        public tetengo2::DifferenceConcept<TimeSpanTick>
    {};


}}}

#endif

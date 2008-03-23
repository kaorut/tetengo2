/*! \file
    \brief The definition of bobura::model::train_info::TimeTickConcept.

    Copyright (C) 2007-2008 kaoru

    $Id: bobura.model.train_info.TimeTickConcept.h 256 2008-03-20 23:49:11Z kaoru $
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIMETICKCONCEPT_H)
#define BOBURA_MODEL_TRAININFO_TIMETICKCONCEPT_H

#include <tetengo2.SizeConcept.h>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The concept check class template for a time tick.

        This class template is an alias of tetengo2::SizeConcept.

        \tparam TimeTick A time tick type.
    */
    template <typename TimeTick>
    class TimeTickConcept : public tetengo2::SizeConcept<TimeTick>
    {};


}}}

#endif

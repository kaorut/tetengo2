/*! \file
    \brief The definition of bobura::model::station_info::NameConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATIONINFO_NAMECONCEPT_H)
#define BOBURA_MODEL_STATIONINFO_NAMECONCEPT_H

#include <tetengo2.StringConcept.h>


namespace bobura { namespace model { namespace station_info
{
    /*!
        \brief The concept check class template for a station name.

        This class template is an alias of tetengo2::StringConcept.

        \tparam Name A name type.
    */
    template <typename Name>
    class NameConcept : public tetengo2::StringConcept<Name>
    {};


}}}

#endif

/*! \file
    \brief The definition of bobura::model::train_info::PlatformConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_PLATFORMCONCEPT_H)
#define BOBURA_MODEL_TRAININFO_PLATFORMCONCEPT_H

#include <tetengo2.StringConcept.h>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The concept check class template for a platform.

        This class template is an alias of tetengo2::StringConcept.

        \tparam Platform A platform type.
    */
    template <typename Platform>
    class PlatformConcept : public tetengo2::StringConcept<Platform>
    {};


}}}

#endif

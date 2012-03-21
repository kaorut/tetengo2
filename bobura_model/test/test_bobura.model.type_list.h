/*! \file
    \brief The definition of test_bobura::model::type_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TYPELIST_H)
#define TESTBOBURA_MODEL_TYPELIST_H

#include <string>

#include <boost/mpl/pair.hpp>

#include <tetengo2.meta.assoc_list.h>

#include "bobura.model.station_info.grade.h"
#include "bobura.model.station.h"


namespace test_bobura { namespace model
{
    namespace type
    {
        struct string;         //!< The string type.
        struct station;        //!< The station type.
        struct grade_type_set; //!< The station grade type set type.
    }

#if !defined(DOCUMENTATION)
    namespace detail
    {
        typedef std::string string_type;
        typedef
            bobura::model::station_info::grade_type_set<string_type>
            grade_type_set_type;
        typedef grade_type_set_type::grade_type grade_type;
    }
#endif

    //! The type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::string, detail::string_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::station,
                bobura::model::station<
                    detail::string_type, detail::grade_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::grade_type_set, detail::grade_type_set_type
            >,
        tetengo2::meta::assoc_list_end
        >>>
        type_list;


}}


#endif

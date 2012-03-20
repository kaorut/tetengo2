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


namespace test_bobura { namespace model
{
    namespace type
    {
        struct grade;          //!< The grade type.
        struct local;          //!< The local grade type.
        struct principal;      //!< The principal grade type.
        struct local_terminal; //!< The local terminal grade type.
        struct principal_terminal; //!< The principal terminal grade type.
    }

#if !defined(DOCUMENTATION)
    namespace detail
    {
        typedef std::string string_type;
    }
#endif

    //! The type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::grade,
                bobura::model::station_info::grade<detail::string_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::local,
                bobura::model::station_info::local<detail::string_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::principal,
                bobura::model::station_info::principal<detail::string_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::local_terminal,
                bobura::model::station_info::local_terminal<
                    detail::string_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::principal_terminal,
                bobura::model::station_info::principal_terminal<
                    detail::string_type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>
        type_list;


}}


#endif

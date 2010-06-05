/*! \file
    \brief The definition of bobura::type_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_TYPELISTNEW_H)
#define BOBURA_TYPELISTNEW_H

#include <cstddef>
#include <string>

#include <boost/mpl/insert_range.hpp>

#include <tetengo2.meta.assoc_list.h>


namespace bobura { namespace types
{
    //! The difference type.
    struct difference {};

    //! The size type.
    struct size {};

    //! The string type.
    struct string {};

    //! The common types.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<difference, std::ptrdiff_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<size, std::size_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<string, std::wstring>,
        tetengo2::meta::assoc_list_end
        > > >
        common_types;


}}


#endif

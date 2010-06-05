/*! \file
    \brief The definition of bobura::type_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_TYPELISTNEW_H)
#define BOBURA_TYPELISTNEW_H

#include <cstddef>
#include <string>

#include <tetengo2.meta.assoc_list.h>


namespace bobura
{
    namespace types
    {
        struct difference; //! The difference type.
        struct size;       //! The size type.
        struct string;     //! The string type.
    }

    //! The common type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<types::difference, std::ptrdiff_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<types::size, std::size_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<types::string, std::wstring>,
        tetengo2::meta::assoc_list_end
        > > >
        common_type_list;


}


#endif

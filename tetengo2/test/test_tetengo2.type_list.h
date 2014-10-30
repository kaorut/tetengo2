/*! \file
    \brief The definition of test_tetengo2::type_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_TYPELIST_H)
#define TESTTETENGO2_TYPELIST_H

#include <cstddef>
#include <string>

#include <boost/mpl/pair.hpp>

#include <tetengo2.h>

#include "test_tetengo2.detail_type_list.h"


namespace test_tetengo2
{
    namespace type
    {
        struct size;           //!< The size type.
        struct string;         //!< The string type.
        struct io_string;      //!< The I/O string type.
    }

    /*!
        \brief The type list.
    */
    using type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::size, std::size_t>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::string, std::string>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::io_string, std::string>,
        tetengo2::meta::assoc_list_end
        >>>;


}


#endif

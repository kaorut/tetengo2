/*! \file
    \brief The definition of test_tetengo2::type_list.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_TYPELIST_H)
#define TESTTETENGO2_TYPELIST_H

#include <cstddef>
#include <string>

#include "test_tetengo2.detail_type_list.h"


namespace test_tetengo2 { namespace type_list
{
    /**** Common *****************************************************************************************************/

    /*!
        \brief The common type list.
    */
    struct common
    {
        //! The size type.
        using size_type = std::size_t;

        //! The string type.
        using string_type = std::string;
        
        //! The I/O string type.
        using io_string_type = std::string;

    };

}}


#endif

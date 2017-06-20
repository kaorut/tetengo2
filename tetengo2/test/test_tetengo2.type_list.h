/*! \file
    \brief The definition of test_tetengo2::type_list.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_TYPELIST_H)
#define TESTTETENGO2_TYPELIST_H

#include <cstddef>
#include <string>


namespace test_tetengo2 { namespace type_list
{
    /**** Common *****************************************************************************************************/

    /*!
        \brief The common type list.
    */
    struct common
    {
        //! The integer type.
        using integer_type = int;

        //! The size type.
        using size_type = std::size_t;

        //! The float type.
        using float_type = double;

        //! The string type.
        using string_type = std::wstring;
        
        //! The I/O string type.
        using io_string_type = std::string;


    };


}}


#endif
